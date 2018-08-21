#include "MultiRotorConnectorUnity.h"
#include "vehicles/multirotor/api/MultirotorRpcLibServer.hpp"
#include "common/AirSimSettings.hpp"
#include "vehicles/multirotor/controllers/DroneCommon.hpp"
#include "PInvokeWrapper.h"

using namespace msr::airlib;

namespace AirSimUnity
{
	MultiRotorConnectorUnity::MultiRotorConnectorUnity(VehiclePawnWrapper* vehicle_pawn_wrapper, MultiRotorParams* vehicle_params)
	{
		vehicle_pawn_wrapper_ = vehicle_pawn_wrapper;
		vehicle_params_ = vehicle_params;
		vehicle_ptr = nullptr;
		rotor_count_ = 0;
		last_pose = vehicle_pawn_wrapper->getPose();
		is_first_collision = true;
		is_api_enable_checked = false;
	}

	MultiRotorConnectorUnity::~MultiRotorConnectorUnity()
	{

	}

	// Not used - Update calls are handled by Unity
	void MultiRotorConnectorUnity::updateRenderedState(float dt)
	{

	}

	// Not used - Update calls are handled by Unity
	void MultiRotorConnectorUnity::updateRendering(float dt)
	{

	}

	//Not used : Server Wrapper classes start the server
	void MultiRotorConnectorUnity::startApiServer()
	{

	}

	//Not used : Server Wrapper classes stop the server
	void MultiRotorConnectorUnity::stopApiServer()
	{

	}

	bool MultiRotorConnectorUnity::isApiServerStarted()
	{
		return controller_ptr->isApiControlEnabled();
	}

	VehicleControllerBase* MultiRotorConnectorUnity::getController()
	{
		return static_cast<DroneControllerBase*>(controller_ptr);
	}

	ImageCaptureBase* MultiRotorConnectorUnity::getImageCapture()
	{
		return vehicle_pawn_wrapper_->getImageCapture();
	}

	void MultiRotorConnectorUnity::setPose(const Pose& pose, bool ignore_collision)
	{
		vehicle_pawn_wrapper_->setPose(pose, ignore_collision);
	}

	Pose MultiRotorConnectorUnity::getPose()
	{
		return vehicle_pawn_wrapper_->getPose();
	}

	bool MultiRotorConnectorUnity::setSegmentationObjectID(const std::string& mesh_name, int object_id, bool is_name_regex)
	{
		return SetSegmentationObjectId(mesh_name.c_str(), object_id, is_name_regex);
	}
	int MultiRotorConnectorUnity::getSegmentationObjectID(const std::string& mesh_name)
	{
		return GetSegmentationObjectId(mesh_name.c_str());
	}

	void MultiRotorConnectorUnity::printLogMessage(const std::string& message, std::string message_param, unsigned char severity)
	{
		vehicle_pawn_wrapper_->printLogMessage(message, message_param, severity);
	}

	Pose MultiRotorConnectorUnity::getActorPose(const std::string& actor_name)
	{
		return vehicle_pawn_wrapper_->getActorPose(actor_name);
	}

	Kinematics::State MultiRotorConnectorUnity::getTrueKinematics()
	{
		return *vehicle_pawn_wrapper_->getTrueKinematics();
	}

	CameraInfo MultiRotorConnectorUnity::getCameraInfo(int camera_id) const
	{
		return vehicle_pawn_wrapper_->getCameraInfo(camera_id);
	}

	void MultiRotorConnectorUnity::setCameraOrientation(int camera_id, const Quaternionr& orientation)
	{
		vehicle_pawn_wrapper_->setCameraOrientation(camera_id, orientation);
	}

	void MultiRotorConnectorUnity::setController(MultiRotor &vehicle)
	{
		controller_ptr = static_cast<DroneControllerBase*>(vehicle.getController());
	}

	void MultiRotorConnectorUnity::getVehicle(MultiRotor &vehicle)
	{
		vehicle_ptr = &vehicle;
		// set the rotor info when the vehicle is assigned
		if (vehicle_ptr)
		{
			rotor_count_ = vehicle_ptr->wrenchVertexCount();
			rotor_info_.assign(rotor_count_, RotorInfo());
		}
	}

	//FastPhysicsEngine calls this update method
	void MultiRotorConnectorUnity::update()
	{
		if (vehicle_pawn_wrapper_)
		{
			CollisionInfo collision_info = vehicle_pawn_wrapper_->getCollisionInfo();
			vehicle_ptr->setCollisionInfo(collision_info);
			if (vehicle_pawn_wrapper_->getRemoteControlID() >= 0)
			{
				msr::airlib::RCData data = vehicle_pawn_wrapper_->getRCData();
				controller_ptr->setRCData(data);
			}
			setPose(vehicle_ptr->getPose(), true);
			//update rotor poses
			if (vehicle_ptr)
			{
				for (unsigned int i = 0; i < rotor_count_; ++i)
				{
					msr::airlib::Rotor::Output rotor_output = vehicle_ptr->getRotorOutput(i);
					RotorInfo* info = &rotor_info_[i];
					info->rotor_speed = rotor_output.speed;
					info->rotor_direction = static_cast<int>(rotor_output.turning_direction);
					info->rotor_thrust = rotor_output.thrust;
					info->rotor_control_filtered = rotor_output.control_signal_filtered;
					vehicle_pawn_wrapper_->setRotorSpeed(i, rotor_info_[i]);
				}
			}
		}
	}
}


