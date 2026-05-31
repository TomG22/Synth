#include "AudioEngine.h"
#include "Synth.h"

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>


int main() {
    // The audio engine starts its stream upon initialization
    AudioEngine ae = AudioEngine();

    // Dummy synth used to test the audioengine
    Synth synth = Synth(ae);

    // Dummy controller loop used to trigger inputs to the synth
    printf("ADSR Synth\n");
    printf("Press 1-9 + ENTER to trigger/release note\n");
    printf("Press 'q' + ENTER to quit\n\n");

    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line.empty()) continue;

        char key = line[0];
        if (key == 'q' || key == 'Q') break;

        if (key >= '1' && key <= '9') {
            NoteName note = static_cast<NoteName>(static_cast<int>(NoteName::C4) + (key - '1'));

            bool foundNote = false;

            for (Voice& voice : ae.m_voices) {
                if (voice.m_note == note) {
                    foundNote = true;
                    if (voice.m_isPlaying) {
                        synth.releaseNote(note);
                        printf("Stopping voice: %i\n", note);
                    } else {
                        synth.holdNote(note);
                        printf("Playing voice: %i\n", note);
                    }
                }
            }

            if (!foundNote) {
                synth.initSineNote(note);
                synth.holdNote(note);
                printf("Playing voice: %i\n", note);
            }
        } else {
            printf("Unmapped key: %c\n", key);
        }
    }


    return 0;
}
