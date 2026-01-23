#!/bin/bash

# build_macos.sh - Build Vital synthesizer on macOS
# Usage: ./build_macos.sh [options]
#
# Options:
#   --config=Debug|Release   Build configuration (default: Debug)
#   --skip-regenerate        Skip Xcode project regeneration (faster builds)
#   --team=TEAM_ID           Override development team ID for signing
#   --no-run                 Build only, don't launch the app
#   --clean                  Clean build before building
#   --help                   Show this help message

set -e  # Exit on error

# Default values
CONFIG="Debug"
REGENERATE=true
TEAM_ID=""
RUN_APP=true
CLEAN_BUILD=false

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
JUCER_FILE="$SCRIPT_DIR/standalone/vital.jucer"
XCODE_PROJECT="$SCRIPT_DIR/standalone/builds/osx/Vial.xcodeproj"
DERIVED_DATA="$HOME/Library/Developer/Xcode/DerivedData"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

echo_status() { echo -e "${GREEN}[✓]${NC} $1"; }
echo_warn() { echo -e "${YELLOW}[!]${NC} $1"; }
echo_error() { echo -e "${RED}[✗]${NC} $1"; }
echo_info() { echo -e "${CYAN}[i]${NC} $1"; }

show_help() {
    head -n 12 "$0" | tail -n 10
    exit 0
}

# Parse arguments
for arg in "$@"; do
    case $arg in
        --config=*)
            CONFIG="${arg#*=}"
            ;;
        --skip-regenerate)
            REGENERATE=false
            ;;
        --team=*)
            TEAM_ID="${arg#*=}"
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

# ==============================================================================
# Step 1: Verify dependencies
# ==============================================================================
echo ""
echo "========================================"
echo "Step 1: Verifying dependencies"
echo "========================================"

# Check for xcodebuild
if command -v xcodebuild &> /dev/null; then
    XCODE_VERSION=$(xcodebuild -version | head -n1)
    echo_status "xcodebuild found: $XCODE_VERSION"
else
    echo_error "xcodebuild not found. Please install Xcode command line tools:"
    echo "    xcode-select --install"
    exit 1
fi

# Check for Projucer (required unless --skip-regenerate)
if [ "$REGENERATE" = true ]; then
    PROJUCER_PATHS=(
        "/Applications/JUCE/Projucer.app/Contents/MacOS/Projucer"
        "/Applications/Projucer.app/Contents/MacOS/Projucer"
        "$HOME/JUCE/Projucer.app/Contents/MacOS/Projucer"
        "$HOME/Applications/JUCE/Projucer.app/Contents/MacOS/Projucer"
    )

    PROJUCER_BIN=""
    for path in "${PROJUCER_PATHS[@]}"; do
        if [ -x "$path" ]; then
            PROJUCER_BIN="$path"
            break
        fi
    done

    if [ -z "$PROJUCER_BIN" ] && command -v Projucer &> /dev/null; then
        PROJUCER_BIN="Projucer"
    fi

    if [ -n "$PROJUCER_BIN" ]; then
        echo_status "Projucer found: $PROJUCER_BIN"
    else
        echo_error "Projucer not found. Install from: https://juce.com/get-juce/"
        echo "       Or use --skip-regenerate to skip project regeneration"
        exit 1
    fi
fi

# Verify Xcode project exists
if [ -d "$XCODE_PROJECT" ]; then
    echo_status "Found Xcode project: $XCODE_PROJECT"
else
    echo_error "Xcode project not found. Run with --regenerate to create it."
    exit 1
fi

# ==============================================================================
# Step 2: Regenerate Xcode project (optional)
# ==============================================================================
if [ "$REGENERATE" = true ]; then
    echo ""
    echo "========================================"
    echo "Step 2: Regenerating Xcode project"
    echo "========================================"

    echo "Running: $PROJUCER_BIN --resave \"$JUCER_FILE\""
    "$PROJUCER_BIN" --resave "$JUCER_FILE"

    if [ -d "$XCODE_PROJECT" ]; then
        echo_status "Xcode project regenerated successfully"
    else
        echo_error "Failed to regenerate Xcode project"
        exit 1
    fi
else
    echo ""
    echo_info "Skipping Xcode project regeneration (--skip-regenerate)"
fi

# ==============================================================================
# Step 3: Build with xcodebuild
# ==============================================================================
echo ""
echo "========================================"
echo "Step 3: Building with xcodebuild ($CONFIG)"
echo "========================================"

cd "$SCRIPT_DIR/standalone/builds/osx"

# Get available schemes
SCHEME=$(xcodebuild -project Vial.xcodeproj -list 2>/dev/null | grep -A 100 "Schemes:" | tail -n +2 | head -n 1 | xargs)

if [ -z "$SCHEME" ]; then
    SCHEME="Vial - App"
fi

echo_info "Using scheme: $SCHEME"

# Build signing arguments
SIGNING_ARGS=("-allowProvisioningUpdates")
if [ -n "$TEAM_ID" ]; then
    echo_info "Using team ID override: $TEAM_ID"
    SIGNING_ARGS+=(
        "DEVELOPMENT_TEAM=$TEAM_ID"
        "CODE_SIGN_STYLE=Automatic"
    )
else
    echo_info "Using project signing settings"
fi

# Clean if requested
if [ "$CLEAN_BUILD" = true ]; then
    echo_info "Cleaning build..."
    xcodebuild -project Vial.xcodeproj -scheme "$SCHEME" -configuration "$CONFIG" clean >/dev/null 2>&1 || true
fi

echo "Building..."

# Run xcodebuild
BUILD_OUTPUT=$(mktemp)
xcodebuild \
    -project Vial.xcodeproj \
    -scheme "$SCHEME" \
    -configuration "$CONFIG" \
    "${SIGNING_ARGS[@]}" \
    build \
    2>&1 | tee "$BUILD_OUTPUT" | while read line; do
        # Show condensed output
        if [[ "$line" == *"error:"* ]]; then
            echo_error "$line"
        elif [[ "$line" == *"BUILD SUCCEEDED"* ]]; then
            echo_status "$line"
        elif [[ "$line" == *"BUILD FAILED"* ]]; then
            echo_error "$line"
        elif [[ "$line" == *"Compiling"* ]]; then
            # Show just the filename being compiled
            FILE=$(echo "$line" | sed 's/.*Compiling //' | sed 's/ .*//')
            echo "  Compiling $FILE"
        elif [[ "$line" == *"Linking"* ]]; then
            echo "  $line"
        fi
    done

# Check build result
if grep -q "BUILD SUCCEEDED" "$BUILD_OUTPUT"; then
    BUILD_SUCCESS=true
else
    BUILD_SUCCESS=false
fi
rm -f "$BUILD_OUTPUT"

# Find the built app
APP_PATH=$(find "$DERIVED_DATA" -name "Vial.app" -path "*Build/Products/$CONFIG*" -type d 2>/dev/null | head -n 1)

# Fallback to local build directory
if [ -z "$APP_PATH" ] || [ ! -d "$APP_PATH" ]; then
    BUILD_DIR="$SCRIPT_DIR/standalone/builds/osx/build/$CONFIG"
    if [ -d "$BUILD_DIR/Vial.app" ]; then
        APP_PATH="$BUILD_DIR/Vial.app"
    fi
fi

if [ "$BUILD_SUCCESS" = true ] && [ -d "$APP_PATH" ]; then
    echo_status "Build successful: $APP_PATH"
else
    echo_error "Build failed or could not find Vial.app"
    exit 1
fi

# ==============================================================================
# Step 4: Run the app (optional)
# ==============================================================================
if [ "$RUN_APP" = true ]; then
    echo ""
    echo "========================================"
    echo "Step 4: Launching Vial"
    echo "========================================"

    echo "Opening: $APP_PATH"
    open "$APP_PATH"
    echo_status "Done!"
else
    echo ""
    echo_status "Build complete (--no-run specified)"
    echo "App location: $APP_PATH"
fi
