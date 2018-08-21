using AirSimUnity.DroneStructs;

namespace AirSimUnity {
    /*
     * Contract to be implemented by Unity's vehicle.
     */

    public interface IVehicleInterface {

        bool SetPose(AirSimPose pose, bool ignoreCollision);

        AirSimPose GetPose();

        CollisionInfo GetCollisionInfo();

        AirSimRCData GetRCData();

        ImageResponse GetSimImages(ImageRequest request);

        bool SetRotorSpeed(int rotorIndex, RotorInfo rotorInfo);

        bool SetCarControls(CarStructs.CarControls controls);

        CarStructs.CarState GetCarState();

        bool SetEnableApi(bool enableApi);

        DataRecorder.ImageData GetRecordingData();

        DataCaptureScript GetCameraCapture(int cameraId);

        CameraInfo GetCameraInfo(int cameraId);

        bool SetCameraOrientation(int cameraId, AirSimQuaternion orientation);

        bool PrintLogMessage(string message, string messageParams, int severity);
    }
}