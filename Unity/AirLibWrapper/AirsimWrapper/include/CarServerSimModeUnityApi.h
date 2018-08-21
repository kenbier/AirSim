#pragma once

#include "api/SimModeApiBase.hpp"
#include"vehicles/car/api/CarApiBase.hpp"

class CarServerSimModeUnityApi : public msr::airlib::SimModeApiBase
{
public:
	CarServerSimModeUnityApi(CarApiBase* api)
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
	CarApiBase* api_;
};