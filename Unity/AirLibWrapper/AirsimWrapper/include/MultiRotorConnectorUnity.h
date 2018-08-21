#pragma once

#include "controllers/VehicleConnectorBase.hpp"
#include "vehicles/multirotor/MultiRotorParams.hpp"
#include "vehicles/multirotor/api/MultirotorApi.hpp"
#include "vehicles/multirotor/MultiRotor.hpp"
#include "api/ApiServerBase.hpp"
#include "VehiclePawnWrapper.h"
#include "vehicles/multirotor/firmwares/simple_flight/SimpleFlightDroneController.hpp"
#include "common/CommonStructs.hpp"
#include "AirSimStructs.hpp"

using namespace AirSimUnity;
/*
* Implements the VehicleConnectorBase interface which is defined in AirLib
*/
namespace AirSimUnity
{
	class MultiRotorConnectorUnity : public msr::airlib::VehicleConnectorBase
	{
	public:
		MultiRotorConnectorUnity(VehiclePawnWrapper* vehicle_pawn_wrapper, MultiRotorParams* vehicle_params);
		~MultiRotorConnectorUnity();
		virtual void updateRenderedState(float dt);
		virtual void updateRendering(float dt);

		//opens up channel to talk to vehicle via APIs
		virtual void startApiServer() ;
		virtual void stopApiServer() ;
		virtual bool isApiServerStarted() ;
		virtual VehicleControllerBase* getController() override;
		virtual ImageCaptureBase* getImageCapture() override;
		virtual void setPose(const Pose& pose, bool ignore_collision) override;
		virtual Pose getPose() override;
		virtual bool setSegmentationObjectID(const std::string& mesh_name, int object_id, bool is_name_regex = false) override;
		virtual int getSegmentationObjectID(const std::string& mesh_name) override;
		virtual void printLogMessage(const std::string& message, std::string message_param = "", unsigned char severity = 0) override;
		virtual Pose getActorPose(const std::string& actor_name) override;
		virtual Kinematics::State getTrueKinematics() override;
		virtual CameraInfo getCameraInfo(int camera_id) const override;
		virtual void setCameraOrientation(int camera_id, const Quaternionr& orientation) override;
		virtual void setController(MultiRotor &vehicle);
		virtual void update() override;
		virtual void getVehicle(MultiRotor &vehicle);
	private:
		bool is_first_collision;
		bool is_api_enable_checked;
		Pose last_pose;
		MultiRotor *vehicle_ptr;
		VehiclePawnWrapper* vehicle_pawn_wrapper_;
		MultiRotorParams* vehicle_params_;
		msr::airlib::DroneControllerBase* controller_ptr;
		std::vector<RotorInfo> rotor_info_;
		unsigned int rotor_count_;
	};
}
 