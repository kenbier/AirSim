#include "MultiRotorRpcLibServerWrapper.h"

MultiRotorRpcLibServerWrapper::MultiRotorRpcLibServerWrapper(int vId)
{
	initializeSettings();
	vehicleId = vId;
	vehicle_pawn = new VehiclePawnWrapper(vId);
	multirotorparams_uptr = MultiRotorParamsFactory::createConfig(vehicle_pawn->getVehicleConfigName(), std::make_shared<SensorFactory>());
	vehicle.initialize(multirotorparams_uptr.get(), vehicle_pawn->getPose(),GeoPoint(), environment);
	vehicle_connector = new MultiRotorConnectorUnity(vehicle_pawn, multirotorparams_uptr.get());
	vehicle_connector->setController(vehicle);
	vehicle_connector->getVehicle(vehicle);
	vehicle_api = new MultirotorApi(vehicle_connector);
	simmode_api = new DroneServerSimModeUnityApi(vehicle_api);
	vehicles = { &vehicle , vehicle_connector };
	if (vehicle_connector->getPhysicsBody() != nullptr)
	{
		vehicle_pawn->setKinematics(&(static_cast<PhysicsBody*>(vehicle_connector->getPhysicsBody())->getKinematics()));
	}
	physics_engine.reset(new FastPhysicsEngine());
}

MultiRotorRpcLibServerWrapper::~MultiRotorRpcLibServerWrapper()
{
	delete vehicle_pawn;
	delete vehicle_connector;
	delete vehicle_api;
}

void MultiRotorRpcLibServerWrapper::startmultirotorserver(std::string hostip, int port)
{
	std::vector<std::string> messages_;
	auto clock = std::make_shared<SteppableClock>(3E-3f);
	ClockFactory::get(clock);
	SensorFactory sensor_factory;
	physics_world_.reset(new msr::airlib::PhysicsWorld(physics_engine.get(), vehicles, static_cast<uint64_t>(clock->getStepSize() * 1E9)));
	rpclib_multirotor_server = new msr::airlib::MultirotorRpcLibServer(simmode_api, hostip, port);
	rpclib_multirotor_server->start();
}

void MultiRotorRpcLibServerWrapper::initializeSettings()
{
	std::string settingsText;
	if (getSettingsText(settingsText))
		AirSimSettings::initializeSettings(settingsText);
	else
		AirSimSettings::createDefaultSettingsFile();

	int warning_count = AirSimSettings::singleton().load([]() {return "Multirotor";});
	if (warning_count > 0)
	{
		//This would mean that settings.json is not configured well
	}
}

//reads settings from settings.json present in the Executable folder or User/Documents folder
//in the mentioned order.
bool MultiRotorRpcLibServerWrapper::getSettingsText(std::string& settingsText)
{
	return (readSettingsTextFromFile(Settings::getExecutableFullPath("settings.json").c_str(), settingsText) ||
		readSettingsTextFromFile(Settings::getUserDirectoryFullPath("settings.json").c_str(), settingsText));
}

bool MultiRotorRpcLibServerWrapper::readSettingsTextFromFile(std::string settingsFilepath, std::string& settingsText)
{
	std::ifstream t(settingsFilepath);
	if (!t.fail())
	{
		std::stringstream buffer;
		buffer << t.rdbuf();
		settingsText = buffer.str();
		return true;
	}
	return false;
}