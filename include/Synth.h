#pragma once

#include "AudioEngine.h"

class Synth {
    public:
        Synth(AudioEngine&);
        double noteNameToFreq(NoteName note);
        void initSineNote(NoteName note);
        void holdNote(NoteName note);
        void releaseNote(NoteName note);
    private:
        AudioEngine& m_audioEngine;
};
