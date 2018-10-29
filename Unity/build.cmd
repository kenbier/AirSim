REM //---------- copy binaries and include for MavLinkCom in deps ----------
msbuild AirLibWrapper\AirsimWrapper.sln  /target:Clean /target:Build  /property:Configuration=Release /property:Platform=x64
if ERRORLEVEL 1 goto :buildfailed
robocopy AirLibWrapper\x64\Release\AirsimWrapper.dll  UnityDemo\Assets\Plugins

REM // Download high poly drone asset
REM // TODO 
 

REM //---------- done building ----------
exit /b 0

:buildfailed
echo(
echo #### Build failed - see messages above. 1>&2