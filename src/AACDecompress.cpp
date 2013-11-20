/**
 * This class will decompress aac input buffer to wav 
 */

#include "AACDecompress.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>


AACDecompress::AACDecompress() {

    // Zero hInfo
     memset(&hInfo, 0, sizeof hInfo);

    // create decode handler
    hAac = NeAACDecOpen();

    conf = NeAACDecGetCurrentConfiguration(hAac);

    //std::cerr << "Sample format = " << (int)conf->outputFormat << "\n";

    initialized = false;

    stage = 0;
    framelength = 0;
    framecount = 0;
}


unsigned char * AACDecompress::decompress(unsigned char *data, int in_size, int *out_size)
{


    long i = 0;

    unsigned char *ptr = 0;

    unsigned char *output_char;
    std::queue<unsigned char> output;

    ptr = data;

    while(in_size > 0 ){
        //std::cout << "stage = " << stage << " in_size = " << in_size <<  "ptr = " << (int)ptr[0] << "\n";
        if (stage == 0)  {
            if (ptr[0] == 0xff) {
                stage = 1;
                stream_queue.push(ptr[0]);
            }
            ptr++;
            in_size--;
        }
        else if (stage == 1)
        {
            if ((ptr[0] & 0xf0) == 0xf0) 
            {
                stream_queue.push(ptr[0]);
                stage = 2;
            }
            else {
                stream_queue.pop();       
                stage = 0;                   
            }
            ptr++;
            in_size--;
        }
        else if (stage == 2) {
            stream_queue.push(ptr[0]);
            stage = 3;
            ptr++;
            in_size--;
        }
        else if (stage == 3) {
            stream_queue.push(ptr[0]);
            stage = 4;
            framelength = (ptr[0] & 0x03) << 11;
            ptr++;
            in_size--;
        }
        else if (stage == 4) {
            stream_queue.push(ptr[0]);
            stage = 5;
            framelength += ptr[0] << 3;
            ptr++;
            in_size--;
        }
        else if (stage == 5) {
            stream_queue.push(ptr[0]);
            stage = 6;
            framelength += (ptr[0] & 0xe0) >> 5;
            //std::cerr << "Framelength is " << framelength;
            ptr++;
            in_size--;
        }
        else if (stage == 6) {
            stream_queue.push(ptr[0]);
            stage = 7;
            remaining = framelength - 7;
            ptr++;
            in_size--;
        }
        else if (stage == 7) {
            if (remaining > 0) {
                remaining --;
                stream_queue.push(ptr[0]);
                ptr++;
                in_size--;
            }
            else if (framecount < 2) {
                stage = 0;
                framecount ++;
            }
            else {

                framecount --;
                int queue_size = stream_queue.size();
                unsigned char in_data[queue_size];

                for (i = 0 ; i < queue_size; i++) {
                    in_data[i] = stream_queue.front();
                    stream_queue.pop();
                }

                //hexdump("in_data", (void*)in_data, queue_size);
                if (!initialized) {
                    long err =  NeAACDecInit(hAac, in_data, queue_size, &samplerate,&channels);
                    if (err != 0) {
                        std::cerr << "Init error " << err << "\n";

                        stage = 0;
                    }
                    else {
                        initialized = true;
                    }
                }
                if (initialized)
                {
                    unsigned char *tmpbuffer;
                    tmpbuffer = (unsigned char*) NeAACDecDecode(hAac, &hInfo,in_data,queue_size);
                    if ((hInfo.error == 0) && (hInfo.samples > 0))
                    {
                        for (i = hInfo.bytesconsumed; i < queue_size; i++) {
                            stream_queue.push(in_data[i]);
                        }
                        for (i = 0 ; i < hInfo.samples * 2; i++) {
                            output.push(tmpbuffer[i]);
                        }       
                    } else if (hInfo.error != 0) {
                        std::cerr << "Decompress error " << hInfo.error << "\n";
                        stage = 0;
                    }           
                }
                remaining = 0;
            }
        }
    }
    if (output.size() == 0) {
        out_size[0] = 0;
        return NULL;
    }
    else {
        int len = output.size();
        out_size[0] = len;
        output_char = (unsigned char*)malloc(output.size() );
        for (i = 0 ; i < len ; i++) {
            output_char[i] = output.front();
            output.pop();
        } 
        return output_char;
    }
}

unsigned char* AACDecompress::terminate(int *out_size) {
    
    int i;
    std::queue<unsigned char>output;
    unsigned char* output_char;

 
    if (!initialized) {
        return NULL;
    }

    int queue_size = stream_queue.size();
    unsigned char in_data[queue_size];

    for (i = 0 ; i < queue_size; i++) {
        in_data[i] = stream_queue.front();
        stream_queue.pop();
    }

    unsigned char*tmpbuffer;
    tmpbuffer = (unsigned char*) NeAACDecDecode(hAac, &hInfo,in_data,queue_size);
    if ((hInfo.error == 0) && (hInfo.samples > 0))
    {
        for (i = 0 ; i < hInfo.samples * 2; i++) {
            output.push(tmpbuffer[i]);
        }
    } else if (hInfo.error != 0) {
        std::cerr << "Decompress error " << hInfo.error << "\n";
        return NULL;
    }
    int len = output.size();
    out_size[0] = len;
    output_char = (unsigned char*)malloc(output.size() );
    for (i = 0 ; i < len ; i++) {
        output_char[i] = output.front();
        output.pop();
    }
    return output_char;
}    

AACDecompress::~AACDecompress()
{
     NeAACDecClose(hAac);
}
/*
int main(int argc, char** argv)
{
    FILE* input = fopen("1.aac","r");

    unsigned char buffer[188];
    int read;
    int written;

    AACDecompress* decompressor = new AACDecompress();

    while ((read = fread(buffer, 1,188, input)) > 0) {
        unsigned char * output = decompressor->decompress(buffer,read,&written);
        if (output != NULL) {
            fwrite(output, 1, written, stdout);
            free(output);
        }
    }

    unsigned char * output = decompressor->terminate(&written);
    if(output != NULL) {
        fwrite(output,1,written, stdout);
        free(output);
    } 

    delete(decompressor);
}
*/
