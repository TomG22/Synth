#include <iterator>
#include <vector>
#include <math.h>

enum NoteName {
    C0, CsDb0, D0, DsEb0, E0, F0, FsGb0, G0, GsAb0, A0, AsBb0, B0,
    C1, CsDb1, D1, DsEb1, E1, F1, FsGb1, G1, GsAb1, A1, AsBb1, B1,
    C2, CsDb2, D2, DsEb2, E2, F2, FsGb2, G2, GsAb2, A2, AsBb2, B2,
    C3, CsDb3, D3, DsEb3, E3, F3, FsGb3, G3, GsAb3, A3, AsBb3, B3,
    C4, CsDb4, D4, DsEb4, E4, F4, FsGb4, G4, GsAb4, A4, AsBb4, B4,
    C5, CsDb5, D5, DsEb5, E5, F5, FsGb5, G5, GsAb5, A5, AsBb5, B5,
    C6, CsDb6, D6, DsEb6, E6, F6, FsGb6, G6, GsAb6, A6, AsBb6, B6,
    C7, CsDb7, D7, DsEb7, E7, F7, FsGb7, G7, GsAb7, A7, AsBb7, B7,
    C8, CsDb8, D8, DsEb8, E8, F8, FsGb8, G8, GsAb8, A8, AsBb8, B8,
    C9, CsDb9, D9, DsEb9, E9, F9, FsGb9, G9, GsAb9, A9, AsBb9, B9,
    C10, CsDb10, D10, DsEb10, E10, F10, FsGb10, G10, GsAb10, A10, AsBb10, B10, DUMMY_NOTE
};


class Voice {
public:
    NoteName m_note = DUMMY_NOTE;
    unsigned long m_totalFrames = 0;
    unsigned long m_currFrame = 0;
    int m_sampleRate = 48000;
    bool m_isActive = false;
    bool m_isPlaying = false;

    Voice(NoteName note, unsigned long totalSamples, int sampleRate);
    Voice() = default; // Needed for initializing the voices array
    float genSample();
    static float noteToFreq(NoteName note);
};
