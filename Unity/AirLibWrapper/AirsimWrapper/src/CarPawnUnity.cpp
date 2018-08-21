#include "CarPawnUnity.h"
#include "AirSimStructs.hpp"
#include "PInvokeWrapper.h"

using namespace AirSimUnity;

namespace AirSimUnity
{
	CarPawnUnity::CarPawnUnity(int vId)
	{
		is_api_control = false;
		vehicleId = vId;
		image_capture_.reset(new UnityImageCapture(vehicleId));
	}

	CarPawnUnity::~CarPawnUnity()
	{}

	GeoPoint CarPawnUnity::getHomeGeoPoint() const
	{
		return GeoPoint(0, 0, 0);
	}

	void CarPawnUnity::simSetPose(const Pose& pose, bool ignore_collision)
	{
		SetPose(pose, true, vehicleId); //Into Unity
	}

	Pose CarPawnUnity::simGetPose() const
	{
		AirSimPose temp = GetPose(vehicleId); // Into Unity
		Pose pose = Pose();
		pose.position.x() = temp.position.x;
		pose.position.y() = temp.position.y;
		pose.position.z() = temp.position.z;
		pose.orientation.x() = temp.orientation.x;
		pose.orientation.y() = temp.orientation.y;
		pose.orientation.z() = temp.orientation.z;
		pose.orientation.w() = temp.orientation.w;
		return pose;
	}

	bool CarPawnUnity::simSetSegmentationObjectID(const std::string& mesh_name, int object_id, bool is_name_regex)
	{
		return SetSegmentationObjectId(mesh_name.c_str(), object_id, is_name_regex);;
	}

	int CarPawnUnity::simGetSegmentationObjectID(const std::string& mesh_name) const
	{
		return GetSegmentationObjectId(mesh_name.c_str());
	}

	Pose CarPawnUnity::simGetObjectPose(const std::string& object_name) const
	{
		AirSimPose temp = GetPose(vehicleId); // Into Unity
		Pose pose = Pose();
		pose.position.x() = temp.position.x;
		pose.position.y() = temp.position.y;
		pose.position.z() = temp.position.z;
		pose.orientation.x() = temp.orientation.x;
		pose.orientation.y() = temp.orientation.y;
		pose.orientation.z() = temp.orientation.z;
		pose.orientation.w() = temp.orientation.w;
		return pose;
	}

	void CarPawnUnity::enableApiControl(bool is_enabled)
	{
		is_api_control = is_enabled;
		SetEnableApi(is_enabled, vehicleId); // Into Unity
	}

	bool CarPawnUnity::isApiControlEnabled() const
	{
		return is_api_control;
	}

	void CarPawnUnity::reset()
	{
		car_controls = CarControls();
	}

	void CarPawnUnity::setCarControls(const CarControls& controls)
	{
		car_controls = controls;
		SetCarApiControls(controls, vehicleId); // Into Unity
	}

	CarApiBase::CarState CarPawnUnity::getCarState() const
	{
		AirSimCarState carUnityState = GetCarState(vehicleId);  // Into Unity
		float rpm_val = 0.0f;
		float maxrpm_val = 0.0f;
		bool handbrake_val = false;

		CarApiBase::CarState carstate(0.0f, 0, rpm_val, maxrpm_val, handbrake_val, CollisionInfo(), Kinematics::State(), 0);
		AirSimCollisionInfo collision = GetCollisionInfo(vehicleId);
		carstate.speed = carUnityState.speed;
		carstate.gear = carUnityState.gear;
		carstate.timestamp = carUnityState.time_stamp;
		carstate.kinematics_true.pose.position.x() = carUnityState.pose.position.x;
		carstate.kinematics_true.pose.position.y() = carUnityState.pose.position.y;
		carstate.kinematics_true.pose.position.z() = carUnityState.pose.position.z;
		carstate.kinematics_true.pose.orientation.x() = carUnityState.pose.orientation.x;
		carstate.kinematics_true.pose.orientation.y() = carUnityState.pose.orientation.y;
		carstate.kinematics_true.pose.orientation.z() = carUnityState.pose.orientation.z;
		carstate.kinematics_true.pose.orientation.w() = carUnityState.pose.orientation.w;

		//collision
		carstate.collision.has_collided = collision.has_collided;
		carstate.collision.normal.x() = collision.normal.x;
		carstate.collision.normal.y() = collision.normal.y;
		carstate.collision.normal.z() = collision.normal.z;
		carstate.collision.impact_point.x() = collision.impact_point.x;
		carstate.collision.impact_point.y() = collision.impact_point.y;
		carstate.collision.impact_point.z() = collision.impact_point.z;
		carstate.collision.position.x() = collision.position.x;
		carstate.collision.position.y() = collision.position.y;
		carstate.collision.position.z() = collision.position.z;
		carstate.collision.penetration_depth = collision.penetration_depth;
		carstate.collision.time_stamp = collision.time_stamp;
		carstate.collision.collision_count = collision.collision_count;
		carstate.collision.object_name = collision.object_name;
		carstate.collision.object_id = collision.object_id;
		
		return carstate;
	}

	const CarApiBase::CarControls& CarPawnUnity::getCarControls() const
	{
		return car_controls;
	}

	bool  CarPawnUnity::armDisarm(bool arm) 
	{
		unused(arm);
		return true;
	}

	// Get captured Images from Unity based on the Image Requests
	vector<ImageCaptureBase::ImageResponse> CarPawnUnity::simGetImages(const vector<ImageCaptureBase::ImageRequest>& requests) const
	{
		vector<ImageCaptureBase::ImageResponse> responses;
		image_capture_->getImages(requests, responses);
		return responses;
	}

	//Get an image captured using camera id and Image Type
	vector<uint8_t> CarPawnUnity::simGetImage(uint8_t camera_id, ImageCaptureBase::ImageType image_type) const
	{
		vector<ImageCaptureBase::ImageRequest> request = {ImageCaptureBase::ImageRequest(camera_id, image_type)};
		const vector<ImageCaptureBase::ImageResponse>& response = simGetImages(request);
		if (response.size() > 0)
			return response.at(0).image_data_uint8;
		else
			return vector<uint8_t>();
	}

	CameraInfo CarPawnUnity::getCameraInfo(int camera_id) const
	{
		AirSimCameraInfo airsim_camera_info = GetCameraInfo(camera_id, vehicleId); // Into Unity
		CameraInfo camera_info;
		camera_info.pose.position.x() = airsim_camera_info.pose.position.x;
		camera_info.pose.position.y() = airsim_camera_info.pose.position.y;
		camera_info.pose.position.z() = airsim_camera_info.pose.position.z;
		camera_info.pose.orientation.x() = airsim_camera_info.pose.orientation.x;
		camera_info.pose.orientation.y() = airsim_camera_info.pose.orientation.y;
		camera_info.pose.orientation.z() = airsim_camera_info.pose.orientation.z;
		camera_info.pose.orientation.w() = airsim_camera_info.pose.orientation.w;
		camera_info.fov = airsim_camera_info.fov;
		return camera_info;
	}

	void CarPawnUnity::setCameraOrientation(int camera_id, const Quaternionr& orientation)
	{
		AirSimQuaternion airsim_orientation;
		airsim_orientation.x = orientation.x();
		airsim_orientation.x = orientation.y();
		airsim_orientation.x = orientation.z();
		airsim_orientation.x = orientation.w();
		SetCameraOrientation(camera_id, airsim_orientation, vehicleId); // Into Unity
	}

	CollisionInfo CarPawnUnity::getCollisionInfo() const
	{
		CollisionInfo collision;
		AirSimCollisionInfo collision_unity = GetCollisionInfo(vehicleId);  // Into Unity
		collision.has_collided = collision_unity.has_collided;
		collision.normal.x() = collision_unity.normal.x;
		collision.normal.y() = collision_unity.normal.y;
		collision.normal.z() = collision_unity.normal.z;
		collision.impact_point.x() = collision_unity.impact_point.x;
		collision.impact_point.y() = collision_unity.impact_point.y;
		collision.impact_point.z() = collision_unity.impact_point.z;
		collision.position.x() = collision_unity.position.x;
		collision.position.y() = collision_unity.position.y;
		collision.position.z() = collision_unity.position.z;
		collision.penetration_depth = collision_unity.penetration_depth;
		collision.time_stamp = collision_unity.time_stamp;
		collision.collision_count = collision_unity.collision_count;
		collision.object_name = collision_unity.object_name;
		collision.object_id = collision_unity.object_id;
		return collision;
	}

	void CarPawnUnity::simPrintLogMessage(const std::string& message, const std::string& message_param, unsigned char severity)
	{
		PrintLogMessage(message.c_str(), message_param.c_str(), (int)severity, vehicleId);
	}
}