cmake_minimum_required(VERSION 3.23.1)

project (IntanRHX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD_REQUIRED 14)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/runtime")

include_directories ("${CMAKE_SOURCE_DIR}/Engine/Processing")
include_directories ("${CMAKE_SOURCE_DIR}/Engine/Processing/DataFileReaders")
include_directories ("${CMAKE_SOURCE_DIR}/Engine/Processing/SaveManagers")
include_directories ("${CMAKE_SOURCE_DIR}/Engine/Processing/XPUInterfaces")
include_directories ("${CMAKE_SOURCE_DIR}/Engine/Threads")
include_directories ("${CMAKE_SOURCE_DIR}/Engine/API/Synthetic")
include_directories ("${CMAKE_SOURCE_DIR}/Engine/API/Abstract")
include_directories ("${CMAKE_SOURCE_DIR}/Engine/API/Hardware")
include_directories ("${CMAKE_SOURCE_DIR}/GUI/Dialogs")
include_directories ("${CMAKE_SOURCE_DIR}/GUI/Widgets")
include_directories ("${CMAKE_SOURCE_DIR}/GUI/Windows")
include_directories ("${CMAKE_SOURCE_DIR}/includes")

find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5MultiMedia)
find_package(Qt5Xml)

set(HEADER_FILES 
    Engine/API/Synthetic/playbackrhxcontroller.h
    Engine/API/Synthetic/randomnumber.h
    Engine/API/Synthetic/synthdatablockgenerator.h
    Engine/API/Synthetic/syntheticrhxcontroller.h
    Engine/API/Abstract/abstractrhxcontroller.h
    Engine/API/Hardware/rhxcontroller.h
    Engine/API/Hardware/rhxdatablock.h
    Engine/API/Hardware/rhxglobals.h
    Engine/API/Hardware/rhxregisters.h
    Engine/Processing/DataFileReaders/datafile.h
    Engine/Processing/DataFileReaders/datafilemanager.h
    Engine/Processing/DataFileReaders/datafilereader.h
    Engine/Processing/DataFileReaders/fileperchannelmanager.h
    Engine/Processing/DataFileReaders/filepersignaltypemanager.h
    Engine/Processing/DataFileReaders/traditionalintanfilemanager.h
    Engine/Processing/SaveManagers/fileperchannelsavemanager.h
    Engine/Processing/SaveManagers/filepersignaltypesavemanager.h
    Engine/Processing/SaveManagers/intanfilesavemanager.h
    Engine/Processing/SaveManagers/savefile.h
    Engine/Processing/SaveManagers/savemanager.h
    Engine/Processing/XPUInterfaces/abstractxpuinterface.h
    Engine/Processing/XPUInterfaces/cpuinterface.h
    Engine/Processing/XPUInterfaces/gpuinterface.h
    Engine/Processing/XPUInterfaces/xpucontroller.h
    Engine/Processing/channel.h
    Engine/Processing/commandparser.h
    Engine/Processing/controllerinterface.h
    Engine/Processing/datastreamfifo.h
    Engine/Processing/displayundomanager.h
    Engine/Processing/fastfouriertransform.h
    Engine/Processing/filter.h
    Engine/Processing/matfilewriter.h
    Engine/Processing/minmax.h
    Engine/Processing/probemapdatastructures.h
    Engine/Processing/rhxdatareader.h
    Engine/Processing/semaphore.h
    Engine/Processing/signalsources.h
    Engine/Processing/softwarereferenceprocessor.h
    Engine/Processing/stateitem.h
    Engine/Processing/stimparameters.h
    Engine/Processing/stimparametersclipboard.h
    Engine/Processing/systemstate.h
    Engine/Processing/tcpcommunicator.h
    Engine/Processing/waveformfifo.h
    Engine/Processing/impedancereader.h
    Engine/Processing/xmlinterface.h
    Engine/Threads/audiothread.h
    Engine/Threads/savetodiskthread.h
    Engine/Threads/tcpdataoutputthread.h
    Engine/Threads/usbdatathread.h
    Engine/Threads/waveformprocessorthread.h
    GUI/Dialogs/advancedstartupdialog.h
    GUI/Dialogs/ampsettledialog.h
    GUI/Dialogs/analogoutconfigdialog.h
    GUI/Dialogs/anoutdialog.h
    GUI/Dialogs/autocolordialog.h
    GUI/Dialogs/autogroupdialog.h
    GUI/Dialogs/auxdigoutconfigdialog.h
    GUI/Dialogs/bandwidthdialog.h
    GUI/Dialogs/boardselectdialog.h
    GUI/Dialogs/cabledelaydialog.h
    GUI/Dialogs/chargerecoverydialog.h
    GUI/Dialogs/demodialog.h
    GUI/Dialogs/digoutdialog.h
    GUI/Dialogs/isidialog.h
    GUI/Dialogs/keyboardshortcutdialog.h
    GUI/Dialogs/performanceoptimizationdialog.h
    GUI/Dialogs/playbackfilepositiondialog.h
    GUI/Dialogs/psthdialog.h
    GUI/Dialogs/referenceselectdialog.h
    GUI/Dialogs/renamechanneldialog.h
    GUI/Dialogs/scrollablemessageboxdialog.h
    GUI/Dialogs/setfileformatdialog.h
    GUI/Dialogs/setthresholdsdialog.h
    GUI/Dialogs/spectrogramdialog.h
    GUI/Dialogs/spikesortingdialog.h
    GUI/Dialogs/startupdialog.h
    GUI/Dialogs/stimparamdialog.h
    GUI/Dialogs/triggerrecorddialog.h
    GUI/Dialogs/waveformselectdialog.h
    GUI/Widgets/abstractfigure.h
    GUI/Widgets/anoutfigure.h
    GUI/Widgets/controlpanelaudioanalogtab.h
    GUI/Widgets/controlpanelbandwidthtab.h
    GUI/Widgets/controlpanelconfiguretab.h
    GUI/Widgets/controlpanelimpedancetab.h
    GUI/Widgets/controlpaneltriggertab.h
    GUI/Widgets/digfigure.h
    GUI/Widgets/displayedwaveform.h
    GUI/Widgets/displaylistmanager.h
    GUI/Widgets/filterdisplayselector.h
    GUI/Widgets/filterplot.h
    GUI/Widgets/impedancegradient.h
    GUI/Widgets/isiplot.h
    GUI/Widgets/multicolumndisplay.h
    GUI/Widgets/multiwaveformplot.h
    GUI/Widgets/pageview.h
    GUI/Widgets/plotutilities.h
    GUI/Widgets/psthplot.h
    GUI/Widgets/scrollbar.h
    GUI/Widgets/smartspinbox.h
    GUI/Widgets/spikegradient.h
    GUI/Widgets/spikeplot.h
    GUI/Widgets/statusbars.h
    GUI/Widgets/stimfigure.h
    GUI/Widgets/tcpdisplay.h
    GUI/Widgets/voltagespinbox.h
    GUI/Widgets/waveformdisplaycolumn.h
    GUI/Widgets/waveformdisplaymanager.h
    GUI/Windows/controlwindow.h
    GUI/Windows/probemapwindow.h
    GUI/Dialogs/impedancefreqdialog.h
    GUI/Widgets/controlpanel.h
    GUI/Widgets/spectrogramplot.h
    GUI/Windows/viewfilterswindow.h
	GUI/Windows/ButtonSocketListener.h
	)
	
set(SOURCE_FILES 
main.cpp
    Engine/API/Synthetic/playbackrhxcontroller.cpp
    Engine/API/Synthetic/randomnumber.cpp
    Engine/API/Synthetic/synthdatablockgenerator.cpp
    Engine/API/Synthetic/syntheticrhxcontroller.cpp
    Engine/API/Abstract/abstractrhxcontroller.cpp
    Engine/API/Hardware/rhxcontroller.cpp
    Engine/API/Hardware/rhxdatablock.cpp
    Engine/API/Hardware/rhxregisters.cpp
    Engine/Processing/DataFileReaders/datafile.cpp
    Engine/Processing/DataFileReaders/datafilemanager.cpp
    Engine/Processing/DataFileReaders/datafilereader.cpp
    Engine/Processing/DataFileReaders/fileperchannelmanager.cpp
    Engine/Processing/DataFileReaders/filepersignaltypemanager.cpp
    Engine/Processing/DataFileReaders/traditionalintanfilemanager.cpp
    Engine/Processing/SaveManagers/fileperchannelsavemanager.cpp
    Engine/Processing/SaveManagers/filepersignaltypesavemanager.cpp
    Engine/Processing/SaveManagers/intanfilesavemanager.cpp
    Engine/Processing/SaveManagers/savefile.cpp
    Engine/Processing/SaveManagers/savemanager.cpp
    Engine/Processing/XPUInterfaces/abstractxpuinterface.cpp
    Engine/Processing/XPUInterfaces/cpuinterface.cpp
    Engine/Processing/XPUInterfaces/gpuinterface.cpp
    Engine/Processing/XPUInterfaces/xpucontroller.cpp
    Engine/Processing/channel.cpp
    Engine/Processing/commandparser.cpp
    Engine/Processing/controllerinterface.cpp
    Engine/Processing/datastreamfifo.cpp
    Engine/Processing/displayundomanager.cpp
    Engine/Processing/fastfouriertransform.cpp
    Engine/Processing/filter.cpp
    Engine/Processing/matfilewriter.cpp
    Engine/Processing/rhxdatareader.cpp
    Engine/Processing/signalsources.cpp
    Engine/Processing/softwarereferenceprocessor.cpp
    Engine/Processing/stateitem.cpp
    Engine/Processing/stimparameters.cpp
    Engine/Processing/stimparametersclipboard.cpp
    Engine/Processing/systemstate.cpp
    Engine/Processing/tcpcommunicator.cpp
    Engine/Processing/waveformfifo.cpp
    Engine/Processing/impedancereader.cpp
    Engine/Processing/xmlinterface.cpp
    Engine/Threads/audiothread.cpp
    Engine/Threads/savetodiskthread.cpp
    Engine/Threads/tcpdataoutputthread.cpp
    Engine/Threads/usbdatathread.cpp
    Engine/Threads/waveformprocessorthread.cpp
    GUI/Dialogs/advancedstartupdialog.cpp
    GUI/Dialogs/ampsettledialog.cpp
    GUI/Dialogs/analogoutconfigdialog.cpp
    GUI/Dialogs/anoutdialog.cpp
    GUI/Dialogs/autocolordialog.cpp
    GUI/Dialogs/autogroupdialog.cpp
    GUI/Dialogs/auxdigoutconfigdialog.cpp
    GUI/Dialogs/bandwidthdialog.cpp
    GUI/Dialogs/boardselectdialog.cpp
    GUI/Dialogs/cabledelaydialog.cpp
    GUI/Dialogs/chargerecoverydialog.cpp
    GUI/Dialogs/demodialog.cpp
    GUI/Dialogs/digoutdialog.cpp
    GUI/Dialogs/isidialog.cpp
    GUI/Dialogs/keyboardshortcutdialog.cpp
    GUI/Dialogs/performanceoptimizationdialog.cpp
    GUI/Dialogs/playbackfilepositiondialog.cpp
    GUI/Dialogs/psthdialog.cpp
    GUI/Dialogs/referenceselectdialog.cpp
    GUI/Dialogs/renamechanneldialog.cpp
    GUI/Dialogs/scrollablemessageboxdialog.cpp
    GUI/Dialogs/setfileformatdialog.cpp
    GUI/Dialogs/setthresholdsdialog.cpp
    GUI/Dialogs/spectrogramdialog.cpp
    GUI/Dialogs/spikesortingdialog.cpp
    GUI/Dialogs/startupdialog.cpp
    GUI/Dialogs/stimparamdialog.cpp
    GUI/Dialogs/triggerrecorddialog.cpp
    GUI/Dialogs/waveformselectdialog.cpp
    GUI/Widgets/abstractfigure.cpp
    GUI/Widgets/anoutfigure.cpp
    GUI/Widgets/controlpanelaudioanalogtab.cpp
    GUI/Widgets/controlpanelbandwidthtab.cpp
    GUI/Widgets/controlpanelconfiguretab.cpp
    GUI/Widgets/controlpanelimpedancetab.cpp
    GUI/Widgets/controlpaneltriggertab.cpp
    GUI/Widgets/digfigure.cpp
    GUI/Widgets/displayedwaveform.cpp
    GUI/Widgets/displaylistmanager.cpp
    GUI/Widgets/filterdisplayselector.cpp
    GUI/Widgets/filterplot.cpp
    GUI/Widgets/impedancegradient.cpp
    GUI/Widgets/isiplot.cpp
    GUI/Widgets/multicolumndisplay.cpp
    GUI/Widgets/multiwaveformplot.cpp
    GUI/Widgets/pageview.cpp
    GUI/Widgets/plotutilities.cpp
    GUI/Widgets/psthplot.cpp
    GUI/Widgets/scrollbar.cpp
    GUI/Widgets/smartspinbox.cpp
    GUI/Widgets/spikegradient.cpp
    GUI/Widgets/spikeplot.cpp
    GUI/Widgets/statusbars.cpp
    GUI/Widgets/stimfigure.cpp
    GUI/Widgets/tcpdisplay.cpp
    GUI/Widgets/voltagespinbox.cpp
    GUI/Widgets/waveformdisplaycolumn.cpp
    GUI/Widgets/waveformdisplaymanager.cpp
    GUI/Windows/controlwindow.cpp
    GUI/Windows/probemapwindow.cpp
    GUI/Dialogs/impedancefreqdialog.cpp
    GUI/Widgets/controlpanel.cpp
    GUI/Widgets/spectrogramplot.cpp
    GUI/Windows/viewfilterswindow.cpp
	IntanRHX.qrc
	GUI/Windows/ButtonSocketListener.cpp
	)

add_executable (${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "TestBed")

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::Multimedia Qt5::Xml)


if(WIN32)
	target_link_libraries(${PROJECT_NAME}  opengl32.lib glu32.lib Ws2_32.lib)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /DEBUG)
else()

endif()

add_library(opencl STATIC IMPORTED)
set_target_properties(opencl PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libraries/Windows/OpenCL.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/includes/CL"
)

add_library(delayimp STATIC IMPORTED)
set_target_properties(delayimp PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libraries/Windows/delayimp.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/includes"
)

target_link_libraries(${PROJECT_NAME} opencl delayimp ${CMAKE_SOURCE_DIR}/libraries/Windows/okFrontPanel.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/DELAYLOAD:${CMAKE_SOURCE_DIR}/libraries/Windows/okFrontPanel.dll")





