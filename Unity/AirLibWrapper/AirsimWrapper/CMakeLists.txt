cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(AirsimWrapper LANGUAGES CXX)

SET( EIGEN3_INCLUDE_DIR  /usr/include/eigen3/)
IF( NOT EIGEN3_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
ENDIF()
INCLUDE_DIRECTORIES ( "${EIGEN3_INCLUDE_DIR}"  ~/repositories/AirSim2/AirLib/deps/MavLinkCom/lib)

set (CMAKE_CXX_STANDARD 11)
include(GNUInstallDirs)

add_library(AirsimWrapper SHARED 
	Source/Logger.cpp
    Source/NedTransform.cpp
    Source/PawnSimApi.cpp
    Source/PInvokeWrapper.cpp
    Source/SimHUD/SimHUD.cpp
    Source/SimMode/SimModeBase.cpp
    Source/SimMode/SimModeWorldBase.cpp
    Source/UnityImageCapture.cpp
    Source/UnitySensors/UnityDistanceSensor.cpp
    Source/UnitySensors/UnitySensorFactory.cpp
    Source/UnityToAirSimCalls.cpp
    Source/Vehicles/Car/CarPawn.cpp
    Source/Vehicles/Car/CarPawnApi.cpp
    Source/Vehicles/Car/CarPawnSimApi.cpp
    Source/Vehicles/Car/SimModeCar.cpp
    Source/Vehicles/Multirotor/FlyingPawn.cpp
    Source/Vehicles/Multirotor/MultirotorPawnEvents.cpp
    Source/Vehicles/Multirotor/MultirotorPawnSimApi.cpp
    Source/Vehicles/Multirotor/SimModeWorldMultiRotor.cpp
    Source/WorldSimApi.cpp )

#set_target_properties(AirsimWrapper PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(AirsimWrapper PROPERTIES 
						SOVERSION 1 )
						#PUBLIC_HEADER include/wrapperlib.h)
configure_file(AirsimWrapper.pc.in AirsimWrapper.pc @ONLY)

target_include_directories(AirsimWrapper 
							PRIVATE .
							PRIVATE ../../../AirLib/include
							PRIVATE ../../../AirLib/include/vehicles/car
							PRIVATE ../../../AirLib/deps/MavLinkCom/include
							PRIVATE ../../../AirLib/deps/rpclib/include

							)



find_library(MAVLINK_LIBRARY MavLinkCom HINTS ../../../AirLib/deps/MavLinkCom/lib)
find_library(AIRLIB_LIBRARY AirLib HINTS ../../../AirLib/lib)		
target_link_libraries(AirsimWrapper ${MAVLINK_LIBRARY} ${AIRLIB_LIBRARY} )



install(TARGETS AirsimWrapper LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )
install(FILES 		${CMAKE_BINARY_DIR}/AirsimWrapper.pc 
		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
