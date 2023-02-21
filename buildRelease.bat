@ECHO OFF
call build.bat

if not exist release\ (
    mkdir release
)

powershell Compress-Archive -Force ^
    -Path ".\build\Client\r-type-client.exe,.\Client\assets,.\config" ^
    -DestinationPath ".\release\r-type-client.zip"

powershell Compress-Archive -Force ^
    -Path ".\build\Server\r-type-server.exe,.\config" ^
    -DestinationPath ".\release\r-type-server.zip"
