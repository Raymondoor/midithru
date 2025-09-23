#include "./midi_code.h"
#ifndef MIDI_GM1_H
#define MIDI_GM1_H

typedef enum{
    PERC_CH = CH10
}InstrumentChannel;
typedef enum{
    Acoustic_Grand_Piano,
    Bright_Acoustic_Piano,
    // all the rest
    Gunshot = 127
}GMPatch;
#endif