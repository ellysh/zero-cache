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

    void PrintError(const ErrorType error) const;

private:
    static Speaker* instance_;

    Speaker() {};
};

}

#endif
