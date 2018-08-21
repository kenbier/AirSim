#pragma once

#include <vector>
#include <memory>
#include "UnityImageCapture.h"
#include "common/Common.hpp"
#include "common/CommonStructs.hpp"
#include "physics/Kinematics.hpp"
#include "common/AirSimSettings.hpp"
#include "vehicles/multirotor/controllers/DroneCommon.hpp"
#include "AirSimStructs.hpp"

using namespace AirSimUnity;

/*
* Drone implementation.
* This implements all the necessary API's related to drone simulation provided by AirLib.
* PInvoke methods are used to communicate to the Unity layer.
*/

namespace AirSimUnity
{
	class VehiclePawnWrapper
	{
	public:
		//types
		typedef msr::airlib::GeoPoint GeoPoint;
		typedef msr::airlib::Vector3r Vector3r;
		typedef msr::airlib::Pose Pose;
		typedef msr::airlib::Quaternionr Quaternionr;
		typedef msr::airlib::CollisionInfo CollisionInfo;
		typedef msr::airlib::VectorMath VectorMath;
		typedef msr::airlib::real_T real_T;
		typedef msr::airlib::Utils Utils;

		struct WrapperConfig
		{
			bool is_fpv_vehicle;
			std::string vehicle_config_name;
			bool enable_collisions;
			bool enable_passthrough_on_collisions;
			bool enable_trace;
			WrapperConfig() :
				is_fpv_vehicle(false),
				vehicle_config_name(""), //use the default config name
				enable_collisions(true),
				enable_passthrough_on_collisions(false),
				enable_trace(false)
			{}
		};

		//ctor and dtor
		VehiclePawnWrapper(int);
		~VehiclePawnWrapper();

		//Drone APIs
		void initialize(const WrapperConfig& config = WrapperConfig());
		void reset();
		void toggleTrace();

		//Image Capture and cameras
		UnityImageCapture* getImageCapture();
		msr::airlib::CameraInfo getCameraInfo(int camera_id) const;
		void setCameraOrientation(int camera_id, const Quaternionr& orientation);
		
		//Poses
		Pose getPose() const;
		void setPose(const Pose& pose, bool ignore_collision);
		const GeoPoint& getHomePoint() const;
		msr::airlib::Pose getActorPose(std::string actor_name);

		//Remote Control Data
		msr::airlib::RCData getRCData();
		int getRemoteControlID() const;

		//Kinematics
		void setKinematics(const msr::airlib::Kinematics::State* kinematics);
		const msr::airlib::Kinematics::State* getTrueKinematics();

		//collision
		CollisionInfo& getCollisionInfo();
	
		//Wrapper Config
		WrapperConfig& getConfig();
		const WrapperConfig& getConfig() const;
		std::string getVehicleConfigName() const;
		void getRawVehicleSettings(msr::airlib::Settings& settings) const;

		//Rotors
		void setRotorSpeed(int rotor_index, RotorInfo rotor_info);

		//Helpers
		void printLogMessage(const std::string& message, const std::string& message_param = "", unsigned char severity = 0);
		
	private:
		int vehicleId;   //vehicle index
		bool canTeleportWhileMove()  const;
		void allowPassthroughToggleInput();
		void setupCamerasFromSettings();
		GeoPoint home_point_;
		std::unique_ptr<UnityImageCapture> image_capture_;
		const msr::airlib::Kinematics::State* kinematics_;
		WrapperConfig config_;
		float rotation_factor;
		struct State
		{
			bool tracing_enabled;
			bool collisions_enabled;
			bool passthrough_enabled;
			bool was_last_move_teleport;
			CollisionInfo collision_info;
		};
		State state_, initial_state_;
	};
}