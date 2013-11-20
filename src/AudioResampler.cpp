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

    // Initialize sndfile
    virtual_io.read = AudioResampler::vio_read;
    virtual_io.write = NULL;
    virtual_io.seek = AudioResampler::vio_seek;
    virtual_io.tell = AudioResampler::vio_tell;
    virtual_io.get_filelen = AudioResampler::vio_get_filelen;


    sf_info.samplerate = sample_rate_in;
    sf_info.channels = channels;
    sf_info.format = SF_FORMAT_RAW | SF_FORMAT_PCM_16;
    sf_info.seekable = 0;    
    snd_file = sf_open_virtual(&virtual_io, SFM_READ, &sf_info, this);

    if (snd_file == NULL) {
        sf_perror(snd_file);
    }

    SF_INFO sf_info_out;
    sf_info_out.samplerate = sample_rate_out;
    sf_info_out.channels = channels;
    sf_info_out.format = SF_FORMAT_RAW | SF_FORMAT_PCM_16;
    sf_info_out.seekable = 0;

    virtual_io_out.read = NULL;
    virtual_io_out.write = AudioResampler::vio_write;
    virtual_io_out.seek = AudioResampler::vio_seek;
    virtual_io_out.tell = AudioResampler::vio_tell;
    virtual_io_out.get_filelen = AudioResampler::vio_get_filelen;   
    snd_file_out = sf_open_virtual(&virtual_io_out, SFM_WRITE, &sf_info_out, this);

    if (snd_file_out == NULL) {
        sf_perror(snd_file_out);
    }

}

void AudioResampler::process()
{


    SRC_DATA src_data;
    sf_count_t sf_count;
    int i;
    int j = 0;
    short in_short[SAMPLES_PER_STEP];
    short out_short[SAMPLES_PER_STEP];

    float in_float[SAMPLES_PER_STEP];
    float out_float[SAMPLES_PER_STEP];

    unsigned char* output;

    sf_count = sf_read_float(snd_file, in_float, internal_buffer.size() / 2);

    if (sf_count < 0) {
        sf_perror(snd_file);
    }

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
    
    sf_writef_float(snd_file_out, out_float, samples_out / 2);


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
 * SNDFILE buffer read function
 */
sf_count_t AudioResampler::vio_read(void* ptr, sf_count_t count, void *user_data) 
{


    AudioResampler *resampler = (AudioResampler*)user_data;

    //std::cerr << "vio_read, count=" << count << ", buffersize= " << resampler->internal_buffer.size() << "\n";

    unsigned char* cast_ptr = (unsigned char*) ptr;

    int j = 0,i, size = resampler->internal_buffer.size();
    for (i = 0; i < count && i < size ; i++)
    {
        cast_ptr[i] = resampler->internal_buffer.front();
        resampler->internal_buffer.pop();
        j++;
    }
    return j;
}

/**
 * SNDFILE buffer write function
 */
sf_count_t AudioResampler::vio_write(const void* ptr, sf_count_t count, void *user_data)
{
    AudioResampler *resampler = (AudioResampler*)user_data;

    unsigned char *cast_ptr = (unsigned char*) ptr;
    
    int i;

    for (i = 0; i < count; i++) {
        resampler->output_buffer.push(cast_ptr[i]);
    }

    return count;
}
/**
 * SNDFILE dummy get file length
 */
sf_count_t AudioResampler::vio_get_filelen(void *user_data){
    std::cerr << "Call to dummy get_filelen \n";
    return 1024*1024*10;
}

/**
 * SNDFILE dummy seek
 */
sf_count_t AudioResampler::vio_seek(sf_count_t offset, int whence, void *user_data) {
    std::cerr << "Call to dummy seek\n";
    return 0;
}

/**
 * SNDFILE dummy tell
 */
sf_count_t AudioResampler::vio_tell(void *user_data){
    std::cerr << "Call to dummy tell \n";
    return 0;
}

/** 
 * Free resources
 */
 
AudioResampler::~AudioResampler() {
    src_delete(state);
    sf_close(snd_file);
    sf_close(snd_file_out);
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
