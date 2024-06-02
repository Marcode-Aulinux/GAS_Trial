@REM  Get the process location
SET mypath=%~dp0
echo %mypath:~0,-1%

@REM Read first parameter which is a source
set src=%1
@REM Read second parameter which is the location where to output built Project
set dest=%2

echo  %arg1% %arg2%

@REM All a UAT tool provided by Unreal which builds a Win64 Project
@REM And output its at the destination
RunUAT BuildCookRun -project="%mypath:~0,-1%/%src%" -platform=Win64 -clientconfig=DebugGame -build -cook -stage -archive -archivedirectory="%mypath:~0,-1%/%dest%"

@REM Zip the build into a publish.zip file
cd "%mypath:~0,-1%/%dest%"
powershell Compress-Archive . publish.zip