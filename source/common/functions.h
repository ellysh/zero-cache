#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace zero_cache
{

static std::string FrameToString(zframe_t* frame)
{
    char* buffer =  zframe_strdup(frame);
    std::string result = buffer;
    free(buffer);

    return result;
}

}

#endif
