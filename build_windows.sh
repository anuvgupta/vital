#!/bin/bash

# build_windows.sh - Build Vital synthesizer on Windows (Git Bash / WSL)
# Usage: ./build_windows.sh [options]
#
# Options:
#   --config=Debug|Release   Build configuration (default: Debug)
#   --skip-regenerate        Skip VS project regeneration (faster builds)
#   --no-run                 Build only, don't launch the app
#   --clean                  Clean build before building
#   --vs=2017|2019           Visual Studio version (default: 2019)
#   --help                   Show this help message

set -e  # Exit on error

# Default values
CONFIG="Debug"
REGENERATE=true
RUN_APP=true
CLEAN_BUILD=false
VS_VERSION="2019"

# Detect if running in WSL or Git Bash
if grep -qi microsoft /proc/version 2>/dev/null; then
    IN_WSL=true
else
    IN_WSL=false
fi

# Convert paths between Unix and Windows formats
to_win_path() {
    if [ "$IN_WSL" = true ]; then
        wslpath -w "$1"
    else
        # Git Bash: convert /c/... to C:\...
        echo "$1" | sed 's|^/\([a-zA-Z]\)/|\1:/|' | sed 's|/|\\|g'
    fi
}

to_unix_path() {
    if [ "$IN_WSL" = true ]; then
        wslpath -u "$1"
    else
        # Git Bash: convert C:\... to /c/...
        echo "$1" | sed 's|^\([a-zA-Z]\):|/\L\1|' | sed 's|\\|/|g'
    fi
}

# Run a Windows command
run_win_cmd() {
    if [ "$IN_WSL" = true ]; then
        cmd.exe /c "$@"
    else
        "$@"
    fi
}

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
JUCER_FILE="$SCRIPT_DIR/standalone/vital.jucer"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

echo_status() { echo -e "${GREEN}[+]${NC} $1"; }
echo_warn() { echo -e "${YELLOW}[!]${NC} $1"; }
echo_error() { echo -e "${RED}[!]${NC} $1"; }
echo_info() { echo -e "${CYAN}[i]${NC} $1"; }

show_help() {
    head -n 13 "$0" | tail -n 11
    exit 0
}

# Parse arguments
for arg in "$@"; do
    case $arg in
        --config=*)
            CONFIG="${arg#*=}"
            ;;
        --vs=*)
            VS_VERSION="${arg#*=}"
            ;;
        --skip-regenerate)
            REGENERATE=false
            ;;
        --no-run)
            RUN_APP=false
            ;;
        --clean)
            CLEAN_BUILD=true
            ;;
        --help|-h)
            show_help
            ;;
        Debug|Release)
            CONFIG="$arg"
            ;;
        *)
            echo_error "Unknown option: $arg"
            show_help
            ;;
    esac
done

# Set VS-specific paths
if [ "$VS_VERSION" = "2017" ]; then
    VS_DIR="vs17"
else
    VS_DIR="vs19"
fi

SLN_FILE="$SCRIPT_DIR/standalone/builds/$VS_DIR/Vial.sln"

# ==============================================================================
# Step 1: Verify dependencies
# ==============================================================================
echo ""
echo "========================================"
echo "Step 1: Verifying dependencies"
echo "========================================"

# Find MSBuild via vswhere
VSWHERE_PATH="/c/Program Files (x86)/Microsoft Visual Studio/Installer/vswhere.exe"
if [ "$IN_WSL" = true ]; then
    VSWHERE_PATH="$(to_unix_path 'C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe')"
fi

MSBUILD=""
if [ -f "$VSWHERE_PATH" ]; then
    VSWHERE_WIN="$(to_win_path "$VSWHERE_PATH")"
    if [ "$IN_WSL" = true ]; then
        MSBUILD_WIN=$("$VSWHERE_PATH" -latest -requires Microsoft.Component.MSBuild -find 'MSBuild\**\Bin\MSBuild.exe' 2>/dev/null | head -n1 | tr -d '\r')
    else
        MSBUILD_WIN=$("$VSWHERE_PATH" -latest -requires Microsoft.Component.MSBuild -find 'MSBuild\**\Bin\MSBuild.exe' 2>/dev/null | head -n1)
    fi
    if [ -n "$MSBUILD_WIN" ]; then
        MSBUILD="$(to_unix_path "$MSBUILD_WIN")"
    fi
fi

if [ -n "$MSBUILD" ] && [ -f "$MSBUILD" ]; then
    echo_status "MSBuild found: $MSBUILD"
else
    echo_error "MSBuild not found. Please install Visual Studio with C++ workload."
    echo "       https://visualstudio.microsoft.com/downloads/"
    exit 1
fi

# Check for Projucer if regenerating
if [ "$REGENERATE" = true ]; then
    PROJUCER_PATHS=(
        "/c/JUCE/Projucer.exe"
        "/c/Program Files/JUCE/Projucer.exe"
        "$HOME/JUCE/Projucer.exe"
    )

    # Add WSL-specific paths
    if [ "$IN_WSL" = true ]; then
        PROJUCER_PATHS+=(
            "$(to_unix_path 'C:\JUCE\Projucer.exe')"
            "$(to_unix_path 'C:\Program Files\JUCE\Projucer.exe')"
        )
    fi

    PROJUCER_BIN=""
    for path in "${PROJUCER_PATHS[@]}"; do
        if [ -f "$path" ]; then
            PROJUCER_BIN="$path"
            break
        fi
    done

    if [ -n "$PROJUCER_BIN" ]; then
        echo_status "Projucer found: $PROJUCER_BIN"
    else
        echo_error "Projucer not found. Install from: https://juce.com/get-juce/"
        echo "       Or use --skip-regenerate to skip project regeneration"
        exit 1
    fi
fi

# Verify solution exists if skipping regeneration
if [ "$REGENERATE" = false ]; then
    if [ -f "$SLN_FILE" ]; then
        echo_status "Found VS solution: $SLN_FILE"
    else
        echo_error "Solution not found. Run without --skip-regenerate to create it."
        exit 1
    fi
fi

# ==============================================================================
# Step 2: Regenerate VS project (optional)
# ==============================================================================
if [ "$REGENERATE" = true ]; then
    echo ""
    echo "========================================"
    echo "Step 2: Regenerating VS project"
    echo "========================================"

    JUCER_WIN="$(to_win_path "$JUCER_FILE")"
    echo "Running: $PROJUCER_BIN --resave $JUCER_WIN"
    "$PROJUCER_BIN" --resave "$JUCER_WIN"

    if [ -f "$SLN_FILE" ]; then
        echo_status "VS project regenerated successfully"
    else
        echo_error "Failed to regenerate VS project"
        exit 1
    fi
else
    echo ""
    echo_info "Skipping VS project regeneration (--skip-regenerate)"
fi

# ==============================================================================
# Step 3: Build with MSBuild
# ==============================================================================
echo ""
echo "========================================"
echo "Step 3: Building with MSBuild ($CONFIG)"
echo "========================================"

# Setup Intel oneAPI environment if available (required for Intel IPP)
ONEAPI_SETVARS=""
ONEAPI_PATHS=(
    "/c/Program Files (x86)/Intel/oneAPI/setvars.bat"
)
if [ "$IN_WSL" = true ]; then
    ONEAPI_PATHS+=(
        "$(to_unix_path 'C:\Program Files (x86)\Intel\oneAPI\setvars.bat')"
    )
fi

for path in "${ONEAPI_PATHS[@]}"; do
    if [ -f "$path" ]; then
        ONEAPI_SETVARS="$path"
        break
    fi
done

SLN_WIN="$(to_win_path "$SLN_FILE")"

if [ "$CLEAN_BUILD" = true ]; then
    echo_info "Cleaning build..."
    "$MSBUILD" "$SLN_WIN" //t:Clean //p:Configuration=$CONFIG //p:Platform=x64 //verbosity:quiet 2>/dev/null || true
fi

echo "Building..."

# Build command - wrap with oneAPI environment if available
MSBUILD_WIN="$(to_win_path "$MSBUILD")"
BUILD_EXIT_CODE=0

if [ -n "$ONEAPI_SETVARS" ]; then
    echo_info "Using Intel oneAPI environment"
    SETVARS_WIN="$(to_win_path "$ONEAPI_SETVARS")"

    # Create a temporary batch file to run the build with oneAPI environment
    TEMP_BAT="$SCRIPT_DIR/_build_temp.bat"
    cat > "$TEMP_BAT" << EOF
@echo off
call "$SETVARS_WIN" >nul 2>&1
"$MSBUILD_WIN" "$SLN_WIN" /t:Build /p:Configuration=$CONFIG /p:Platform=x64 /verbosity:minimal /m
exit /b %ERRORLEVEL%
EOF

    # Convert to Windows line endings
    sed -i 's/$/\r/' "$TEMP_BAT" 2>/dev/null || true

    TEMP_BAT_WIN="$(to_win_path "$TEMP_BAT")"

    if [ "$IN_WSL" = true ]; then
        cmd.exe /c "$TEMP_BAT_WIN"
        BUILD_EXIT_CODE=$?
    else
        cmd //c "$TEMP_BAT_WIN"
        BUILD_EXIT_CODE=$?
    fi

    # Clean up temp batch file
    rm -f "$TEMP_BAT"
else
    echo_warn "Intel oneAPI not found - build may fail if Intel IPP is required"
    "$MSBUILD" "$SLN_WIN" //t:Build //p:Configuration=$CONFIG //p:Platform=x64 //verbosity:minimal //m
    BUILD_EXIT_CODE=$?
fi

if [ $BUILD_EXIT_CODE -ne 0 ]; then
    echo_error "Build failed"
    exit 1
fi

# Find the built executable
BUILD_DIR="$SCRIPT_DIR/standalone/builds/$VS_DIR/x64/$CONFIG/App"
EXE_PATH=""

if [ -f "$BUILD_DIR/Vial.exe" ]; then
    EXE_PATH="$BUILD_DIR/Vial.exe"
fi

# Fallback paths
if [ -z "$EXE_PATH" ]; then
    ALT_DIR="$SCRIPT_DIR/standalone/builds/$VS_DIR/$CONFIG"
    if [ -f "$ALT_DIR/Vial.exe" ]; then
        EXE_PATH="$ALT_DIR/Vial.exe"
    fi
fi

if [ -n "$EXE_PATH" ] && [ -f "$EXE_PATH" ]; then
    echo_status "Build successful: $EXE_PATH"

    # Copy resource files next to the executable
    RESOURCE_FILES=("SYSTEM_PROMPT.md" "PRESET_SCHEMA.md")
    RESOURCE_SRC_DIR="$SCRIPT_DIR/agents/vital-assistant"
    EXE_DIR="$(dirname "$EXE_PATH")"

    for FILE in "${RESOURCE_FILES[@]}"; do
        if [ -f "$RESOURCE_SRC_DIR/$FILE" ]; then
            cp "$RESOURCE_SRC_DIR/$FILE" "$EXE_DIR/$FILE"
            echo_status "Copied $FILE to $EXE_DIR"
        else
            echo_warn "$FILE not found at $RESOURCE_SRC_DIR/$FILE"
        fi
    done
else
    echo_warn "Build may have succeeded but could not locate Vial.exe"
    echo "      Check: $BUILD_DIR"
fi

# ==============================================================================
# Step 4: Run the app (optional)
# ==============================================================================
if [ "$RUN_APP" = true ]; then
    if [ -n "$EXE_PATH" ] && [ -f "$EXE_PATH" ]; then
        echo ""
        echo "========================================"
        echo "Step 4: Launching Vial"
        echo "========================================"

        EXE_WIN="$(to_win_path "$EXE_PATH")"
        echo "Starting: $EXE_WIN"

        if [ "$IN_WSL" = true ]; then
            cmd.exe /c start "" "$EXE_WIN" &
        else
            start "" "$EXE_WIN" &
        fi

        echo_status "Done!"
    fi
else
    echo ""
    echo_status "Build complete (--no-run specified)"
    if [ -n "$EXE_PATH" ]; then
        echo "App location: $EXE_PATH"
    fi
fi
