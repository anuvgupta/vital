@echo off
setlocal enabledelayedexpansion

:: build_windows.bat - Build Vital synthesizer on Windows
:: Usage: build_windows.bat [options]
::
:: Options:
::   --config=Debug|Release  Build configuration (default: Debug)
::   --skip-regenerate       Skip VS project regeneration (faster builds)
::   --no-run                Build only, don't launch the app
::   --clean                 Clean build before building
::   --help                  Show this help message

:: Default values
set "CONFIG=Debug"
set "REGENERATE=1"
set "RUN_APP=1"
set "CLEAN_BUILD=0"

set "SCRIPT_DIR=%~dp0"
set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"
set "JUCER_FILE=%SCRIPT_DIR%\standalone\vital.jucer"
set "SLN_FILE=%SCRIPT_DIR%\standalone\builds\vs19\Vial.sln"

:: Parse arguments
:parse_args
if "%~1"=="" goto done_args
if /i "%~1"=="--help" goto show_help
if /i "%~1"=="-h" goto show_help
if /i "%~1"=="--skip-regenerate" (
    set "REGENERATE=0"
    shift
    goto parse_args
)
if /i "%~1"=="--no-run" (
    set "RUN_APP=0"
    shift
    goto parse_args
)
if /i "%~1"=="--clean" (
    set "CLEAN_BUILD=1"
    shift
    goto parse_args
)
:: Handle --config=Value (as single arg) or --config Value (split by cmd)
if /i "%~1"=="--config=Debug" (
    set "CONFIG=Debug"
    shift
    goto parse_args
)
if /i "%~1"=="--config=Release" (
    set "CONFIG=Release"
    shift
    goto parse_args
)
if /i "%~1"=="--config" (
    if /i "%~2"=="Debug" (
        set "CONFIG=Debug"
        shift
        shift
        goto parse_args
    )
    if /i "%~2"=="Release" (
        set "CONFIG=Release"
        shift
        shift
        goto parse_args
    )
    echo [X] Invalid config value: %~2
    goto show_help
)

echo [X] Unknown option: %~1
goto show_help

:done_args

:: ==============================================================================
:: Step 1: Setup Intel oneAPI environment
:: ==============================================================================
echo.
echo ========================================
echo Step 1: Setting up build environment
echo ========================================

set "ONEAPI_SETVARS=C:\Program Files (x86)\Intel\oneAPI\setvars.bat"
if exist "!ONEAPI_SETVARS!" (
    echo [+] Found Intel oneAPI, initializing environment...
    call "!ONEAPI_SETVARS!" >nul 2>&1
    if errorlevel 1 (
        echo [!] Warning: oneAPI setvars.bat returned an error
    ) else (
        echo [+] Intel oneAPI environment initialized
    )
) else (
    echo [!] Intel oneAPI not found at: !ONEAPI_SETVARS!
    echo     Install from: https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html
    echo     Build will fail if Intel IPP is required.
)

:: ==============================================================================
:: Step 2: Verify dependencies
:: ==============================================================================
echo.
echo ========================================
echo Step 2: Verifying dependencies
echo ========================================

:: Find MSBuild via vswhere
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "MSBUILD="

if exist "%VSWHERE%" (
    for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -prerelease -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe 2^>nul`) do (
        set "MSBUILD=%%i"
    )
)

if defined MSBUILD (
    echo [+] MSBuild found: %MSBUILD%
) else (
    echo [!] MSBuild not found. Please install Visual Studio with C++ workload.
    echo     https://visualstudio.microsoft.com/downloads/
    exit /b 1
)

:: Check for Projucer if regenerating
if "%REGENERATE%"=="1" (
    set "PROJUCER="

    if exist "C:\JUCE\Projucer.exe" set "PROJUCER=C:\JUCE\Projucer.exe"
    if exist "%ProgramFiles%\JUCE\Projucer.exe" set "PROJUCER=%ProgramFiles%\JUCE\Projucer.exe"
    if exist "%USERPROFILE%\JUCE\Projucer.exe" set "PROJUCER=%USERPROFILE%\JUCE\Projucer.exe"

    if defined PROJUCER (
        echo [+] Projucer found: !PROJUCER!
    ) else (
        echo [!] Projucer not found. Install from: https://juce.com/get-juce/
        echo     Or use --skip-regenerate to skip project regeneration
        exit /b 1
    )
)

:: Verify solution exists if skipping regeneration
if "%REGENERATE%"=="0" (
    if exist "%SLN_FILE%" (
        echo [+] Found VS solution: %SLN_FILE%
    ) else (
        echo [!] Solution not found. Run without --skip-regenerate to create it.
        exit /b 1
    )
)

:: ==============================================================================
:: Step 3: Regenerate VS project (optional)
:: ==============================================================================
if "%REGENERATE%"=="1" (
    echo.
    echo ========================================
    echo Step 3: Regenerating VS project
    echo ========================================

    echo Running: "%PROJUCER%" --resave "%JUCER_FILE%"
    "%PROJUCER%" --resave "%JUCER_FILE%"

    if exist "%SLN_FILE%" (
        echo [+] VS project regenerated successfully
    ) else (
        echo [!] Failed to regenerate VS project
        exit /b 1
    )
) else (
    echo.
    echo [i] Skipping VS project regeneration ^(--skip-regenerate^)
)

:: ==============================================================================
:: Step 4: Build with MSBuild
:: ==============================================================================
echo.
echo ========================================
echo Step 4: Building with MSBuild ^(%CONFIG%^)
echo ========================================

if "%CLEAN_BUILD%"=="1" (
    echo [i] Cleaning build...
    "%MSBUILD%" "%SLN_FILE%" /t:Clean /p:Configuration=%CONFIG% /p:Platform=x64 /verbosity:quiet >nul 2>&1
)

echo Building...
"%MSBUILD%" "%SLN_FILE%" /t:Build /p:Configuration=%CONFIG% /p:Platform=x64 /verbosity:minimal /m
if errorlevel 1 (
    echo [!] Build failed
    exit /b 1
)

:: Find the built executable
set "BUILD_DIR=%SCRIPT_DIR%\standalone\builds\vs19\x64\%CONFIG%\App"
set "EXE_PATH="

if exist "%BUILD_DIR%\Vial.exe" (
    set "EXE_PATH=%BUILD_DIR%\Vial.exe"
)

:: Fallback path
if not defined EXE_PATH (
    set "BUILD_DIR2=%SCRIPT_DIR%\standalone\builds\vs19\%CONFIG%"
    if exist "!BUILD_DIR2!\Vial.exe" (
        set "EXE_PATH=!BUILD_DIR2!\Vial.exe"
    )
)

if defined EXE_PATH (
    echo [+] Build successful: %EXE_PATH%

    :: Copy resource files next to the executable
    set "RESOURCE_SRC=%SCRIPT_DIR%\prompts\system_prompts"
    for %%E in ("%EXE_PATH%") do set "EXE_DIR=%%~dpE"

    for %%F in (SYSTEM_PROMPT.md PRESET_SCHEMA.md ROUTER_PROMPT.md SOUND_DESIGN_PROMPT.md SOUND_DESIGN_GUIDE.md) do (
        if exist "!RESOURCE_SRC!\%%F" (
            copy /y "!RESOURCE_SRC!\%%F" "!EXE_DIR!%%F" >nul
            echo [+] Copied %%F
        )
    )
) else (
    echo [!] Build may have succeeded but could not locate Vial.exe
    echo     Check: %BUILD_DIR%
)

:: ==============================================================================
:: Step 5: Run the app (optional)
:: ==============================================================================
if "%RUN_APP%"=="1" (
    if defined EXE_PATH (
        echo.
        echo ========================================
        echo Step 5: Launching Vial
        echo ========================================
        echo Starting: %EXE_PATH%
        start "" "%EXE_PATH%"
        echo [+] Done!
    )
) else (
    echo.
    echo [+] Build complete ^(--no-run specified^)
    if defined EXE_PATH echo App location: %EXE_PATH%
)

endlocal
exit /b 0

:show_help
echo build_windows.bat - Build Vital synthesizer on Windows
echo.
echo Usage: build_windows.bat [options]
echo.
echo Options:
echo   --config=Debug^|Release  Build configuration (default: Debug)
echo   --skip-regenerate       Skip VS project regeneration (faster builds)
echo   --no-run                Build only, don't launch the app
echo   --clean                 Clean build before building
echo   --help                  Show this help message
echo.
echo Examples:
echo   build_windows.bat                      Build Debug config
echo   build_windows.bat --config=Release     Build Release config
echo   build_windows.bat --skip-regenerate    Fast rebuild without Projucer
exit /b 0
