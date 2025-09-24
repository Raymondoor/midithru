#include "midi_code.h"

const char *statusToString(BYTE status){
    switch(status & 0xF0){  // mask off the channel
        case NOTE_OFF:          return "Note Off";
        case NOTE_ON:           return "Note On";
        case POLY_KEY_PRESSURE: return "Poly Key Pressure";
        case CONTROL_CHANGE:    return "Control Change";
        case PROGRAM_CHANGE:    return "Program Change";
        case CHANNEL_PRESSURE:  return "Channel Pressure";
        case PITCH_BEND:        return "Pitch Bend";
        case SYSTEM_EXCLUSIVE:  return "System Exclusive";
        default:                return "Unknown";
    }
}

// out short msg in correct order, by little-endian
unsigned long midiShortMsg4bytes(MidiMessage message){
    return (0x00 << 24) | (message.data[1] << 16) | (message.data[0] << 8) | (message.status);
}
unsigned long midiShortMsg4bytesChangeToNoteOff(MidiMessage *pMessage){
    pMessage->status = (NOTE_OFF & 0xF0) | (pMessage->status & 0x0F);
    return (0x00 << 24) | (pMessage->data[1] << 16) | (pMessage->data[0] << 8) | (pMessage->status);
}