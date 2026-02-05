@echo off
call "c:\Program Files (x86)\Intel\oneAPI\setvars.bat" >nul 2>&1
"c:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe" "c:\Users\anuvc\Documents\Code\Workspace\synth\vital\standalone\builds\vs19\Vial.sln" /t:Build /p:Configuration=Debug /p:Platform=x64 /verbosity:minimal /m
exit /b %ERRORLEVEL%
