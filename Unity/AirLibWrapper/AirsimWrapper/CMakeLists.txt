cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(AirsimWrapper LANGUAGES CXX)

SET( EIGEN3_INCLUDE_DIR  /usr/include/eigen3/)
IF( NOT EIGEN3_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
ENDIF()
INCLUDE_DIRECTORIES ( "${EIGEN3_INCLUDE_DIR}"  )

set (CMAKE_CXX_STANDARD 11)
#include(GNUInstallDirs)


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
#    Source/Vehicles/Multirotor/FlyingPawn.cpp
#    Source/Vehicles/Multirotor/MultirotorPawnEvents.cpp
#    Source/Vehicles/Multirotor/MultirotorPawnSimApi.cpp
#    Source/Vehicles/Multirotor/SimModeWorldMultiRotor.cpp
    Source/WorldSimApi.cpp )

target_include_directories(AirsimWrapper 
							PRIVATE .
							PRIVATE ../../../AirLib/include
							PRIVATE ../../../AirLib/include/vehicles/car
							PRIVATE ../../../AirLib/deps/rpclib/include
                            PRIVATE ../../../AirLib/deps/MavLinkCom/include
							)



find_library(MAVLINK_LIBRARY MavLinkCom HINTS ../../../AirLib/deps/MavLinkCom/lib)
find_library(AIRLIB_LIBRARY AirLib HINTS ../../../AirLib/lib)
find_library(RPC_LIBRARY rpc HINTS ../../../AirLib/deps/rpclib/lib)

IF( NOT RPC_LIBRARY )
    MESSAGE(FATAL_ERROR "rpc library not found")
ENDIF()

target_link_libraries(AirsimWrapper ${MAVLINK_LIBRARY} ${AIRLIB_LIBRARY} ${RPC_LIBRARY})



install(TARGETS AirsimWrapper DESTINATION lib )
#install(FILES     
#    Source/AirSimStructs.hpp
#    Source/Logger.h
#    Source/NedTransform.h
#    Source/SimMode/SimModeWorldBase.h
#    Source/UnityPawn.h
#    Source/PawnSimApi.h
#    Source/PInvokeWrapper.h
#    Source/SimHUD/SimHUD.h
#    Source/SimMode/SimModeBase.h
#    Source/UnityImageCapture.h
#    Source/UnitySensors/UnityDistanceSensor.h
#    Source/UnitySensors/UnitySensorFactory.h
#    Source/UnityToAirSimCalls.h
#    Source/UnityUtilities.hpp
#    Source/Vehicles/Car/CarPawn.h
#    Source/Vehicles/Car/CarPawnApi.h
#    Source/Vehicles/Car/CarPawnSimApi.h
#    Source/Vehicles/Car/SimModeCar.h
#    Source/Vehicles/Multirotor/FlyingPawn.h
#    Source/Vehicles/Multirotor/MultirotorPawnEvents.h
#    Source/Vehicles/Multirotor/MultirotorPawnSimApi.h
#    Source/Vehicles/Multirotor/SimModeWorldMultiRotor.h
#    Source/WorldSimApi.h
#    DESTINATION include)
