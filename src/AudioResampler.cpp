#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "AudioResampler.h"

#define SAMPLES_PER_STEP 12000

AudioResampler::AudioResampler(int sample_rate_in, int sample_rate_out, int channels)
{
    int error;

    // Initialize audioresample
    ratio = (double)sample_rate_out / (double)sample_rate_in;
    state = src_new(SRC_SINC_FASTEST, channels, &error);   

    if (error > 0) {
        std::cerr << src_strerror(error);
    }


}

void AudioResampler::pcm_to_float(float *out_float, int size)
{
    int i;
    unsigned char byte1, byte2;
    unsigned short int sample;
    short int sample2;
    float div = (float)1.0/(float)32768.0;

    for (i = 0 ; i < size ; i++) {
       
        byte1 = internal_buffer.front();
        internal_buffer.pop();

        byte2 = internal_buffer.front();
        internal_buffer.pop();

        sample = (unsigned short)(byte2 << 8);
        sample += byte1;
        sample2 = sample;
        
        out_float[i] = div * (float)sample2;
    
    }
}

void AudioResampler::float_to_pcm(float *in_float, int size)
{
    int i;
    char byte1, byte2;
    
    float mul = 32768.0;

    short int tmp;
    unsigned short int tmp2;

    for (i = 0 ; i < size; i++) {
        tmp = (int)(mul*in_float[i]);
        if (tmp < -32768) tmp = -32768;
        if (tmp > 32767) tmp = 32767;
        
        tmp2 = tmp;

        byte1 = (tmp2 & 0xFF);
        byte2 = ( tmp2 >> 8 ) & 0x00FF;

        output_buffer.push(byte1);
        output_buffer.push(byte2);
    }
}

void AudioResampler::process()
{


    SRC_DATA src_data;
    int sf_count = internal_buffer.size() / 2;
    int i;
    int j = 0;
    short in_short[SAMPLES_PER_STEP];
    short out_short[SAMPLES_PER_STEP];

    float in_float[SAMPLES_PER_STEP];
    float out_float[SAMPLES_PER_STEP];

    unsigned char* output;

    pcm_to_float(in_float, sf_count);

    src_data.data_in = in_float;
    src_data.data_out = out_float;
    src_data.input_frames = sf_count;
    src_data.output_frames = SAMPLES_PER_STEP;
    src_data.src_ratio = ratio;

    int error = src_process(state, &src_data);

    if (error < 0) {
        std::cerr << " Error in process "  << src_strerror(error);
        return ;
    }

    int samples_out = (int)src_data.output_frames_gen;
    
    float_to_pcm(out_float, samples_out );


    //std::cerr << "Resulting samples " << samples_out << "\n";

}


/**
 * Fill internal buffer
 */
void AudioResampler::bufferize(unsigned char *buffer, int size)
{
    int i = 0;

    for (i = 0; i < size; i++) {
        internal_buffer.push(buffer[i]);
    }
}

/** 
 *Flush the internal_output buffer
 */
 

unsigned char* AudioResampler::flush(int *written) {

    int size = output_buffer.size();
    unsigned char* result = (unsigned char*)malloc(size);

    for (int i = 0 ; i < size ; i++) {
        result[i] = output_buffer.front();
        output_buffer.pop();
    }
    (*written) = size;
    return result;
}


/** 
 * Free resources
 */
 
AudioResampler::~AudioResampler() {
    src_delete(state);
}
/*
int main(int argc, char**argv)
{
    AudioResampler* resampler = new AudioResampler(48000,16000, 2);

    FILE *input = fopen("1.raw", "r");
    int readed = 0, written;

    unsigned char buffer[2048];

    while (( readed = fread(buffer, 1, 2048, input)) > 0) {

        resampler->bufferize(buffer, readed);
        
        resampler->process();
        unsigned char *result = resampler->flush(&written);

        if (result != NULL) {
            fwrite(result, 1, written , stdout);
            free(result);
        }
    }
    

}
*/
