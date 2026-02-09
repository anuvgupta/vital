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

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DDEBUG=1" "-D_DEBUG=1" "-DIXWEBSOCKET_USE_TLS=1" "-DBUILD_DATE=$(BUILD_DATE)" "-DNO_AUTH=1" "-D_GLIBCXX_USE_CXX11_ABI=0" "-DJUCE_JACK_CLIENT_NAME=\"Vital\"" "-DJUCE_ALSA_MIDI_INPUT_NAME=\"Vital\"" "-DJUCE_ALSA_MIDI_OUTPUT_NAME=\"Vital\"" "-DJUCE_USE_XRANDR=0" "-DJUCE_OPENGL3=1" "-DJUCE_DSP_USE_SHARED_FFTW=1" "-DJUCER_LINUX_MAKE_6B3E762A=1" "-DJUCE_APP_VERSION=1.0.6" "-DJUCE_APP_VERSION_HEX=0x10006" $(shell $(PKG_CONFIG) --cflags alsa freetype2 libcurl) -pthread -I../../JuceLibraryCode -I../../../third_party/JUCE/modules -I../../../src/common -I../../../src/common/wavetable -I../../../src/interface/editor_components -I../../../src/interface/editor_sections -I../../../src/interface/look_and_feel -I../../../src/interface/wavetable -I../../../src/interface/wavetable/editors -I../../../src/interface/wavetable/overlays -I../../../src/standalone -I../../../src/synthesis/synth_engine -I../../../src/synthesis/effects -I../../../src/synthesis/filters -I../../../src/synthesis/framework -I../../../src/synthesis/lookups -I../../../src/synthesis/modulators -I../../../src/synthesis/modules -I../../../src/synthesis/producers -I../../../src/synthesis/utilities -I../../../third_party -I../../../third_party/md4c -I../../../third_party/ixwebsocket $(CPPFLAGS)
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

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DNDEBUG=1" "-DIXWEBSOCKET_USE_TLS=1" "-DBUILD_DATE=$(BUILD_DATE)" "-DNO_AUTH=1" "-D_GLIBCXX_USE_CXX11_ABI=0" "-DJUCE_JACK_CLIENT_NAME=\"Vital\"" "-DJUCE_ALSA_MIDI_INPUT_NAME=\"Vital\"" "-DJUCE_ALSA_MIDI_OUTPUT_NAME=\"Vital\"" "-DJUCE_USE_XRANDR=0" "-DJUCE_OPENGL3=1" "-DJUCE_DSP_USE_SHARED_FFTW=1" "-DJUCER_LINUX_MAKE_6B3E762A=1" "-DJUCE_APP_VERSION=1.0.6" "-DJUCE_APP_VERSION_HEX=0x10006" $(shell $(PKG_CONFIG) --cflags alsa freetype2 libcurl) -pthread -I../../JuceLibraryCode -I../../../third_party/JUCE/modules -I../../../src/common -I../../../src/common/wavetable -I../../../src/interface/editor_components -I../../../src/interface/editor_sections -I../../../src/interface/look_and_feel -I../../../src/interface/wavetable -I../../../src/interface/wavetable/editors -I../../../src/interface/wavetable/overlays -I../../../src/standalone -I../../../src/synthesis/synth_engine -I../../../src/synthesis/effects -I../../../src/synthesis/filters -I../../../src/synthesis/framework -I../../../src/synthesis/lookups -I../../../src/synthesis/modulators -I../../../src/synthesis/modules -I../../../src/synthesis/producers -I../../../src/synthesis/utilities -I../../../third_party -I../../../third_party/md4c -I../../../third_party/ixwebsocket $(CPPFLAGS)
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
  $(JUCE_OBJDIR)/aes_912de3f8.o \
  $(JUCE_OBJDIR)/aesce_fd5ceb1a.o \
  $(JUCE_OBJDIR)/aesni_fd61fa33.o \
  $(JUCE_OBJDIR)/aria_9541fa4a.o \
  $(JUCE_OBJDIR)/asn1parse_ab05eb07.o \
  $(JUCE_OBJDIR)/asn1write_39d58d33.o \
  $(JUCE_OBJDIR)/base64_428f9a10.o \
  $(JUCE_OBJDIR)/bignum_d5e39987.o \
  $(JUCE_OBJDIR)/bignum_core_82351ea1.o \
  $(JUCE_OBJDIR)/bignum_mod_f43bd20a.o \
  $(JUCE_OBJDIR)/bignum_mod_raw_432e70b3.o \
  $(JUCE_OBJDIR)/block_cipher_9f27c63e.o \
  $(JUCE_OBJDIR)/camellia_c169600f.o \
  $(JUCE_OBJDIR)/ccm_914913b6.o \
  $(JUCE_OBJDIR)/chacha20_7f65babf.o \
  $(JUCE_OBJDIR)/chachapoly_aa42cdcd.o \
  $(JUCE_OBJDIR)/cipher_4cc4a3cc.o \
  $(JUCE_OBJDIR)/cipher_wrap_d86c5967.o \
  $(JUCE_OBJDIR)/cmac_98619a8d.o \
  $(JUCE_OBJDIR)/constant_time_5d7f0e71.o \
  $(JUCE_OBJDIR)/ctr_drbg_7f28c9f2.o \
  $(JUCE_OBJDIR)/debug_9b28437c.o \
  $(JUCE_OBJDIR)/des_91582a7b.o \
  $(JUCE_OBJDIR)/dhm_91597112.o \
  $(JUCE_OBJDIR)/ecdh_9b3fd0a3.o \
  $(JUCE_OBJDIR)/ecdsa_ccbffd3d.o \
  $(JUCE_OBJDIR)/ecjpake_d51843c0.o \
  $(JUCE_OBJDIR)/ecp_91654dfb.o \
  $(JUCE_OBJDIR)/ecp_curves_eeca50f2.o \
  $(JUCE_OBJDIR)/ecp_curves_new_42dcaf13.o \
  $(JUCE_OBJDIR)/entropy_60f50d1a.o \
  $(JUCE_OBJDIR)/entropy_poll_88184f0e.o \
  $(JUCE_OBJDIR)/error_e71c65f1.o \
  $(JUCE_OBJDIR)/gcm_918171ba.o \
  $(JUCE_OBJDIR)/hkdf_a0cf0f06.o \
  $(JUCE_OBJDIR)/hmac_drbg_47dc2fd4.o \
  $(JUCE_OBJDIR)/lmots_50b7ccb6.o \
  $(JUCE_OBJDIR)/lms_91cc897b.o \
  $(JUCE_OBJDIR)/md_fc723e58.o \
  $(JUCE_OBJDIR)/md5_91d5a0e7.o \
  $(JUCE_OBJDIR)/memory_buffer_alloc_54818edd.o \
  $(JUCE_OBJDIR)/mps_reader_429ec2b3.o \
  $(JUCE_OBJDIR)/mps_trace_4852addf.o \
  $(JUCE_OBJDIR)/net_sockets_58cfaa27.o \
  $(JUCE_OBJDIR)/nist_kw_5d96c458.o \
  $(JUCE_OBJDIR)/oid_91f4c633.o \
  $(JUCE_OBJDIR)/padlock_20cfa5a7.o \
  $(JUCE_OBJDIR)/pem_92012e01.o \
  $(JUCE_OBJDIR)/pk_fc73b5bc.o \
  $(JUCE_OBJDIR)/pk_ecc_dfd29782.o \
  $(JUCE_OBJDIR)/pk_wrap_3a0afd77.o \
  $(JUCE_OBJDIR)/pkcs12_e753d08d.o \
  $(JUCE_OBJDIR)/pkcs5_203c9153.o \
  $(JUCE_OBJDIR)/pkcs7_203c98d5.o \
  $(JUCE_OBJDIR)/pkparse_97d25481.o \
  $(JUCE_OBJDIR)/pkwrite_26a1f6ad.o \
  $(JUCE_OBJDIR)/platform_b8f5b934.o \
  $(JUCE_OBJDIR)/platform_util_e6ce76b7.o \
  $(JUCE_OBJDIR)/poly1305_9711ee34.o \
  $(JUCE_OBJDIR)/psa_crypto_ae5b6763.o \
  $(JUCE_OBJDIR)/psa_crypto_aead_a1013fed.o \
  $(JUCE_OBJDIR)/psa_crypto_cipher_22f68d71.o \
  $(JUCE_OBJDIR)/psa_crypto_client_b5912b31.o \
  $(JUCE_OBJDIR)/psa_crypto_driver_wrappers_no_static_42ebc608.o \
  $(JUCE_OBJDIR)/psa_crypto_ecp_dab4e76.o \
  $(JUCE_OBJDIR)/psa_crypto_ffdh_a998feaa.o \
  $(JUCE_OBJDIR)/psa_crypto_hash_acc30bf4.o \
  $(JUCE_OBJDIR)/psa_crypto_mac_e1af0f3.o \
  $(JUCE_OBJDIR)/psa_crypto_pake_ba6622b1.o \
  $(JUCE_OBJDIR)/psa_crypto_rsa_e698da4.o \
  $(JUCE_OBJDIR)/psa_crypto_se_217f8078.o \
  $(JUCE_OBJDIR)/psa_crypto_slot_management_8ad5508.o \
  $(JUCE_OBJDIR)/psa_crypto_storage_d2bca39f.o \
  $(JUCE_OBJDIR)/psa_its_file_5cb37995.o \
  $(JUCE_OBJDIR)/psa_util_89ccf1a4.o \
  $(JUCE_OBJDIR)/ripemd160_a858b8b1.o \
  $(JUCE_OBJDIR)/rsa_92238d29.o \
  $(JUCE_OBJDIR)/rsa_alt_helpers_dd1dbf59.o \
  $(JUCE_OBJDIR)/sha1_b367f346.o \
  $(JUCE_OBJDIR)/sha256_7948dce8.o \
  $(JUCE_OBJDIR)/sha3_b367fac8.o \
  $(JUCE_OBJDIR)/sha512_797142eb.o \
  $(JUCE_OBJDIR)/ssl_cache_f47e4bb8.o \
  $(JUCE_OBJDIR)/ssl_ciphersuites_e315acda.o \
  $(JUCE_OBJDIR)/ssl_client_eb479c5f.o \
  $(JUCE_OBJDIR)/ssl_cookie_948970b8.o \
  $(JUCE_OBJDIR)/ssl_debug_helpers_generated_c267799f.o \
  $(JUCE_OBJDIR)/ssl_msg_bc5ffc37.o \
  $(JUCE_OBJDIR)/ssl_ticket_289c4760.o \
  $(JUCE_OBJDIR)/ssl_tls_bcbf9f31.o \
  $(JUCE_OBJDIR)/ssl_tls12_client_c19bbda2.o \
  $(JUCE_OBJDIR)/ssl_tls12_server_dda9fb1a.o \
  $(JUCE_OBJDIR)/ssl_tls13_client_b5e52ec1.o \
  $(JUCE_OBJDIR)/ssl_tls13_generic_895d726b.o \
  $(JUCE_OBJDIR)/ssl_tls13_keys_9bbc7eea.o \
  $(JUCE_OBJDIR)/ssl_tls13_server_d1f36c39.o \
  $(JUCE_OBJDIR)/threading_8ec62b81.o \
  $(JUCE_OBJDIR)/timing_2dac1a4b.o \
  $(JUCE_OBJDIR)/version_2a290fc1.o \
  $(JUCE_OBJDIR)/version_features_ab5a6045.o \
  $(JUCE_OBJDIR)/x509_b90b5787.o \
  $(JUCE_OBJDIR)/x509_create_419af7e.o \
  $(JUCE_OBJDIR)/x509_crl_60c92025.o \
  $(JUCE_OBJDIR)/x509_crt_60c93e2d.o \
  $(JUCE_OBJDIR)/x509_csr_60c9ab0a.o \
  $(JUCE_OBJDIR)/x509write_c70ebbc2.o \
  $(JUCE_OBJDIR)/x509write_crt_39ba0ce8.o \
  $(JUCE_OBJDIR)/x509write_csr_39ba79c5.o \
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

$(JUCE_OBJDIR)/aes_912de3f8.o: ../../../third_party/mbedtls/library/aes.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling aes.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/aesce_fd5ceb1a.o: ../../../third_party/mbedtls/library/aesce.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling aesce.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/aesni_fd61fa33.o: ../../../third_party/mbedtls/library/aesni.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling aesni.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/aria_9541fa4a.o: ../../../third_party/mbedtls/library/aria.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling aria.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/asn1parse_ab05eb07.o: ../../../third_party/mbedtls/library/asn1parse.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling asn1parse.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/asn1write_39d58d33.o: ../../../third_party/mbedtls/library/asn1write.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling asn1write.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/base64_428f9a10.o: ../../../third_party/mbedtls/library/base64.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling base64.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bignum_d5e39987.o: ../../../third_party/mbedtls/library/bignum.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling bignum.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bignum_core_82351ea1.o: ../../../third_party/mbedtls/library/bignum_core.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling bignum_core.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bignum_mod_f43bd20a.o: ../../../third_party/mbedtls/library/bignum_mod.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling bignum_mod.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bignum_mod_raw_432e70b3.o: ../../../third_party/mbedtls/library/bignum_mod_raw.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling bignum_mod_raw.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/block_cipher_9f27c63e.o: ../../../third_party/mbedtls/library/block_cipher.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling block_cipher.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/camellia_c169600f.o: ../../../third_party/mbedtls/library/camellia.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling camellia.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ccm_914913b6.o: ../../../third_party/mbedtls/library/ccm.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ccm.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/chacha20_7f65babf.o: ../../../third_party/mbedtls/library/chacha20.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling chacha20.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/chachapoly_aa42cdcd.o: ../../../third_party/mbedtls/library/chachapoly.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling chachapoly.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cipher_4cc4a3cc.o: ../../../third_party/mbedtls/library/cipher.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling cipher.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cipher_wrap_d86c5967.o: ../../../third_party/mbedtls/library/cipher_wrap.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling cipher_wrap.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cmac_98619a8d.o: ../../../third_party/mbedtls/library/cmac.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling cmac.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/constant_time_5d7f0e71.o: ../../../third_party/mbedtls/library/constant_time.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling constant_time.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ctr_drbg_7f28c9f2.o: ../../../third_party/mbedtls/library/ctr_drbg.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ctr_drbg.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/debug_9b28437c.o: ../../../third_party/mbedtls/library/debug.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling debug.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/des_91582a7b.o: ../../../third_party/mbedtls/library/des.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling des.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/dhm_91597112.o: ../../../third_party/mbedtls/library/dhm.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling dhm.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ecdh_9b3fd0a3.o: ../../../third_party/mbedtls/library/ecdh.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ecdh.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ecdsa_ccbffd3d.o: ../../../third_party/mbedtls/library/ecdsa.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ecdsa.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ecjpake_d51843c0.o: ../../../third_party/mbedtls/library/ecjpake.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ecjpake.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ecp_91654dfb.o: ../../../third_party/mbedtls/library/ecp.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ecp.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ecp_curves_eeca50f2.o: ../../../third_party/mbedtls/library/ecp_curves.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ecp_curves.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ecp_curves_new_42dcaf13.o: ../../../third_party/mbedtls/library/ecp_curves_new.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ecp_curves_new.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/entropy_60f50d1a.o: ../../../third_party/mbedtls/library/entropy.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling entropy.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/entropy_poll_88184f0e.o: ../../../third_party/mbedtls/library/entropy_poll.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling entropy_poll.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/error_e71c65f1.o: ../../../third_party/mbedtls/library/error.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling error.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/gcm_918171ba.o: ../../../third_party/mbedtls/library/gcm.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling gcm.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hkdf_a0cf0f06.o: ../../../third_party/mbedtls/library/hkdf.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling hkdf.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hmac_drbg_47dc2fd4.o: ../../../third_party/mbedtls/library/hmac_drbg.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling hmac_drbg.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lmots_50b7ccb6.o: ../../../third_party/mbedtls/library/lmots.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling lmots.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lms_91cc897b.o: ../../../third_party/mbedtls/library/lms.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling lms.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/md_fc723e58.o: ../../../third_party/mbedtls/library/md.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling md.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/md5_91d5a0e7.o: ../../../third_party/mbedtls/library/md5.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling md5.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/memory_buffer_alloc_54818edd.o: ../../../third_party/mbedtls/library/memory_buffer_alloc.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling memory_buffer_alloc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mps_reader_429ec2b3.o: ../../../third_party/mbedtls/library/mps_reader.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling mps_reader.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mps_trace_4852addf.o: ../../../third_party/mbedtls/library/mps_trace.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling mps_trace.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/net_sockets_58cfaa27.o: ../../../third_party/mbedtls/library/net_sockets.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling net_sockets.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/nist_kw_5d96c458.o: ../../../third_party/mbedtls/library/nist_kw.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling nist_kw.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/oid_91f4c633.o: ../../../third_party/mbedtls/library/oid.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling oid.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/padlock_20cfa5a7.o: ../../../third_party/mbedtls/library/padlock.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling padlock.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pem_92012e01.o: ../../../third_party/mbedtls/library/pem.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pem.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pk_fc73b5bc.o: ../../../third_party/mbedtls/library/pk.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pk.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pk_ecc_dfd29782.o: ../../../third_party/mbedtls/library/pk_ecc.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pk_ecc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pk_wrap_3a0afd77.o: ../../../third_party/mbedtls/library/pk_wrap.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pk_wrap.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pkcs12_e753d08d.o: ../../../third_party/mbedtls/library/pkcs12.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pkcs12.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pkcs5_203c9153.o: ../../../third_party/mbedtls/library/pkcs5.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pkcs5.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pkcs7_203c98d5.o: ../../../third_party/mbedtls/library/pkcs7.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pkcs7.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pkparse_97d25481.o: ../../../third_party/mbedtls/library/pkparse.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pkparse.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pkwrite_26a1f6ad.o: ../../../third_party/mbedtls/library/pkwrite.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling pkwrite.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/platform_b8f5b934.o: ../../../third_party/mbedtls/library/platform.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling platform.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/platform_util_e6ce76b7.o: ../../../third_party/mbedtls/library/platform_util.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling platform_util.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/poly1305_9711ee34.o: ../../../third_party/mbedtls/library/poly1305.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling poly1305.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_ae5b6763.o: ../../../third_party/mbedtls/library/psa_crypto.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_aead_a1013fed.o: ../../../third_party/mbedtls/library/psa_crypto_aead.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_aead.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_cipher_22f68d71.o: ../../../third_party/mbedtls/library/psa_crypto_cipher.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_cipher.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_client_b5912b31.o: ../../../third_party/mbedtls/library/psa_crypto_client.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_client.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_driver_wrappers_no_static_42ebc608.o: ../../../third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_driver_wrappers_no_static.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_ecp_dab4e76.o: ../../../third_party/mbedtls/library/psa_crypto_ecp.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_ecp.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_ffdh_a998feaa.o: ../../../third_party/mbedtls/library/psa_crypto_ffdh.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_ffdh.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_hash_acc30bf4.o: ../../../third_party/mbedtls/library/psa_crypto_hash.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_hash.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_mac_e1af0f3.o: ../../../third_party/mbedtls/library/psa_crypto_mac.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_mac.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_pake_ba6622b1.o: ../../../third_party/mbedtls/library/psa_crypto_pake.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_pake.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_rsa_e698da4.o: ../../../third_party/mbedtls/library/psa_crypto_rsa.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_rsa.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_se_217f8078.o: ../../../third_party/mbedtls/library/psa_crypto_se.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_se.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_slot_management_8ad5508.o: ../../../third_party/mbedtls/library/psa_crypto_slot_management.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_slot_management.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_crypto_storage_d2bca39f.o: ../../../third_party/mbedtls/library/psa_crypto_storage.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_crypto_storage.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_its_file_5cb37995.o: ../../../third_party/mbedtls/library/psa_its_file.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_its_file.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/psa_util_89ccf1a4.o: ../../../third_party/mbedtls/library/psa_util.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling psa_util.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ripemd160_a858b8b1.o: ../../../third_party/mbedtls/library/ripemd160.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ripemd160.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rsa_92238d29.o: ../../../third_party/mbedtls/library/rsa.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling rsa.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rsa_alt_helpers_dd1dbf59.o: ../../../third_party/mbedtls/library/rsa_alt_helpers.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling rsa_alt_helpers.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sha1_b367f346.o: ../../../third_party/mbedtls/library/sha1.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling sha1.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sha256_7948dce8.o: ../../../third_party/mbedtls/library/sha256.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling sha256.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sha3_b367fac8.o: ../../../third_party/mbedtls/library/sha3.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling sha3.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sha512_797142eb.o: ../../../third_party/mbedtls/library/sha512.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling sha512.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_cache_f47e4bb8.o: ../../../third_party/mbedtls/library/ssl_cache.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_cache.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_ciphersuites_e315acda.o: ../../../third_party/mbedtls/library/ssl_ciphersuites.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_ciphersuites.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_client_eb479c5f.o: ../../../third_party/mbedtls/library/ssl_client.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_client.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_cookie_948970b8.o: ../../../third_party/mbedtls/library/ssl_cookie.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_cookie.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_debug_helpers_generated_c267799f.o: ../../../third_party/mbedtls/library/ssl_debug_helpers_generated.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_debug_helpers_generated.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_msg_bc5ffc37.o: ../../../third_party/mbedtls/library/ssl_msg.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_msg.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_ticket_289c4760.o: ../../../third_party/mbedtls/library/ssl_ticket.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_ticket.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_tls_bcbf9f31.o: ../../../third_party/mbedtls/library/ssl_tls.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_tls.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_tls12_client_c19bbda2.o: ../../../third_party/mbedtls/library/ssl_tls12_client.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_tls12_client.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_tls12_server_dda9fb1a.o: ../../../third_party/mbedtls/library/ssl_tls12_server.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_tls12_server.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_tls13_client_b5e52ec1.o: ../../../third_party/mbedtls/library/ssl_tls13_client.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_tls13_client.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_tls13_generic_895d726b.o: ../../../third_party/mbedtls/library/ssl_tls13_generic.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_tls13_generic.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_tls13_keys_9bbc7eea.o: ../../../third_party/mbedtls/library/ssl_tls13_keys.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_tls13_keys.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ssl_tls13_server_d1f36c39.o: ../../../third_party/mbedtls/library/ssl_tls13_server.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling ssl_tls13_server.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/threading_8ec62b81.o: ../../../third_party/mbedtls/library/threading.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling threading.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/timing_2dac1a4b.o: ../../../third_party/mbedtls/library/timing.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling timing.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/version_2a290fc1.o: ../../../third_party/mbedtls/library/version.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling version.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/version_features_ab5a6045.o: ../../../third_party/mbedtls/library/version_features.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling version_features.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x509_b90b5787.o: ../../../third_party/mbedtls/library/x509.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling x509.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x509_create_419af7e.o: ../../../third_party/mbedtls/library/x509_create.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling x509_create.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x509_crl_60c92025.o: ../../../third_party/mbedtls/library/x509_crl.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling x509_crl.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x509_crt_60c93e2d.o: ../../../third_party/mbedtls/library/x509_crt.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling x509_crt.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x509_csr_60c9ab0a.o: ../../../third_party/mbedtls/library/x509_csr.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling x509_csr.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x509write_c70ebbc2.o: ../../../third_party/mbedtls/library/x509write.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling x509write.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x509write_crt_39ba0ce8.o: ../../../third_party/mbedtls/library/x509write_crt.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling x509write_crt.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x509write_csr_39ba79c5.o: ../../../third_party/mbedtls/library/x509write_csr.c
	-$(V_AT)mkdir -p $(@D)
	@echo "Compiling x509write_csr.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

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
