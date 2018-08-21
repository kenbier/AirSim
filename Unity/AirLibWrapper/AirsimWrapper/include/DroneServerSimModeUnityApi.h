#pragma once

#include "api/SimModeApiBase.hpp"
#include "vehicles\multirotor\api\MultirotorApi.hpp"

class DroneServerSimModeUnityApi : public msr::airlib::SimModeApiBase
{
public:
	DroneServerSimModeUnityApi(MultirotorApi* api)
		: api_(api)
	{

	}
	virtual VehicleApiBase* getVehicleApi() override
	{
		return api_;
	}
	virtual void reset() override
	{
		api_->reset();
	}
	virtual bool isPaused() const override
	{
		return false;
	}
	virtual void pause(bool is_paused) override
	{

	}
	virtual void continueForTime(double seconds) override
	{
	}
private:
	MultirotorApi * api_;
};