#include "PInvokeWrapper.h"

//Function pointers to hold the addresses of the functions that are defined in Unity
bool(*SetPose)(AirSimPose pose, bool ignore_collision, int vehicleId);
AirSimPose(*GetPose)(int vehicleId);
AirSimCollisionInfo(*GetCollisionInfo)(int vehicleId);
AirSimRCData(*GetRCData)(int vehicleId);
AirSimImageResponse(*GetSimImages)(AirSimImageRequest request, int vehicleId);
bool(*SetRotorSpeed)(int rotor_index, RotorInfo rotor_info, int vehicleId);
bool(*SetEnableApi)(bool enable_api, int vehicleId);
bool(*SetCarApiControls)(msr::airlib::CarApiBase::CarControls controls, int vehicleId);
AirSimCarState(*GetCarState)(int vehicleId);
AirSimCameraInfo(*GetCameraInfo)(int cameraId, int vehicleId);
bool(*SetCameraOrientation)(int cameraId,AirSimQuaternion orientation, int vehicleId);
bool(*SetSegmentationObjectId)(const char* mesh_name, int object_id, bool is_name_regex);
int(*GetSegmentationObjectId)(const char* mesh_name);
bool(*PrintLogMessage) (const char* message, const char* message_param, int severity,int vehicleId);


void InitVehicleManager(
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
	bool(*setSegmentationObjectId)(const char* mesh_name, int object_id,bool is_name_regex),
	int(*getSegmentationObjectId)(const char* mesh_name),
	bool(*printLogMessage) (const char* message, const char* message_param, int severity, int vehicleId)
)
{
	SetPose = setPose;
	GetPose = getPose;
	GetCollisionInfo = getCollisionInfo;
	GetRCData = getDroneRCData;
	GetSimImages = getSimImages;
	SetRotorSpeed = setRotorSpeed;
	SetEnableApi = setEnableApi;
	SetCarApiControls = setCarApiControls;
	GetCarState = getCarState;
	GetCameraInfo = getCameraInfo;
	SetCameraOrientation = setCameraOrientation;
	SetSegmentationObjectId = setSegmentationObjectId;
	GetSegmentationObjectId = getSegmentationObjectId;
	PrintLogMessage = printLogMessage;
}