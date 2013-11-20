
/**
 * This class will decompress aac input buffer to wav 
 */

#include <neaacdec.h>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>

class AACDecompress {

    NeAACDecFrameInfo hInfo;
    NeAACDecHandle hAac;
    NeAACDecConfigurationPtr conf;

    std::queue<unsigned char> stream_queue;
 
    bool initialized;

    //int buffersize;
    int stage;
    int framecount;
    unsigned long framelength;
    unsigned long remaining;

    public:
        AACDecompress();
        unsigned char* decompress(unsigned char *data, int size, int *out_size);
        unsigned char* terminate(int *out_size);
        ~AACDecompress();
        unsigned long samplerate;
        unsigned char channels;

};
