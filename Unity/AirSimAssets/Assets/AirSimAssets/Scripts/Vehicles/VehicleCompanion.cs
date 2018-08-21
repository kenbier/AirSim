using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AirSimUnity.DroneStructs;
using AirSimUnity.CarStructs;
using UnityEngine;

namespace AirSimUnity {
    /*
     * An implementation of IAirSimInterface, facilitating calls from Unity to AirLib.
     * And also a bridge for the calls originating from AirLib into Unity.
     *
     * Unity client components should use an instance of this class to interact with AirLib.
     */

    internal class VehicleCompanion : IAirSimInterface {

        //All the vehicles that are created in this game.
        private static List<VehicleCompanion> Vehicles = new List<VehicleCompanion>();

        private static int basePortId;

        //An interface to interact with Unity vehicle component.
        private IVehicleInterface VehicleInterface;

        private int vehicleId;
        private readonly bool isDrone;

        static VehicleCompanion() {
            InitDelagators();
        }

        private VehicleCompanion(IVehicleInterface vehicleInterface) {
            VehicleInterface = vehicleInterface;
            isDrone = vehicleInterface is Drone ? true : false;
            basePortId = AirSimSettings.GetSettings().GetPortIDForVehicle(isDrone);
        }

        public static VehicleCompanion GetVehicleCompanion(IVehicleInterface vehicleInterface) {
            var companion = new VehicleCompanion(vehicleInterface);
            Vehicles.Add(companion);
            companion.vehicleId = Vehicles.Count - 1;

            return companion;
        }

        public void StartVehicleServer(string hostIP) {
            if (isDrone) {
                PInvokeWrapper.StartDroneServer(hostIP, basePortId + vehicleId, vehicleId);
            } else {
                PInvokeWrapper.StartCarServer(hostIP, basePortId + vehicleId, vehicleId);
            }
        }

        public void StopVehicleServer() {
            if (isDrone) {
                PInvokeWrapper.StopDroneServer(vehicleId);
            } else {
                PInvokeWrapper.StopCarServer(vehicleId);
            }
        }

        public KinemticState GetKinemticState() {
            return PInvokeWrapper.GetKinematicState(vehicleId);
        }

        public static DataRecorder.ImageData GetRecordingData() {
            return Vehicles[0].VehicleInterface.GetRecordingData();
        }

        public static DataCaptureScript GetCameraCaptureForRecording() {
            AirSimSettings.CamerasSettings recordCamSettings = AirSimSettings.GetSettings().Recording.Cameras[0];
            DataCaptureScript recordCam = Vehicles[0].VehicleInterface.GetCameraCapture(recordCamSettings.CameraID);
            return recordCam;
        }

        //Register the delegate functions to AirLib, based on IVehicleInterface
        private static void InitDelagators() {
            PInvokeWrapper.InitVehicleManager(
                Marshal.GetFunctionPointerForDelegate(new Func<AirSimPose, bool, int, bool>(SetPose)),
                Marshal.GetFunctionPointerForDelegate(new Func<int, AirSimPose>(GetPose)),
                Marshal.GetFunctionPointerForDelegate(new Func<int, CollisionInfo>(GetCollisionInfo)),
                Marshal.GetFunctionPointerForDelegate(new Func<int, AirSimRCData>(GetRCData)),
                Marshal.GetFunctionPointerForDelegate(new Func<ImageRequest, int, ImageResponse>(GetSimImages)),
                Marshal.GetFunctionPointerForDelegate(new Func<int, RotorInfo, int, bool>(SetRotorSpeed)),
                Marshal.GetFunctionPointerForDelegate(new Func<bool, int, bool>(SetEnableApi)),
                Marshal.GetFunctionPointerForDelegate(new Func<CarControls, int, bool>(SetCarControls)),
                Marshal.GetFunctionPointerForDelegate(new Func<int, CarState>(GetCarState)),
                Marshal.GetFunctionPointerForDelegate(new Func<int, int, CameraInfo>(GetCameraInfo)),
                Marshal.GetFunctionPointerForDelegate(new Func<int, AirSimQuaternion, int, bool>(SetCameraOrientation)),
                Marshal.GetFunctionPointerForDelegate(new Func<string, int, bool, bool>(SetSegmentationObjectId)),
                Marshal.GetFunctionPointerForDelegate(new Func<string, int>(GetSegmentationObjectId)),
                Marshal.GetFunctionPointerForDelegate(new Func<string, string, int, int, bool>(PrintLogMessage))
            );
        }

        /*********************** Delegate functions to be registered with AirLib *****************************/

        private static bool SetPose(AirSimPose pose, bool ignoreCollision, int vehicleId) {
            Vehicles[vehicleId].VehicleInterface.SetPose(pose, ignoreCollision);
            return true;
        }

        private static AirSimPose GetPose(int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.GetPose();
        }

        private static CollisionInfo GetCollisionInfo(int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.GetCollisionInfo();
        }

        private static AirSimRCData GetRCData(int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.GetRCData();
        }

        private static ImageResponse GetSimImages(ImageRequest request, int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.GetSimImages(request);
        }

        private static bool SetRotorSpeed(int rotorIndex, RotorInfo rotorInfo, int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.SetRotorSpeed(rotorIndex, rotorInfo);
        }

        private static bool SetEnableApi(bool enableApi, int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.SetEnableApi(enableApi);
        }

        private static bool SetCarControls(CarControls controls, int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.SetCarControls(controls);
        }

        private static CarState GetCarState(int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.GetCarState();
        }

        private static CameraInfo GetCameraInfo(int cameraId, int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.GetCameraInfo(cameraId);
        }

        private static bool SetCameraOrientation(int cameraId, AirSimQuaternion orientation, int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.SetCameraOrientation(cameraId, orientation);
        }

        private static bool PrintLogMessage(string message, string messageParams, int severity, int vehicleId) {
            return Vehicles[vehicleId].VehicleInterface.PrintLogMessage(message, messageParams, severity);
        }

        private static bool SetSegmentationObjectId(string objectName, int objectId, bool isNameRejex) {
            return Vehicle.SetSegmentationObjectId(objectName, objectId, isNameRejex);
        }

        private static int GetSegmentationObjectId(string objectName) {
            return Vehicle.GetSegmentationObjectId(objectName);
        }
    }
}