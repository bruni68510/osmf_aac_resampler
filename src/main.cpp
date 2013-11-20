#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "AACDecompress.h"
#include "AudioResampler.h"

/**
 * Helper to resampler
 */
void resampler_to_output(AudioResampler *resampler, FILE *fd, unsigned char*buffer, int size)
{

    int written;
    resampler->bufferize(buffer, size);
    resampler->process();
    unsigned char * result = resampler->flush(&written);

    
    if (result != NULL) {
        fwrite(result, 1, written, fd);
        free(result);
    }
}

/**
 * The main programm takes any aac file
 * decrypt it the convert raw audio to samplerate 44100
 */
int main(int argc, char ** argv)
{

    
    FILE* fd_in = stdin;
    FILE* fd_out = stdout;

    unsigned char buffer[188];
    int read;
    int written;

    AACDecompress* decompressor = new AACDecompress();
    AudioResampler* resampler = NULL;

    while ((read = fread(buffer, 1,188, fd_in)) > 0) {
        unsigned char * output = decompressor->decompress(buffer,read,&written);
        if (output != NULL) {

            if (resampler == NULL) {
                std::cerr << "samplerate = " << decompressor->samplerate << " channels = " << (int)decompressor->channels << "\n";
                resampler = new AudioResampler(decompressor->samplerate,44100, decompressor->channels);
            }
            resampler_to_output(resampler, fd_out, output, written);
            free(output);
        }
    }

    unsigned char * output = decompressor->terminate(&written);
    if(output != NULL) {
        //resampler_to_output(resampler, fd_out, output, written);
        free(output);
    } 

    delete(decompressor);
    delete(resampler);

}

