//------------------------------------------------------------------------------
//
//  Intan Technologies RHX Data Acquisition Software
//  Version 3.1.0
//
//  Copyright (c) 2020-2022 Intan Technologies
//
//  This file is part of the Intan Technologies RHX Data Acquisition Software.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  This software is provided 'as-is', without any express or implied warranty.
//  In no event will the authors be held liable for any damages arising from
//  the use of this software.
//
//  See <http://www.intantech.com> for documentation and product information.
//
//------------------------------------------------------------------------------

#include "ButtonSocketListener.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <thread>
#include <fstream>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <errno.h>
#define INVALID_SOCKET -1
#endif

#include <qaction.h>

/*!
 * \brief Implementation of ButtonSocketListener
 */
class ButtonSocketListenerImpl
{
public:
	SOCKET m_socket = INVALID_SOCKET;
	std::thread* m_thread;
	bool m_running = true;
	QAction* m_record_action;
	QAction* m_stop_action;

	std::string m_server_ip_address;

#ifdef _WIN32
#define SOCKET_PORT "1299"
#else
#define SOCKET_PORT 1299
#endif

	struct Message
	{
		int		m_command_code;
		double	m_time;
	};


	//---------------------------------------------------

	ButtonSocketListenerImpl(QAction* record_action, QAction* stop_action) 
		: m_record_action(record_action)
		, m_stop_action(stop_action)
	{
		std::ifstream file;
		file.open("ServerIP.txt", std::ios::in);
		if (!file.is_open())
		{
			char cwd[MAX_PATH];
#ifdef _WIN32
			GetCurrentDirectory(MAX_PATH, cwd);
#else
			cwd[0] = 0;
#endif
			printf("\nTILO: ServerIP.txt not found in folder %s. Using 127.0.0.1\n\n", cwd);
			m_server_ip_address = "127.0.0.1";
		}
		else
		{
			std::getline(file, m_server_ip_address);

			printf("\nServerIP.txt found, using IP address %s\n\n", m_server_ip_address.c_str());
			file.close();
		}

		m_thread = new std::thread(std::bind(&ButtonSocketListenerImpl::ThreadRun, this));
	}

	//---------------------------------------------------

	~ButtonSocketListenerImpl()
	{
		m_running = false;
		closesocket(m_socket);
		m_thread->join();
		delete m_thread;
	}

	//---------------------------------------------------

	double GetTimeSecs()
	{
#ifdef _WIN32
		LARGE_INTEGER count;
		LARGE_INTEGER frequency;

		QueryPerformanceCounter(&count);
		QueryPerformanceFrequency(&frequency);

		return (double)count.QuadPart / (double)frequency.QuadPart;
#else
		struct timespec time;
		clock_gettime(CLOCK_REALTIME, &time);

		double t = (double)(time.tv_sec + (double)time.tv_nsec / 1e9);
		return t;
#endif
	}

	//---------------------------------------------------

	void ThreadRun()
	{
		while (m_running)
		{
			// Connect.
			while (m_socket == INVALID_SOCKET && m_running)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				printf("ButtonSocketListenerImpl: Connecting\n");
				Connect();
			}

			char recvbuf[512];
			char str[256];

			if (m_socket != INVALID_SOCKET && m_running)
			{
				printf("ButtonSocketListenerImpl: Connected to button server\n");

				int result;

				do {
					result = recv(m_socket, recvbuf, 512, 0);
					if (result > 0)
					{
						if (result == sizeof(Message))
						{
							Message* msg = (Message*)recvbuf;

							if (msg->m_command_code == 0)
							{
								sprintf_s(str, "Time - %.3f ms\n", (GetTimeSecs() - msg->m_time) * 1000.0);
								printf(str);

								m_record_action->activate(QAction::ActionEvent::Trigger);								
							}
							else if (msg->m_command_code == 1)
							{
								m_stop_action->activate(QAction::ActionEvent::Trigger);								
							}
						}
					}
					else if (result == 0)
					{
						printf("ButtonSocketListenerImpl: Connection closed\n");
					}
					else
					{
						printf(str, "ButtonSocketListenerImpl: recv failed with error: %d\n", WSAGetLastError());
					}

				} while (result > 0);

#ifdef _WIN32
				closesocket(m_socket);
				WSACleanup();
#else
				shutdown(m_socket, SHUT_RD);
				close(m_socket);
#endif
				m_socket = INVALID_SOCKET;
			}
		}
	}

	bool Connect()
	{
#ifdef _WIN32
		WSADATA wsaData;
		struct addrinfo hints;
		struct addrinfo* addresses;

		int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (error != 0)
		{
			printf("ButtonSocketListenerImpl: WSAStartup failed with error: %d\n", error);
			return false;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		error = getaddrinfo(m_server_ip_address.c_str(), SOCKET_PORT, &hints, &addresses);
		if (error != 0)
		{
			printf("ButtonSocketListenerImpl: getaddrinfo %s failed with error: %d\n", m_server_ip_address.c_str(), error);
			WSACleanup();
			return false;
		}

		for (struct addrinfo* ptr = addresses; ptr != NULL; ptr = ptr->ai_next)
		{

			// Create a SOCKET for connecting to server
			m_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (m_socket == INVALID_SOCKET)
			{
				printf("ButtonSocketListenerImpl: socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return false;
			}

			// Connect to server.
			error = connect(m_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (error == SOCKET_ERROR)
			{
				closesocket(m_socket);
				m_socket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(addresses);

		if (m_socket == INVALID_SOCKET) 
		{
			printf("ButtonSocketListenerImpl: Unable to connect to server!\n");
			WSACleanup();
			return false;
		}

		return true;
#else
		struct sockaddr_in serv_addr;
		struct hostent* server;

		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			printf("ButtonSocketListenerImpl: ERROR opening socket\n");
			return false;
		}

		std::string ip_address = m_listener->GetHostIpAddress();
		server = gethostbyname(ip_address.c_str());
		if (server == NULL)
		{
			printf("ButtonSocketListenerImpl: ERROR, no such host\n");
			return false;
		}

		bzero((char*)&serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;

		bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
		serv_addr.sin_port = htons(JetsonProtocol::SOCKET_PORT);

		struct timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

		if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		{
			//printf("ButtonSocketListenerImpl: %f ERROR connecting %d\n",GetTimeSecs(), errno);
			// 111 = ECONNREFUSED
			shutdown(sockfd, SHUT_RD);
			close(sockfd);
			return false;
		}

		// Disable NAGGLE algorithm as it causes big delays.
		int flag = 1;
		setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (char*)&flag, sizeof(int));
		flag = 0;
		setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (char*)&flag, sizeof(int));

		// Reset timeout as m_socket inherits setting from socket_. 0 = never times out (default).
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));

		m_socket = sockfd;
		return true;
#endif
	}
};


//-------------------------------------------------------

ButtonSocketListener::ButtonSocketListener(QAction* record_action, QAction* stop_action)
{
	m_impl = new ButtonSocketListenerImpl(record_action, stop_action);
}

//-------------------------------------------------------

ButtonSocketListener::~ButtonSocketListener()
{
	delete m_impl;
}

