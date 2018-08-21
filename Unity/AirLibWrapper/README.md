# Unity Airsim Wrapper plugin

This project is for generating the Wrapper dll `(AirsimWrapper.dll)` that can be used as a Unity plugin.

## Description 
1. `AirsimWrapper` - This is the wrapper project that is built using AirLib and generates `AirsimWrapper.dll` that can be used as a Unity plugin.
2. This wrapper acts as a bridge between `AirLib.lib` and the Unity project.
3. Interfaces from/to Unity are exposed by the wrapper using `PInvoke` methods.

## Prerequisites
You will need Visual Studio 2017 (make sure to install VC++) or newer to compile the project.

### Generate dll with snapshot of MSAirsim
To generate plugin dll using the snapshot of `Airsim` available in [MSAirsim](../MSAirsim) folder, follow the following steps. 

1. Open `AirsimWrapper.sln` solution file. This solution contains the project `AirsimWrapper`.
2. Build the solution in either Debug/Release with x64 configuration.
3. `AIrsimWrapper.dll` file will be generated in `x64/(Debug or Release)` folder. This will be used as a Unity plugin.

### Generate dll with your own copy of MSAirsim
To generate the plugin dll using your own copy of MSAirsim, follow the following steps.

1. Checkout [MSAirsim repository](https://github.com/Microsoft/AirSim) into a folder of your choice in your system.
2. Build `AirLib` by running `build.cmd` as described at [MS Airsim page](https://github.com/Microsoft/AirSim/blob/master/docs/build_windows.md#build-airsim). This will produce the required libraries in `AirLib` that are linked with Unity plugin dll.
3. Edit [AirsimWrapper](AirLibWrapper/AirsimWrapper/AirsimWrapper.vcxproj) project configuration file to set the value of user macro `AirSimDir` to refer to the folder into which MS Airsim project was checkedout.
```xml
<PropertyGroup Label="UserMacros">
    <AirSimDir>$(ProjectDir)..\..\..\..\MSAirsim</AirSimDir>
</PropertyGroup>
```
4. Follow the steps as given under `Generate dll with snapshot of MSAirsim` above.

## Usage
Copy/Replace the generated dll(AirsimWrapper.dll) to the `Plugins` folder in the Airsim Unity project.