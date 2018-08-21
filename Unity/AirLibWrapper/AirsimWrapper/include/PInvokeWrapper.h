#pragma once

#include "AirSimStructs.hpp"
#include "UnityImageCapture.h"
#include "vehicles/car/api/CarApiBase.hpp"

/*
* Defines all the functions that can be called into Unity
*/

//Function pointers to hold the addresses of the functions that are defined in Unity
extern bool(*SetPose)(AirSimPose pose, bool ignore_collision, int vehicleId);
extern AirSimPose(*GetPose)(int vehicleId);
extern AirSimCollisionInfo(*GetCollisionInfo)(int vehicleId);
extern AirSimRCData(*GetRCData)(int vehicleId);
extern AirSimImageResponse(*GetSimImages)(AirSimImageRequest request, int vehicleId);
extern bool(*SetRotorSpeed)(int rotor_index, RotorInfo rotor_info, int vehicleId);
extern bool(*SetEnableApi)(bool enable_api, int vehicleId);
extern bool(*SetCarApiControls)(msr::airlib::CarApiBase::CarControls controls, int vehicleId);
extern AirSimCarState(*GetCarState)(int vehicleId);
extern AirSimCameraInfo(*GetCameraInfo)(int cameraId, int vehicleId);
extern bool(*SetCameraOrientation)(int cameraId, AirSimQuaternion orientation, int vehicleId);
extern bool(*SetSegmentationObjectId)(const char* mesh_name, int object_id, bool is_name_regex);
extern int(*GetSegmentationObjectId)(const char* mesh_name);
extern bool(*PrintLogMessage) (const char* message, const char* message_param, int severity,int vehicleId);

// PInvoke call to initialize the function pointers. This function is called from Unity.
extern "C" __declspec(dllexport) void InitVehicleManager(
	bool(*setPose)(AirSimPose pose, bool ignore_collision, int vehicleId),
	AirSimPose(*getPose)(int vehicleId),
	AirSimCollisionInfo(*getCollisionInfo)(int vehicleId),
	AirSimRCData(*getDroneRCData)(int vehicleId),
	AirSimImageResponse(*getSimImages)(AirSimImageRequest request, int vehicleId),
	bool(*setRotorSpeed)(int rotor_index, RotorInfo rotor_info, int vehicleId),
	bool(*setEnableApi)(bool enable_api, int vehicleId),
	bool(*setCarApiControls)(msr::airlib::CarApiBase::CarControls controls, int vehicleId),
	AirSimCarState(*getCarState)(int vehicleId),
	AirSimCameraInfo(*getCameraInfo)(int cameraId, int vehicleId),
	bool(*setCameraOrientation)(int cameraId, AirSimQuaternion orientation, int vehicleId),
	bool(*setSegmentationObjectId)(const char* mesh_name, int object_id, bool is_name_regex),
	int(*getSegmentationObjectId)(const char* mesh_name),
	bool(*printLogMessage) (const char* message, const char* message_param, int severity, int vehicleId)
);