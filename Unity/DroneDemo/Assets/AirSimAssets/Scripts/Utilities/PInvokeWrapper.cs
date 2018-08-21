using System;
using System.Runtime.InteropServices;

namespace AirSimUnity {
    /*
     * class for all the PInvoke methods.
     */

    public static class PInvokeWrapper {
        private const string DLL_NAME = "AirsimWrapper";

        // Delegates initializer. All the delegate methods are registered through this PInvoke call
        [DllImport(DLL_NAME)]
        public static extern void InitVehicleManager(IntPtr SetPos, IntPtr GetPos, IntPtr GetCollisionInfo, IntPtr GetRCData,
            IntPtr GetSimImages, IntPtr SetDroneSpeed, IntPtr SetEnableApi, IntPtr SetCarControls, IntPtr GetCarState,
            IntPtr GetCameraInfo, IntPtr SetCameraOrientation, IntPtr SetSegmentationObjectid, IntPtr GetSegmentationObjectId, IntPtr PrintLogMessage);

        [DllImport(DLL_NAME)]
        public static extern KinemticState GetKinematicState(int vehicleId);

        [DllImport(DLL_NAME)]
        public static extern void StartDroneServer(string ip, int port, int vehicleId);

        [DllImport(DLL_NAME)]
        public static extern void StopDroneServer(int vehicleId);

        [DllImport(DLL_NAME)]
        public static extern void StartCarServer(string ip, int port, int vehicleId);

        [DllImport(DLL_NAME)]
        public static extern void StopCarServer(int vehicleId);
    }
}