#include "CarRpcLibServerWrapper.h"
#include "vehicles/car/api/CarRpcLibServer.hpp"
#include "rpc/server.h"
#include "vehicles/car/api/CarRpcLibAdapators.hpp"
#include "common/AirSimSettings.hpp"

CarRpcLibServerWrapper::CarRpcLibServerWrapper(int vId)
{
	vehicleId = vId;
	carpawn = new CarPawnUnity(vehicleId);
	simmode_api = new CarServerSimModeUnityApi(carpawn);
}

CarRpcLibServerWrapper::~CarRpcLibServerWrapper()
{
	delete carpawn;
}

void CarRpcLibServerWrapper::startCarServer(std::string hostip, int port)
{
	rpclib_car_server = new msr::airlib::CarRpcLibServer(simmode_api, hostip, port);
	rpclib_car_server->start();
}
