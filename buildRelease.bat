@ECHO OFF
call build.bat

if not exist release\ (
    mkdir releaseWindows
)

powershell Compress-Archive -Force ^
    -Path ".\build\Client\r-type-client.exe,.\Client\assets,.\config" ^
    -DestinationPath ".\releaseWindows\r-type-client.zip"

powershell Compress-Archive -Force ^
    -Path ".\build\Server\r-type-server.exe,.\config" ^
    -DestinationPath ".\releaseWindows\r-type-server.zip"

powershell Compress-Archive -Force ^
    -Path ".\build\Pong\pong.exe,.\Pong\assets" ^
    -DestinationPath ".\releaseWindows\ponge.zip"
