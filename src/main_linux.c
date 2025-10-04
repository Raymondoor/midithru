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

snd_seq_t *open_client();
int main(){
    snd_seq_t *handle = open_client();
    printf("%d", snd_seq_client_id(handle));
    return 0;
}
snd_seq_t *open_client(){
        snd_seq_t *handle;
        int err;
        err = snd_seq_open(&handle, "default", SND_SEQ_OPEN_INPUT, 0);
        if (err < 0)
                return NULL;
        snd_seq_set_client_name(handle, "My Client");
    return handle;
}