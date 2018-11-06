cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(AirsimWrapper LANGUAGES CXX)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)



SET( EIGEN3_INCLUDE_DIR  /usr/include/eigen3/)
IF( NOT EIGEN3_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
ENDIF()
INCLUDE_DIRECTORIES ( "${EIGEN3_INCLUDE_DIR}"  )

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
#    Source/Vehicles/Multirotor/FlyingPawn.cpp
#    Source/Vehicles/Multirotor/MultirotorPawnEvents.cpp
#    Source/Vehicles/Multirotor/MultirotorPawnSimApi.cpp
#    Source/Vehicles/Multirotor/SimModeWorldMultiRotor.cpp
    Source/WorldSimApi.cpp
    ../../../AirLib/src/vehicles/car/api/CarRpcLibServer.cpp
    ../../../AirLib/src/api/RpcLibServerBase.cpp
            )

target_include_directories(AirsimWrapper 
							PRIVATE .
							PRIVATE ../../../AirLib/include
							#PRIVATE ../../../AirLib/include/vehicles/car
                            #PRIVATE ../../../AirLib/include/vehicles/car/api
							PRIVATE ../../../AirLib/deps/rpclib/include
                            #PRIVATE ../../../AirLib/deps/MavLinkCom/include
							)



find_library(MAVLINK_LIBRARY MavLinkCom HINTS ../../../AirLib/deps/MavLinkCom/lib)
find_library(AIRLIB_LIBRARY AirLib HINTS ../../../AirLib/lib)
find_library(RPC_LIBRARY rpc HINTS ../../../AirLib/deps/rpclib/lib)


target_link_libraries(AirsimWrapper  ${RPC_LIBRARY} ${AIRLIB_LIBRARY} ${MAVLINK_LIBRARY} )


install(TARGETS AirsimWrapper DESTINATION lib )



