#ifndef __AUDIO_RESAMPLER_H
#define __AUDIO_RESAMPLER_H

#include <samplerate.h>
#include <sndfile.h>
#include <queue>

class AudioResampler {

    private:
        double ratio;
        SRC_STATE *state;
        SF_VIRTUAL_IO virtual_io;
        SF_INFO sf_info;
        SNDFILE *snd_file;        

        SNDFILE *snd_file_out;
        SF_VIRTUAL_IO virtual_io_out;

    public:
        std::queue<unsigned char> internal_buffer;
        std::queue<unsigned char> output_buffer;
        
    public:

        AudioResampler(int sample_rate_in, int sample_rate_out,int channels);
        void bufferize(unsigned char* data_in, int size);
        void process();
        unsigned char * flush(int *written);
        ~AudioResampler();

        static sf_count_t vio_get_filelen(void *user_data);
        static sf_count_t vio_seek(sf_count_t offset, int whence, void *user_data) ;
        static sf_count_t vio_tell(void *user_data);
        static sf_count_t vio_read(void *ptr, sf_count_t count, void *user_data);
        static sf_count_t vio_write(const void *ptr, sf_count_t count, void *user_data);

};

#endif
