%module AACDecompress
%{
#include "AACDecompress.h"
%}


class AACDecompress {

    public:
        AACDecompress();
        unsigned char* decompress(unsigned char *data, int size, int *out_size);
        unsigned char* terminate(int *out_size);
        ~AACDecompress();
        unsigned long samplerate;
        unsigned char channels;

};

%module AudioResampler
%{
#include "AudioResampler.h"
%}


class AudioResampler {


    public:
        
        AudioResampler(int sample_rate_in, int sample_rate_out,int channels);
        void bufferize(unsigned char* data_in, int size);
        void process();
        unsigned char * flush(int *written);
        ~AudioResampler();

};

