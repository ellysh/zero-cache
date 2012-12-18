#ifndef SPEAKER_H
#define SPEAKER_H

namespace zero_cache
{

enum ErrorType
{
    kSocketTypeError = 0,
    kSocketNameError
};

class Speaker
{
public:
    static Speaker* Instance();

    void PrintError(ErrorType error);

private:
    static Speaker* instance_;

    Speaker() {};
};

}

#endif
