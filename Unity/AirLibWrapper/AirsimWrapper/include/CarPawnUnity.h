#pragma once

#include"vehicles/car/api/CarApiBase.hpp"
#include "UnityImageCapture.h"

using namespace msr::airlib;

/*
* This is the implementation of Car.
* This implements all the necessary API's related to car simulation provided by AirLib.
* PInvoke methods are used to communicate to the Unity layer.
*/
namespace AirSimUnity
{
	class CarPawnUnity :public msr::airlib::CarApiBase
	{
	public:
		//ctor and dtor
		CarPawnUnity(int vId);
		~CarPawnUnity();

		//Poses
		GeoPoint getHomeGeoPoint() const;
		void simSetPose(const Pose& pose, bool ignore_collision);
		Pose simGetPose() const;
		bool simSetSegmentationObjectID(const std::string& mesh_name, int object_id, bool is_name_regex = false);
		int simGetSegmentationObjectID(const std::string& mesh_name) const;
		Pose simGetObjectPose(const std::string& object_name) const;

		//Car APIs
		void enableApiControl(bool is_enabled);
		bool isApiControlEnabled() const;
		void reset();
		void setCarControls(const CarControls& controls);
		CarState getCarState() const;
		const CarApiBase::CarControls& getCarControls() const;
		virtual bool armDisarm(bool arm) override;

		//Image Capture and Cameras
		vector<ImageCaptureBase::ImageResponse> simGetImages(const vector<ImageCaptureBase::ImageRequest>& request) const;
		vector<uint8_t> simGetImage(uint8_t camera_id, ImageCaptureBase::ImageType image_type) const;
		CameraInfo getCameraInfo(int camera_id) const;
		void setCameraOrientation(int camera_id, const Quaternionr& orientation);

		//Collision
		CollisionInfo getCollisionInfo() const;

		//Helper Functions
		void simPrintLogMessage(const std::string& message, const std::string& message_param = "", unsigned char severity = 0);

	private:
		int vehicleId; //vehicle index 
		std::unique_ptr<UnityImageCapture> image_capture_;
		bool is_api_control;
		CarControls car_controls;
	};
}