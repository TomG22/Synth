#include <numbers>

#include "Voice.h"

Voice::Voice(NoteName note, unsigned long totalFrames, int sampleRate) :  m_note(note), m_totalFrames(totalFrames), m_sampleRate(sampleRate) {}


float Voice::noteToFreq(NoteName note) {
    return 440.0 * pow(2.0f, (note - A4) / 12.0f);
}

float Voice::genSample() {
    // Stop the active voice if it's done playing
    if (m_currFrame >= m_totalFrames) {
        m_isActive = false;
        return 0.0;
    }
            
    float sample;
    if (m_isPlaying) {
        // This is where the base generator would be used.
        // We're just going to use sine for now
        sample = sin(static_cast<float>(m_currFrame) / m_sampleRate * 2.0f * std::numbers::pi_v<float> * noteToFreq(m_note));
    } else {
        sample = sin(static_cast<float>(m_currFrame) / m_sampleRate * 2.0f * std::numbers::pi_v<float> * noteToFreq(m_note));
    }

    m_currFrame++;

    return sample;
}
