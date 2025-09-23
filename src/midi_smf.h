#include <stdio.h>
#include <string.h>
#include "./midi_code.h"
#include "./midi_gm1.h"
#ifndef MIDI_SMF_H
#define MIDI_SMF_H

typedef struct{
    unsigned char chunkTypeH[4];
    unsigned char lengthH[4];
    unsigned char formatH[2];
    unsigned char ntrksH[2];
    unsigned char divisionH[2];
}SmfHeader;
typedef struct{
    unsigned char chunkType[4];
    unsigned char length[4];
    // I don't quite understand the docs, it says chnks are 14 bytes, but also says <MTrk event> can be one or more, which I take it as being exceeding 14 bytes
    unsigned char event[6];
}SmfTrack;
SmfHeader makeEmptyHeader(){
    SmfHeader h = {
        {'M','T','h','d'},
        {0x00,0x00,0x00,0x06},
        {0x00,0x00},
        {0x00,0x01},
        {0x01,0xE0}
    };
    return h;
}
SmfHeader makeHeader(const unsigned char format, const unsigned char ntrks, const unsigned char division1, const unsigned char division2){
    SmfHeader h = {
        {'M','T','h','d'},
        {0x00,0x00,0x00,0x06},
        {0x00,format},
        {0x00,ntrks},
        {division1,division2}
    };
    return h;
}

FILE* fopenMidi(const char *filename, const char *mode){
    FILE *f = fopen(filename, mode);
    if(!f){
        perror("Failed to fopen MIDI file");
        return NULL;
    }
    // Only check header if reading
    if(mode[0] == 'r'){
        char header[4];
        if(fread(header, 1, 4, f) != 4 || strncmp(header, "MThd", 4) != 0){
            fprintf(stderr, "Not a valid MIDI file: %s\n", filename);
            fclose(f);
            return NULL;
        }
        // rewind so caller starts at beginning
        rewind(f);
    }
    return f;
}

#endif