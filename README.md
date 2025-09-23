# MIDITHRU Program.
---
Currently only for Windows (2025/09/23)<br>
I will add linux feature with alsa sequencer.<br>
I don't know about mac.

## How to use
Asuming you have copied the program to a recognized path, but don't. just replace "**midithru**" with "**./midithru.exe**" or wherever the program is.
1. List devices
    ```
    $ midithru -l
    ```
    to display midi input & output devices' IDs.

2. Select and run
    ```
    $ midithru -i (inputId) -o (outputId)
    ```
    to select according devices and run the thru program.
    It will print the messages to the terminal.

3. Quit
    type
    ```
    q
    ```
    to get out of the program.

0. Example
    ```
    // list devices
    $  ./midithru -l
    MIDI Input devices:
        ID 0: microKEY2 Air 1 KEYBOARD
        ID 1: 2- Steinberg UR24C-1
        ID 2: Midinous Thru Port
        ID 3: Midinous Clock Port
        ID 4: Midinous Port

    MIDI Output devices:
        ID 0: Microsoft GS Wavetable Synth
        ID 1: microKEY2 Air 1 CTRL
        ID 2: 2- Steinberg UR24C-1
        ID 3: Midinous Clock Port
    
    // select and run the thru
    $ ./midithru -i 0 -o 2
    MIDI Thru active (input=0 => output=2).
    Press 'q' to quit.
    MIDI IN: status=Note On, data1=60, data2=100
    RAW dwParam1 = 0x00503C90
    ...
    ```