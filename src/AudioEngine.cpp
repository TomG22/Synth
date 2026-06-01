#define MA_IMPLEMENTATION
#define MA_NO_DECODING
#define MA_NO_ENCODING

#include <stdio.h>

#include "AudioEngine.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    auto* self = static_cast<AudioEngine*>(pDevice->pUserData);

    if (self) {
        self->callback(pDevice, pOutput, pInput, frameCount);
    }
}

AudioEngine::AudioEngine() {
    ma_device_config config = ma_device_config_init(ma_device_type_playback);

    config.playback.format   = ma_format_f32;
    config.playback.channels = 2;
    config.sampleRate        = 48000;
    config.dataCallback      = data_callback;
    config.pUserData = this;

    if (ma_device_init(NULL, &config, &m_device) != MA_SUCCESS) {
        printf("Failed to open device.\n");
        exit(1);
    }

    m_sampleRate = (float)m_device.sampleRate;
    m_channels   = m_device.playback.channels;

    ma_device_start(&m_device);
}

AudioEngine::~AudioEngine() {
    ma_device_uninit(&m_device);
}

Voice* AudioEngine::getVoice(NoteName note) {
    for (Voice& voice : m_voices) {
        if (voice.m_note == note) {
            return &voice;
        }
    }

    return nullptr;
}

Voice& AudioEngine::addVoice(Voice voice) {
    for (size_t i = 0; i < MAX_VOICES; i++) {
        if (!m_voices[i].m_isActive) {
            m_voices[i] = voice;
            return m_voices[i];
        }
    }

    // Would implement voice stealing here to replace the longest playing voice
    // For now, just replace the first voice
    m_voices[MAX_VOICES - 1] = voice;

    return m_voices[MAX_VOICES - 1];
}

void AudioEngine::callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    float* out = (float*)pOutput;
    ma_uint32 channels = pDevice->playback.channels;
    ma_uint32 sampleRate = pDevice->sampleRate;

    for (ma_uint32 i = 0; i < frameCount; ++i) {
        float mixedSample = 0.0f;

        for (auto& voice : m_voices) {
            // Skip inactive voices
            if (!voice.m_isActive) continue;

            mixedSample += voice.genSample();
        }

        // Prevent clipping
        if (mixedSample > 0.95f) mixedSample = 0.95f;
        if (mixedSample < -0.95f) mixedSample = -0.95f;

        // Mono audio
        for (ma_uint32 ch = 0; ch < channels; ++ch)
            out[i * channels + ch] = mixedSample;
    }
    (void)pInput;
}

