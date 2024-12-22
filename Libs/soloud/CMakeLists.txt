add_library(SoLoud STATIC)

set_target_properties(SoLoud PROPERTIES LINKER_LANGUAGE CXX)

target_compile_options(SoLoud PRIVATE -Wno-unused-value)

# Include directories

target_include_directories(SoLoud PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/
)

# Source files

target_sources(SoLoud PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_audiosource.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_bassboostfilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_biquadresonantfilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_bus.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_c.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_dcremovalfilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_echofilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_error.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_fader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_fft.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_fftfilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_file.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_file_hack_off.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_file_hack_on.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_filter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_flangerfilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_freeverbfilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_lofifilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_misc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_monotone.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_noise.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_openmpt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_queue.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_robotizefilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_sfxr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_speech.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_tedsid.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_thread.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_vic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_vizsn.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_wav.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_waveshaperfilter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include/soloud_wavstream.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/monotone/soloud_monotone.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/noise/soloud_noise.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/openmpt/soloud_openmpt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/openmpt/soloud_openmpt_dll.c
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/sfxr/soloud_sfxr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/speech/darray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/speech/darray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/speech/klatt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/speech/klatt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/speech/resonator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/speech/resonator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/speech/soloud_speech.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/speech/tts.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/speech/tts.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/tedsid/sid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/tedsid/sid.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/tedsid/soloud_tedsid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/tedsid/ted.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/tedsid/ted.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/vic/soloud_vic.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/vizsn/soloud_vizsn.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/wav/dr_flac.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/wav/dr_impl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/wav/dr_mp3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/wav/dr_wav.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/wav/soloud_wav.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/wav/soloud_wavstream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/wav/stb_vorbis.c
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/audiosource/wav/stb_vorbis.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/backend/miniaudio/miniaudio.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/backend/miniaudio/soloud_miniaudio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_audiosource.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_bus.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_core_3d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_core_basicops.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_core_faderops.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_core_filterops.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_core_getters.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_core_setters.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_core_voicegroup.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_core_voiceops.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_fader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_fft.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_fft_lut.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_file.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_filter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_misc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_queue.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/core/soloud_thread.cpp
)

# Macro Definitions

target_compile_definitions(SoLoud PRIVATE WITH_MINIAUDIO)

target_compile_definitions(SoLoud PRIVATE _CRT_SECURE_NO_WARNINGS)