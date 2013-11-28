#ifndef __AUDIO_RESAMPLER_H
#define __AUDIO_RESAMPLER_H

#include <samplerate.h>
#include <queue>

class AudioResampler {

    private:
        double ratio;
        SRC_STATE *state;


    private:
        std::queue<unsigned char> internal_buffer;
        std::queue<unsigned char> output_buffer;
        
    public:

        AudioResampler(int sample_rate_in, int sample_rate_out,int channels);
        void bufferize(unsigned char* data_in, int size);
        void process();
        unsigned char * flush(int *written);
        void pcm_to_float(float *out_float, int size);
        void float_to_pcm(float *in_float, int size);
        ~AudioResampler();
};

#endif
