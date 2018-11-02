cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(AirSimWrapper LANGUAGES CXX)

SET( EIGEN3_INCLUDE_DIR  /usr/include/eigen3/)
IF( NOT EIGEN3_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
ENDIF()
INCLUDE_DIRECTORIES ( "${EIGEN3_INCLUDE_DIR}" )

set (CMAKE_CXX_STANDARD 11)
include(GNUInstallDirs)

add_library(wrapperlib SHARED 
		Source/Logger.cpp
		Source/NedTransform.cpp
		Source/PawnSimApi.cpp
		Source/PInvokeWrapper.cpp
		Source/UnityImageCapture.cpp
		Source/WorldSimApi.cpp )

#set_target_properties(wrapperlib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(wrapperlib PROPERTIES 
						SOVERSION 1 
						PUBLIC_HEADER include/wrapperlib.h)
configure_file(wrapperlib.pc.in wrapperlib.pc @ONLY)

target_include_directories(wrapperlib PRIVATE . )
target_include_directories(wrapperlib PRIVATE ../../../AirLib/include)

install(TARGETS wrapperlib LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )
install(FILES 		${CMAKE_BINARY_DIR}/wrapperlib.pc 
		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
