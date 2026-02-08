# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef PKG_CONFIG
  PKG_CONFIG=pkg-config
endif

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

JUCE_ARCH_LABEL := $(shell uname -m)

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DDEBUG=1" "-D_DEBUG=1" "-DIXWEBSOCKET_USE_TLS=1" "-DIXWEBSOCKET_USE_SECURE_TRANSPORT=1" "-DBUILD_DATE=$(BUILD_DATE)" "-DNO_AUTH=1" "-D_GLIBCXX_USE_CXX11_ABI=0" "-DJUCE_JACK_CLIENT_NAME=\"Vital\"" "-DJUCE_ALSA_MIDI_INPUT_NAME=\"Vital\"" "-DJUCE_ALSA_MIDI_OUTPUT_NAME=\"Vital\"" "-DJUCE_USE_XRANDR=0" "-DJUCE_OPENGL3=1" "-DJUCE_DSP_USE_SHARED_FFTW=1" "-DJUCER_LINUX_MAKE_6B3E762A=1" "-DJUCE_APP_VERSION=1.0.6" "-DJUCE_APP_VERSION_HEX=0x10006" $(shell $(PKG_CONFIG) --cflags alsa freetype2 libcurl) -pthread -I../../JuceLibraryCode -I../../../third_party/JUCE/modules -I../../../src/common -I../../../src/common/wavetable -I../../../src/interface/editor_components -I../../../src/interface/editor_sections -I../../../src/interface/look_and_feel -I../../../src/interface/wavetable -I../../../src/interface/wavetable/editors -I../../../src/interface/wavetable/overlays -I../../../src/standalone -I../../../src/synthesis/synth_engine -I../../../src/synthesis/effects -I../../../src/synthesis/filters -I../../../src/synthesis/framework -I../../../src/synthesis/lookups -I../../../src/synthesis/modulators -I../../../src/synthesis/modules -I../../../src/synthesis/producers -I../../../src/synthesis/utilities -I../../../third_party -I../../../third_party/md4c -I../../../third_party/ixwebsocket $(CPPFLAGS)
  JUCE_CPPFLAGS_APP :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_APP := vial

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 -ffast-math ${SIMDFLAGS} ${GLFLAGS} -ftree-vectorize -ftree-slp-vectorize -funroll-loops $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++17 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -L/usr/X11R6/lib/ $(shell $(PKG_CONFIG) --libs alsa freetype2 libcurl) -fvisibility=hidden -ffast-math ${SIMDFLAGS} ${GLFLAGS} -ftree-vectorize -ftree-slp-vectorize -lcurl -lrt -ldl -lpthread -lGL -lsecret-1 -lglib-2.0 $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(JUCE_TARGET_APP) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DNDEBUG=1" "-DIXWEBSOCKET_USE_TLS=1" "-DIXWEBSOCKET_USE_SECURE_TRANSPORT=1" "-DBUILD_DATE=$(BUILD_DATE)" "-DNO_AUTH=1" "-D_GLIBCXX_USE_CXX11_ABI=0" "-DJUCE_JACK_CLIENT_NAME=\"Vital\"" "-DJUCE_ALSA_MIDI_INPUT_NAME=\"Vital\"" "-DJUCE_ALSA_MIDI_OUTPUT_NAME=\"Vital\"" "-DJUCE_USE_XRANDR=0" "-DJUCE_OPENGL3=1" "-DJUCE_DSP_USE_SHARED_FFTW=1" "-DJUCER_LINUX_MAKE_6B3E762A=1" "-DJUCE_APP_VERSION=1.0.6" "-DJUCE_APP_VERSION_HEX=0x10006" $(shell $(PKG_CONFIG) --cflags alsa freetype2 libcurl) -pthread -I../../JuceLibraryCode -I../../../third_party/JUCE/modules -I../../../src/common -I../../../src/common/wavetable -I../../../src/interface/editor_components -I../../../src/interface/editor_sections -I../../../src/interface/look_and_feel -I../../../src/interface/wavetable -I../../../src/interface/wavetable/editors -I../../../src/interface/wavetable/overlays -I../../../src/standalone -I../../../src/synthesis/synth_engine -I../../../src/synthesis/effects -I../../../src/synthesis/filters -I../../../src/synthesis/framework -I../../../src/synthesis/lookups -I../../../src/synthesis/modulators -I../../../src/synthesis/modules -I../../../src/synthesis/producers -I../../../src/synthesis/utilities -I../../../third_party -I../../../third_party/md4c -I../../../third_party/ixwebsocket $(CPPFLAGS)
  JUCE_CPPFLAGS_APP :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJucePlugin_Build_LV2=0"
  JUCE_TARGET_APP := vial

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -Ofast -flto -ffast-math ${SIMDFLAGS} ${GLFLAGS} -ftree-vectorize -ftree-slp-vectorize -funroll-loops $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++17 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -L/usr/X11R6/lib/ $(shell $(PKG_CONFIG) --libs alsa freetype2 libcurl) -fvisibility=hidden -flto -ffast-math ${SIMDFLAGS} ${GLFLAGS} -ftree-vectorize -ftree-slp-vectorize -lcurl -lrt -ldl -lpthread -lGL -lsecret-1 -lglib-2.0 $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(JUCE_TARGET_APP) $(JUCE_OBJDIR)
endif

OBJECTS_APP := \
  $(JUCE_OBJDIR)/md4c_a090da74.o \
  $(JUCE_OBJDIR)/IXBench_7d52c42f.o \
  $(JUCE_OBJDIR)/IXCancellationRequest_afc0c28b.o \
  $(JUCE_OBJDIR)/IXConnectionState_ce334452.o \
  $(JUCE_OBJDIR)/IXDNSLookup_f41b2f82.o \
  $(JUCE_OBJDIR)/IXExponentialBackoff_4646bc4e.o \
  $(JUCE_OBJDIR)/IXGzipCodec_2e1485db.o \
  $(JUCE_OBJDIR)/IXHttp_45157eb3.o \
  $(JUCE_OBJDIR)/IXHttpClient_9509fa9e.o \
  $(JUCE_OBJDIR)/IXNetSystem_7dbd2b.o \
  $(JUCE_OBJDIR)/IXSelectInterrupt_6091eec6.o \
  $(JUCE_OBJDIR)/IXSelectInterruptEvent_8a597ebe.o \
  $(JUCE_OBJDIR)/IXSelectInterruptFactory_9833a56e.o \
  $(JUCE_OBJDIR)/IXSelectInterruptPipe_dd99dd14.o \
  $(JUCE_OBJDIR)/IXSetThreadName_46411a36.o \
  $(JUCE_OBJDIR)/IXSocket_5fbb229e.o \
  $(JUCE_OBJDIR)/IXSocketAppleSSL_92d3cd10.o \
  $(JUCE_OBJDIR)/IXSocketConnect_ccfb4676.o \
  $(JUCE_OBJDIR)/IXSocketFactory_6ad8ee96.o \
  $(JUCE_OBJDIR)/IXSocketMbedTLS_44a16e73.o \
  $(JUCE_OBJDIR)/IXSocketOpenSSL_afe3d0ee.o \
  $(JUCE_OBJDIR)/IXSocketTLSOptions_dbdd7721.o \
  $(JUCE_OBJDIR)/IXStrCaseCompare_f7bbe14f.o \
  $(JUCE_OBJDIR)/IXUrlParser_e32b0c6d.o \
  $(JUCE_OBJDIR)/IXUserAgent_760295f9.o \
  $(JUCE_OBJDIR)/IXUuid_acfc9866.o \
  $(JUCE_OBJDIR)/IXWebSocket_c68fd166.o \
  $(JUCE_OBJDIR)/IXWebSocketCloseConstants_5a1e9a7d.o \
  $(JUCE_OBJDIR)/IXWebSocketHandshake_974fd37b.o \
  $(JUCE_OBJDIR)/IXWebSocketHttpHeaders_77e30a22.o \
  $(JUCE_OBJDIR)/IXWebSocketPerMessageDeflate_b0c75825.o \
  $(JUCE_OBJDIR)/IXWebSocketPerMessageDeflateCodec_9d57983b.o \
  $(JUCE_OBJDIR)/IXWebSocketPerMessageDeflateOptions_61642ec3.o \
  $(JUCE_OBJDIR)/IXWebSocketTransport_73e765ad.o \
  $(JUCE_OBJDIR)/common_24cbed85.o \
  $(JUCE_OBJDIR)/interface_editor_components_ecc54012.o \
  $(JUCE_OBJDIR)/interface_editor_sections_3ae74ea.o \
  $(JUCE_OBJDIR)/interface_editor_sections2_72403e52.o \
  $(JUCE_OBJDIR)/interface_look_and_feel_36de0f18.o \
  $(JUCE_OBJDIR)/interface_wavetable_9ddf1df.o \
  $(JUCE_OBJDIR)/standalone_72202c5f.o \
  $(JUCE_OBJDIR)/synthesis_1ee447c4.o \
  $(JUCE_OBJDIR)/BinaryData_ce4232d4.o \
  $(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o \
  $(JUCE_OBJDIR)/include_juce_audio_devices_63111d02.o \
  $(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o \
  $(JUCE_OBJDIR)/include_juce_audio_utils_9f9fb2d6.o \
  $(JUCE_OBJDIR)/include_juce_core_f26d17db.o \
  $(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o \
  $(JUCE_OBJDIR)/include_juce_dsp_aeb2060f.o \
  $(JUCE_OBJDIR)/include_juce_events_fd7d695.o \
  $(JUCE_OBJDIR)/include_juce_graphics_f817e147.o \
  $(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o \
  $(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o \
  $(JUCE_OBJDIR)/include_juce_opengl_a8a032b.o \

.PHONY: clean all strip

all : $(JUCE_OUTDIR)/$(JUCE_TARGET_APP)

$(JUCE_OUTDIR)/$(JUCE_TARGET_APP) : $(OBJECTS_APP) $(JUCE_OBJDIR)/execinfo.cmd $(RESOURCES)
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@$(PKG_CONFIG) --print-errors alsa freetype2 libcurl
	@echo Linking "Vial - App"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_APP) $(OBJECTS_APP) $(JUCE_LDFLAGS) $(shell cat $(JUCE_OBJDIR)/execinfo.cmd) $(JUCE_LDFLAGS_APP) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OBJDIR)/md4c_a090da74.o: ../../../third_party/md4c/md4c.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling md4c.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXBench_7d52c42f.o: ../../../third_party/ixwebsocket/IXBench.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXBench.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXCancellationRequest_afc0c28b.o: ../../../third_party/ixwebsocket/IXCancellationRequest.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXCancellationRequest.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXConnectionState_ce334452.o: ../../../third_party/ixwebsocket/IXConnectionState.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXConnectionState.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXDNSLookup_f41b2f82.o: ../../../third_party/ixwebsocket/IXDNSLookup.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXDNSLookup.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXExponentialBackoff_4646bc4e.o: ../../../third_party/ixwebsocket/IXExponentialBackoff.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXExponentialBackoff.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXGzipCodec_2e1485db.o: ../../../third_party/ixwebsocket/IXGzipCodec.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXGzipCodec.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXHttp_45157eb3.o: ../../../third_party/ixwebsocket/IXHttp.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXHttp.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXHttpClient_9509fa9e.o: ../../../third_party/ixwebsocket/IXHttpClient.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXHttpClient.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXNetSystem_7dbd2b.o: ../../../third_party/ixwebsocket/IXNetSystem.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXNetSystem.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSelectInterrupt_6091eec6.o: ../../../third_party/ixwebsocket/IXSelectInterrupt.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSelectInterrupt.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSelectInterruptEvent_8a597ebe.o: ../../../third_party/ixwebsocket/IXSelectInterruptEvent.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSelectInterruptEvent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSelectInterruptFactory_9833a56e.o: ../../../third_party/ixwebsocket/IXSelectInterruptFactory.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSelectInterruptFactory.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSelectInterruptPipe_dd99dd14.o: ../../../third_party/ixwebsocket/IXSelectInterruptPipe.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSelectInterruptPipe.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSetThreadName_46411a36.o: ../../../third_party/ixwebsocket/IXSetThreadName.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSetThreadName.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSocket_5fbb229e.o: ../../../third_party/ixwebsocket/IXSocket.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSocket.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSocketAppleSSL_92d3cd10.o: ../../../third_party/ixwebsocket/IXSocketAppleSSL.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSocketAppleSSL.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSocketConnect_ccfb4676.o: ../../../third_party/ixwebsocket/IXSocketConnect.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSocketConnect.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSocketFactory_6ad8ee96.o: ../../../third_party/ixwebsocket/IXSocketFactory.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSocketFactory.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSocketMbedTLS_44a16e73.o: ../../../third_party/ixwebsocket/IXSocketMbedTLS.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSocketMbedTLS.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSocketOpenSSL_afe3d0ee.o: ../../../third_party/ixwebsocket/IXSocketOpenSSL.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSocketOpenSSL.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXSocketTLSOptions_dbdd7721.o: ../../../third_party/ixwebsocket/IXSocketTLSOptions.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXSocketTLSOptions.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXStrCaseCompare_f7bbe14f.o: ../../../third_party/ixwebsocket/IXStrCaseCompare.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXStrCaseCompare.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXUrlParser_e32b0c6d.o: ../../../third_party/ixwebsocket/IXUrlParser.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXUrlParser.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXUserAgent_760295f9.o: ../../../third_party/ixwebsocket/IXUserAgent.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXUserAgent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXUuid_acfc9866.o: ../../../third_party/ixwebsocket/IXUuid.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXUuid.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXWebSocket_c68fd166.o: ../../../third_party/ixwebsocket/IXWebSocket.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXWebSocket.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXWebSocketCloseConstants_5a1e9a7d.o: ../../../third_party/ixwebsocket/IXWebSocketCloseConstants.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXWebSocketCloseConstants.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXWebSocketHandshake_974fd37b.o: ../../../third_party/ixwebsocket/IXWebSocketHandshake.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXWebSocketHandshake.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXWebSocketHttpHeaders_77e30a22.o: ../../../third_party/ixwebsocket/IXWebSocketHttpHeaders.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXWebSocketHttpHeaders.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXWebSocketPerMessageDeflate_b0c75825.o: ../../../third_party/ixwebsocket/IXWebSocketPerMessageDeflate.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXWebSocketPerMessageDeflate.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXWebSocketPerMessageDeflateCodec_9d57983b.o: ../../../third_party/ixwebsocket/IXWebSocketPerMessageDeflateCodec.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXWebSocketPerMessageDeflateCodec.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXWebSocketPerMessageDeflateOptions_61642ec3.o: ../../../third_party/ixwebsocket/IXWebSocketPerMessageDeflateOptions.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXWebSocketPerMessageDeflateOptions.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IXWebSocketTransport_73e765ad.o: ../../../third_party/ixwebsocket/IXWebSocketTransport.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling IXWebSocketTransport.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/common_24cbed85.o: ../../../src/unity_build/common.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling common.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/interface_editor_components_ecc54012.o: ../../../src/unity_build/interface_editor_components.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling interface_editor_components.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/interface_editor_sections_3ae74ea.o: ../../../src/unity_build/interface_editor_sections.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling interface_editor_sections.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/interface_editor_sections2_72403e52.o: ../../../src/unity_build/interface_editor_sections2.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling interface_editor_sections2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/interface_look_and_feel_36de0f18.o: ../../../src/unity_build/interface_look_and_feel.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling interface_look_and_feel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/interface_wavetable_9ddf1df.o: ../../../src/unity_build/interface_wavetable.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling interface_wavetable.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/standalone_72202c5f.o: ../../../src/unity_build/standalone.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling standalone.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/synthesis_1ee447c4.o: ../../../src/unity_build/synthesis.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling synthesis.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling BinaryData.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o: ../../JuceLibraryCode/include_juce_audio_basics.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_devices_63111d02.o: ../../JuceLibraryCode/include_juce_audio_devices.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o: ../../JuceLibraryCode/include_juce_audio_formats.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o: ../../JuceLibraryCode/include_juce_audio_processors.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_utils_9f9fb2d6.o: ../../JuceLibraryCode/include_juce_audio_utils.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_audio_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_core_f26d17db.o: ../../JuceLibraryCode/include_juce_core.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o: ../../JuceLibraryCode/include_juce_data_structures.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_dsp_aeb2060f.o: ../../JuceLibraryCode/include_juce_dsp.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_dsp.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_events_fd7d695.o: ../../JuceLibraryCode/include_juce_events.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_graphics_f817e147.o: ../../JuceLibraryCode/include_juce_graphics.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o: ../../JuceLibraryCode/include_juce_gui_basics.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o: ../../JuceLibraryCode/include_juce_gui_extra.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_opengl_a8a032b.o: ../../JuceLibraryCode/include_juce_opengl.cpp
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling include_juce_opengl.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/execinfo.cmd:
	-$(V_AT)mkdir -p $(@D)
	-@if [ -z "$(V_AT)" ]; then echo "Checking if we need to link libexecinfo"; fi
	$(V_AT)printf "int main() { return 0; }" | $(CXX) -x c++ -o $(@D)/execinfo.x -lexecinfo - >/dev/null 2>&1 && printf -- "-lexecinfo" > "$@" || touch "$@"

$(JUCE_OBJDIR)/cxxfs.cmd:
	-$(V_AT)mkdir -p $(@D)
	-@if [ -z "$(V_AT)" ]; then echo "Checking if we need to link stdc++fs"; fi
	$(V_AT)printf "int main() { return 0; }" | $(CXX) -x c++ -o $(@D)/cxxfs.x -lstdc++fs - >/dev/null 2>&1 && printf -- "-lstdc++fs" > "$@" || touch "$@"

clean:
	@echo Cleaning Vial
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping Vial
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(JUCE_TARGET_APP)

-include $(OBJECTS_APP:%.o=%.d)
