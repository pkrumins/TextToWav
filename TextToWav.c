#include <stdio.h>
#include "loqtts.h"

int main(int argc, char **argv)
{ 
    ttsHandleType hReader;
    ttsResultType r;

    char *voice, *inputTextFile, *outputWavFile;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <VoiceName> <InputTextFile> <OutputWavFile>\n", argv[0]);
        return 1;
    }

    voice = argv[1];
    inputTextFile = argv[2];
    outputWavFile = argv[3];

    r = ttsNewReader(&hReader, NULL);
    if (r != tts_OK) { 
        fprintf(stderr, "%s\n", ttsGetErrorMessage(r));
        ttsDeleteSession(NULL);
        return r;
    }
    
    r = ttsLoadPersona(hReader, voice, NULL, NULL);
    if (r != tts_OK) {
        fprintf(stderr, "%s\n", ttsGetErrorMessage(r));
        ttsDeleteSession(NULL);
        return r;
    }

    r = ttsSetSpeed(hReader, 40);
    if (r != tts_OK) {
        fprintf(stderr, "%s\n", ttsGetErrorMessage(r));
        ttsDeleteSession(NULL);
        return r;
    }

    r = ttsSetAudio(
        hReader,
        "LTTS7AudioFile",
        outputWavFile,
        32000,
        tts_LINEAR,
        tts_STEREO,
        NULL
    );

    if (r != tts_OK) {
        fprintf(stderr, "%s\n", ttsGetErrorMessage(r));
        ttsDeleteSession(NULL);
        return r;
    }

    r = ttsRead(
        hReader,
        inputTextFile,
        ttsFALSE, /* bAsync */
        ttsTRUE,  /* bFromFile */
        NULL
    );

    if (r != tts_OK) {
        fprintf(stderr, "%s\n", ttsGetErrorMessage(r));
        ttsDeleteSession(NULL);
        return 1;
    }

    ttsDeleteSession(NULL);
    return 0;
}

