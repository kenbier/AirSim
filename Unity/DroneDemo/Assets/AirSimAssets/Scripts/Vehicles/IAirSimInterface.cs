
namespace AirSimUnity
{
    /**
     * An interface to Unity client into AirLib wrapper.
     */
    public interface IAirSimInterface
    {
        void StartVehicleServer(string hostIP);

        void StopVehicleServer();

        KinemticState GetKinemticState();
    }
}
