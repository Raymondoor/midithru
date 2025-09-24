// several code was generated using AI. I will replace all with my code after I get the hang of C and midi stuff in each OS
// The code here will not run properly yet. This is in development, manly for linux.
#include <stdio.h>
#include <string.h>
#include "./midi_code.h"
#include "./midi_smf.h"

#ifdef _WIN32
    #include <windows.h> // Other basic stuff
    #include <mmsystem.h> // Actual midi stuff
    #include <conio.h>  // for _kbhit() and _getch()
#elif defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    #include <alsa/asoundlib.h>
#endif // OS specific
#ifndef BYTE
    typedef unsigned char BYTE;
#endif


// Callback: forward MIDI messages
void CALLBACK thru(HMIDIIN hMidiIn, UINT wMsg,
                   DWORD_PTR dwInstance, DWORD dwParam1, DWORD dwParam2) {
    if (wMsg == MIM_DATA) {
        HMIDIOUT out = (HMIDIOUT)(DWORD_PTR)dwInstance;

        // Unpack the MIDI message
        BYTE status = (BYTE)(dwParam1 & 0xFF);
        BYTE data1  = (BYTE)((dwParam1 >> 8) & 0xFF);
        BYTE data2  = (BYTE)((dwParam1 >> 16) & 0xFF);

        // Print it
        printf("MIDI IN: status=%s, data1=%d, data2=%d\n", statusToString(status), data1, data2);
        printf("RAW dwParam1 = 0x%08lX\n", dwParam1);

        // Forward it to output
        MMRESULT r = midiOutShortMsg(out, dwParam1);
        if (r != MMSYSERR_NOERROR) {
            printf("midiOutShortMsg error: %d\n", r);
        }
    }
}

// Show available MIDI devices
void listDevices() {
    UINT numIn = midiInGetNumDevs();
    UINT numOut = midiOutGetNumDevs();
    MIDIINCAPS inCaps;
    MIDIOUTCAPS outCaps;

    printf("MIDI Input devices:\n");
    for(UINT i = 0; i < numIn; i++){
        if(midiInGetDevCaps(i, &inCaps, sizeof(inCaps)) == MMSYSERR_NOERROR){
            printf("  ID %u: %s\n", i, inCaps.szPname);
        }
    }

    printf("\nMIDI Output devices:\n");
    for(UINT i = 0; i < numOut; i++){
        if(midiOutGetDevCaps(i, &outCaps, sizeof(outCaps)) == MMSYSERR_NOERROR){
            printf("  ID %u: %s\n", i, outCaps.szPname);
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    HMIDIIN Input;
    HMIDIOUT Output;
    MMRESULT res;
    int inID = -1, outID = -1;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            inID = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outID = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-l") == 0) {
            listDevices();
            return 0;
        } else {
            printf("Usage: %s -i <inputID> -o <outputID>\n", argv[0]);
            printf("       %s -l   (list devices)\n", argv[0]);
            return 1;
        }
    }

    if (inID < 0 || outID < 0) {
        printf("You must specify both -i and -o.\n");
        listDevices();
        return 1;
    }

    // Open output
    res = midiOutOpen(&Output, outID, 0, 0, CALLBACK_NULL);
    if (res != MMSYSERR_NOERROR) {
        printf("Error opening output device %d\n", outID);
        return 1;
    }
    MidiMessage test = {NOTE_ON | CH01, {NT_C4, VEL_STANDARD}};
    midiOutShortMsg(Output, midiShortMsg4bytes(test)); // Note On, channel 1, note 60, velocity 100
    Sleep(500);
    midiOutShortMsg(Output, midiShortMsg4bytesChangeToNoteOff(&test)); // Note Off, same note

    // Open input, pass output handle as instance
    res = midiInOpen(&Input, inID, (DWORD_PTR)thru, (DWORD_PTR)Output, CALLBACK_FUNCTION);
    if (res != MMSYSERR_NOERROR) {
        printf("Error opening input device %d\n", inID);
        midiOutClose(Output);
        return 1;
    }

    // Start receiving
    midiInStart(Input);
    printf("MIDI Thru active (input=%d => output=%d).\n", inID, outID);
    printf("Press 'q' to quit.\n");

    // Main loop
    int running = 1;
    while(running){
        // only works for windows atm
        if(_kbhit()){
            int c = _getch();
            if(c == 'q' || c == 'Q'){
                running = 0;
            }
        }
        Sleep(50);
    }
    // Cleanup
    midiInStop(Input);
    midiInClose(Input);
    midiOutReset(Output);
    midiOutClose(Output);

    printf("MIDI Thru stopped.\n");
    return 0;
}