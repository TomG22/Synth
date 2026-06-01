#pragma once

#include <array>
#include <stdint.h>

#include "miniaudio.h"
#include "Voice.h"

class AudioEngine {
    public:
        static constexpr size_t MAX_VOICES = 64;

        std::array<Voice, MAX_VOICES> m_voices;
        ma_device m_device;

        float m_sampleRate = 48000.0f;
        uint32_t m_channels = 2;

        AudioEngine();
        ~AudioEngine();

        Voice* getVoice(NoteName note);
        Voice& addVoice(Voice& voice);
        void callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

    private:
};
