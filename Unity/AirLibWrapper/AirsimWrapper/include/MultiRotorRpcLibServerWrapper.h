#pragma once

#include "vehicles\multirotor\api\MultirotorRpcLibServer.hpp"
#include "MultiRotorConnectorUnity.h"
#include "vehicles\multirotor\api\MultirotorApi.hpp"
#include "vehicles\multirotor\MultiRotorParamsFactory.hpp"
#include "physics\PhysicsWorld.hpp"
#include "physics\FastPhysicsEngine.hpp"
#include "common\SteppableClock.hpp"
#include "DroneServerSimModeUnityApi.h"

/*
* Defines the entry point for creating a drone Server.
*/

class MultiRotorRpcLibServerWrapper
{
public:
	void initializeSettings();
	bool getSettingsText(std::string& settingsText);
	bool readSettingsTextFromFile(std::string settingsFilepath, std::string& settingsText);
	void startmultirotorserver(std::string hostip = "localhost", int port = 41451);
	MultirotorRpcLibServer* rpclib_multirotor_server;
	MultiRotorRpcLibServerWrapper(int);
	~MultiRotorRpcLibServerWrapper();
private:
	int vehicleId;	
	std::unique_ptr<MultiRotorParams> multirotorparams_uptr;
	VehiclePawnWrapper* vehicle_pawn;
	MultiRotorConnectorUnity* vehicle_connector;
	MultirotorApi* vehicle_api;
	DroneServerSimModeUnityApi* simmode_api;
	MultiRotor vehicle;
	std::vector<UpdatableObject*> vehicles;
	std::unique_ptr<PhysicsEngineBase> physics_engine;
	std::unique_ptr<msr::airlib::PhysicsWorld> physics_world_;
	std::unique_ptr<Environment> environment;
};


static std::map<int, MultiRotorRpcLibServerWrapper*> multiRotors; //map to track drone based on the vehicle index

//Method on which drone server thread is invoked
void StartDroneServerThread(int vehicleId, std::string hostIp,int portNum)
{
	MultiRotorRpcLibServerWrapper* server_wrapper = new MultiRotorRpcLibServerWrapper(vehicleId);
	server_wrapper->startmultirotorserver(hostIp, portNum);
	multiRotors[vehicleId] = server_wrapper;
}

//Corresponding Import methods are called in Unity
extern "C" __declspec(dllexport) void StartDroneServer(char* hostIp, int port, int vehicleId)
{
	std::string ipaddress = hostIp;
	std::thread server_thread(StartDroneServerThread, vehicleId, ipaddress,port);
	server_thread.detach();
}

extern "C" __declspec(dllexport) void StopDroneServer(int vehicleId)
{
	MultiRotorRpcLibServerWrapper* serverWrapper = multiRotors[vehicleId];
	serverWrapper->rpclib_multirotor_server->stop();
	multiRotors.erase(vehicleId);
	delete serverWrapper->rpclib_multirotor_server;
	delete serverWrapper;
}