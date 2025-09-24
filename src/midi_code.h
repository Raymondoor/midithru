#ifndef MIDI_CODE_H
#define MIDI_CODE_H

#ifdef _WIN32
    #include <windows.h>
    #include <mmsystem.h>
#elif defined(__linux__) || defined(__APPLE__)
    // include whatever
#endif // OS specific
#ifndef BYTE
    typedef unsigned char BYTE;
#endif

typedef struct{
    BYTE status;
    BYTE data[2];
}MidiMessage;

typedef enum{
    // Default to Channel 1
    NOTE_OFF = 0x80,
    NOTE_ON = 0x90,
    POLY_KEY_PRESSURE = 0xA0,
    CONTROL_CHANGE = 0xB0,
    PROGRAM_CHANGE = 0xC0,
    CHANNEL_PRESSURE = 0xD0,
    PITCH_BEND = 0xE0,
    SYSTEM_EXCLUSIVE = 0xF0 // 240, 11110000
}Status;

typedef enum{
    CH01, CH02, CH03, CH04, CH05, CH06, CH07, CH08, CH09, CH10, CH11, CH12, CH13, CH14, CH15, CH16
}Channel;

typedef enum{
    BANK_SELECT = 0x00, // 0, 00000000
    MODULATION = 0x01,
    CHANNEL_VOLUME = 0x07, // 7, 00000111
    DAMPER_PEDAL = 0x40 // 64, 00100000
}ControlNumber;

typedef enum{
    CSWITCH_OFF = 0x00,
    CSWITCH_ON = 0x7F // 127, 01111111
}ControlSwitch;

typedef enum{
    // Most are guesses
    VEL_DEFAULT = 0x40, // 64
    VEL_STANDARD = 0x64, // 100
    VEL_MAX = 0x7F, // 127
    VEL_MIN = 0x00, // 0

    VEL_PPP = 0x01, // 1
    VEL_PP = 0xC0, // 12
    VEL_P = 0x24, // 36
    VEL_MP = 0x34, // 52
    VEL_MF = 0x40, // 64
    VEL_F = 0x50, // 80
    VEL_FF = 0x68, // 104
    VEL_FFF = 0x7F, // 127
}Velocity;

typedef enum{
    NT_C4 = 0x3c,
    NT_C5 = NT_C4 + 12,
    NT_C6 = NT_C4 + 24,
    NT_C7 = NT_C4 + 36,
    NT_G9 = 0x7f,
}Note;
const char *statusToString(BYTE status);
// out short msg in correct order, by little-endian
unsigned long midiShortMsg4bytes(MidiMessage message);
// change the message to note_off
unsigned long midiShortMsg4bytesChangeToNoteOff(MidiMessage *pMessage);

#endif // MIDI_CODE_H