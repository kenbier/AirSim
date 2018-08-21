#pragma once

#include "vehicles/car/api/CarRpcLibServer.hpp"
#include "CarPawnUnity.h"
#include "CarServerSimModeUnityApi.h"
#include <map>
/*
* Defines the Entry point for creating a Car Server.
*/
class CarRpcLibServerWrapper
{
public:
	CarRpcLibServerWrapper(int);
	~CarRpcLibServerWrapper();
	void startCarServer(std::string hostip = "localhost", int port = 42451);
	CarRpcLibServer* rpclib_car_server;
	CarServerSimModeUnityApi* simmode_api;
private:
	int vehicleId;
	CarPawnUnity* carpawn;
};

static std::map<int,CarRpcLibServerWrapper*> cars;   //map to track cars based on the vehicle index

//Method on which car server thread is invoked
void StartCarServerThread(int vehicleId, std::string hostIp, int portNum)
{
	CarRpcLibServerWrapper* server_wrapper = new CarRpcLibServerWrapper(vehicleId);
	server_wrapper->startCarServer(hostIp, portNum);
	cars[vehicleId] = server_wrapper;
}

//Corresponding Import methods are declared and called in Unity
extern "C"  __declspec(dllexport) void StartCarServer(char* ip, int port, int vehicleId)
{
	std::string ipaddress = ip;
	std::thread server_thread(StartCarServerThread, vehicleId, ipaddress, port);
	server_thread.detach();
}

extern "C" __declspec(dllexport) void StopCarServer(int vehicleId)
{
	CarRpcLibServerWrapper* serverWrapper = cars[vehicleId];
	serverWrapper->rpclib_car_server->stop();
	cars.erase(vehicleId);
	delete serverWrapper->rpclib_car_server;
	delete serverWrapper;
}