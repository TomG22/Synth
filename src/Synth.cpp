#include "Synth.h"
#include <math.h>

Synth::Synth(AudioEngine& audioEngine) : m_audioEngine(audioEngine) {}

Voice& Synth::initSineNote(NoteName note) {
    const int SAMPLE_LEN = 48000;
    Voice sineVoice = Voice(note, SAMPLE_LEN, m_audioEngine.m_sampleRate);
    Voice& addedVoice = m_audioEngine.addVoice(sineVoice);

    return addedVoice;
}

void Synth::holdNote(NoteName note) {
    Voice* voice;
    if ((voice = m_audioEngine.getVoice(note))) {
        voice->m_isActive = true;
        voice->m_isPlaying = true;
        voice->m_currFrame = 0;
    } else {
        voice = &initSineNote(note);
    }
}


void Synth::releaseNote(NoteName note) {
    Voice* voice;
    if ((voice = m_audioEngine.getVoice(note))) {
        voice->m_isPlaying = false;
    }
}
