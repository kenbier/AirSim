# AirSim Unity port
Welcome to `AirSim` Unity port.

* [MSAirsim repository](https://github.com/Microsoft/AirSim)
* [Compatible MSAirsim revision](https://github.com/Microsoft/AirSim/tree/1da8e3b8c0dc055111319240fddd2ec2726cb8a7)

## Build & Usage 
* [Unity Airsim wrappler dll](AirLibWrapper/README.md)
* [Airsim Assets](AirSimAssets/README.md)
* [Car Demo](CarDemo/README.md)
* [Drone Demo](DroneDemo/README.md)

## MS Airsim folder
The `MSAirsim` folder contains a snapshot of [AirLib](https://github.com/Microsoft/AirSim) dependencies taken @ revision [1da8e3b8c0dc05](https://github.com/Microsoft/AirSim/tree/1da8e3b8c0dc055111319240fddd2ec2726cb8a7). This folder contains only the dependencies which are needed to compile `Unity Airsim wrapper dll`. 

If you want to build this `dll` against the [MSAirsim repository](https://github.com/Microsoft/AirSim), please checkout [MSAirsim repository](https://github.com/Microsoft/AirSim) into some folder on your system and modify `AirSimDir` user macro in [AirsimWrapper](AirLibWrapper/AirsimWrapper/AirsimWrapper.vcxproj) project configuration file.

The value of the user macro `AirSimDir` is configured to refer to [MSAirsim](MSAirsim) folder, which contains a snapshot of required dependencies as described above, for demonstration purpose.