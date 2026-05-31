#include "Synth.h"
#include <math.h>

Synth::Synth(AudioEngine& audioEngine) : m_audioEngine(audioEngine) {}

void Synth::initSineNote(NoteName note) {
    const int SAMPLE_LEN = 48000;
    Voice sineVoice = Voice(note, SAMPLE_LEN, m_audioEngine.m_sampleRate);
    m_audioEngine.addVoice(sineVoice);
}

void Synth::holdNote(NoteName note) {
    for (Voice& voice : m_audioEngine.m_voices) {
        if (voice.m_note == note) {
            voice.m_isActive = true;
            voice.m_isPlaying = true;
            voice.m_currFrame = 0;
        }
    }
}


void Synth::releaseNote(NoteName note) {
    for (Voice& voice : m_audioEngine.m_voices) {
        if (voice.m_note == note) {
            voice.m_isPlaying = false;
        }
    }
}
