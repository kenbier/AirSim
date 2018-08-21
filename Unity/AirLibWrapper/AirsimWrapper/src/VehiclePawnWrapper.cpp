#include "VehiclePawnWrapper.h"
#include "common/ClockFactory.hpp"
#include "common/AirSimSettings.hpp"
#include "common/EarthUtils.hpp"
#include "AirSimStructs.hpp"
#include "UnityImageCapture.h"
#include "PInvokeWrapper.h"

using namespace AirSimUnity;

namespace AirSimUnity
{
	VehiclePawnWrapper::VehiclePawnWrapper(int vId)
	{
		vehicleId = vId;
		image_capture_.reset(new UnityImageCapture(vehicleId));
		rotation_factor = 0.1f;
	}

	VehiclePawnWrapper::~VehiclePawnWrapper(){ }

	void VehiclePawnWrapper::initialize(const WrapperConfig& config)
	{
		typedef msr::airlib::AirSimSettings AirSimSettings;

		config_ = config;

		//compute our home point
		Vector3r nedWrtOrigin = getPose().position;
		home_point_ = msr::airlib::EarthUtils::nedToGeodetic(nedWrtOrigin, AirSimSettings::singleton().origin_geopoint);

		initial_state_.tracing_enabled = config.enable_trace;
		initial_state_.collisions_enabled = config.enable_collisions;
		initial_state_.passthrough_enabled = config.enable_passthrough_on_collisions;

		initial_state_.collision_info = CollisionInfo();

		initial_state_.was_last_move_teleport = false;
		initial_state_.was_last_move_teleport = canTeleportWhileMove();

		setupCamerasFromSettings();
	}

	void VehiclePawnWrapper::reset()
	{
		state_ = initial_state_;
	}

	void VehiclePawnWrapper::toggleTrace()
	{
		state_.tracing_enabled = !state_.tracing_enabled;
	}

	UnityImageCapture* VehiclePawnWrapper::getImageCapture()
	{
		return image_capture_.get();
	}

	msr::airlib::CameraInfo VehiclePawnWrapper::getCameraInfo(int camera_id) const
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

	void VehiclePawnWrapper::setCameraOrientation(int camera_id, const msr::airlib::Quaternionr& orientation)
	{
		AirSimQuaternion airsim_orientation;
		airsim_orientation.x = orientation.x();
		airsim_orientation.x = orientation.y();
		airsim_orientation.x = orientation.z();
		airsim_orientation.x = orientation.w();
		SetCameraOrientation(camera_id, airsim_orientation, vehicleId); // Into Unity
	}

	VehiclePawnWrapper::Pose VehiclePawnWrapper::getPose() const
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

	void VehiclePawnWrapper::setPose(const Pose& pose, bool ignore_collision)
	{
		SetPose(pose, true, vehicleId); // Into Unity
	}

	const VehiclePawnWrapper::GeoPoint& VehiclePawnWrapper::getHomePoint() const
	{
		return home_point_;
	}

	msr::airlib::Pose VehiclePawnWrapper::getActorPose(std::string actor_name)
	{
		return getPose();
	}

	msr::airlib::RCData VehiclePawnWrapper::getRCData()
	{
		AirSimRCData airsimdata = GetRCData(vehicleId); // Into Unity
		msr::airlib::RCData data;
		data.timestamp = airsimdata.timestamp;
		data.pitch = airsimdata.pitch;
		data.roll = airsimdata.roll;
		data.throttle = airsimdata.throttle;
		data.yaw = airsimdata.yaw;
		data.switch1 = airsimdata.switch1;
		data.switch2 = airsimdata.switch2;
		data.switch3 = airsimdata.switch3;
		data.switch4 = airsimdata.switch4;
		data.switch5 = airsimdata.switch5;
		data.switch6 = airsimdata.switch6;
		data.switch6 = airsimdata.switch6;
		data.switch7 = airsimdata.switch7;
		data.switch8 = airsimdata.switch8;
		data.is_initialized = airsimdata.is_initialized;
		data.is_valid = airsimdata.is_valid;
		return data;
	}

	int VehiclePawnWrapper::getRemoteControlID() const
	{
		typedef msr::airlib::AirSimSettings AirSimSettings;

		//find out which RC we should use
		AirSimSettings::VehicleSettings vehicle_settings =
			AirSimSettings::singleton().getVehicleSettings(getVehicleConfigName());

		msr::airlib::Settings settings;
		vehicle_settings.getRawSettings(settings);

		msr::airlib::Settings rc_settings;
		settings.getChild("RC", rc_settings);
		return rc_settings.getInt("RemoteControlID", -1);
	}

	void VehiclePawnWrapper::setKinematics(const msr::airlib::Kinematics::State* kinematics)
	{
		kinematics_ = kinematics;
	}

	const msr::airlib::Kinematics::State* VehiclePawnWrapper::getTrueKinematics()
	{
		return kinematics_;
	}

	VehiclePawnWrapper::CollisionInfo& VehiclePawnWrapper::getCollisionInfo()
	{
		AirSimCollisionInfo temp = GetCollisionInfo(vehicleId); // Into Unity
		state_.collision_info.has_collided = temp.has_collided;
		state_.collision_info.normal.x() = temp.normal.x;
		state_.collision_info.normal.y() = temp.normal.y;
		state_.collision_info.normal.z() = temp.normal.z;
		state_.collision_info.impact_point.x() = temp.impact_point.x;
		state_.collision_info.impact_point.y() = temp.impact_point.y;
		state_.collision_info.impact_point.z() = temp.impact_point.z;
		state_.collision_info.position.x() = temp.position.x;
		state_.collision_info.position.y() = temp.position.y;
		state_.collision_info.position.z() = temp.position.z;
		state_.collision_info.penetration_depth = temp.penetration_depth;
		state_.collision_info.time_stamp = temp.time_stamp;
		state_.collision_info.collision_count = temp.collision_count;
		state_.collision_info.object_name = temp.object_name;
		state_.collision_info.object_id = temp.object_id;
		return state_.collision_info;
	}

	VehiclePawnWrapper::WrapperConfig& VehiclePawnWrapper::getConfig()
	{
		return config_;
	}

	const VehiclePawnWrapper::WrapperConfig& VehiclePawnWrapper::getConfig() const
	{
		return config_;
	}

	std::string VehiclePawnWrapper::getVehicleConfigName() const
	{
		return getConfig().vehicle_config_name == "" ? msr::airlib::AirSimSettings::singleton().default_vehicle_config
			: getConfig().vehicle_config_name;
	}

	void VehiclePawnWrapper::getRawVehicleSettings(msr::airlib::Settings& settings) const
	{
		typedef msr::airlib::AirSimSettings AirSimSettings;
		//find out which RC we should use
		AirSimSettings::VehicleSettings vehicle_settings = AirSimSettings::singleton().getVehicleSettings(this->getVehicleConfigName());
		vehicle_settings.getRawSettings(settings);
	}

	void VehiclePawnWrapper::setRotorSpeed(int rotor_index, RotorInfo rotor_info)
	{
		SetRotorSpeed(rotor_index, rotor_info, vehicleId); // Into Unity
	}

	void VehiclePawnWrapper::printLogMessage(const std::string& message, const std::string& message_param, unsigned char severity)
	{
		PrintLogMessage(message.c_str(), message_param.c_str(), (int)severity, vehicleId);
	}

	//private method
	bool VehiclePawnWrapper::canTeleportWhileMove()  const
	{
		return !state_.collisions_enabled || (state_.collision_info.has_collided && !state_.was_last_move_teleport && state_.passthrough_enabled);
	}

	//private method
	void VehiclePawnWrapper::allowPassthroughToggleInput()
	{
		state_.passthrough_enabled = !state_.passthrough_enabled;
	}

	//private method
	void VehiclePawnWrapper::setupCamerasFromSettings()
	{
		typedef msr::airlib::Settings Settings;
		typedef msr::airlib::ImageCaptureBase::ImageType ImageType;
		typedef msr::airlib::AirSimSettings AirSimSettings;

		int image_count = static_cast<int>(Utils::toNumeric(ImageType::Count));
	}
}