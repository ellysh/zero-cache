#include "reactor.h"

#include <iostream>
#include <algorithm>

using namespace std;
using namespace zero_cache;

char* GetOption(char** begin, char** end, const string & option)
{
    char ** itr = find(begin, end, option);

    if ( (itr != end) && (++itr != end) )
        return *itr;
    else
        return 0;
}

bool IsOptionExist(char** begin, char** end, const string& option)
{
    return find(begin, end, option) != end;
}

void PrintUsage()
{
    cout << "Usage: zero_cached [options]" << endl;
    cout << "Options:" << endl;
    cout << "\t-c CONNECTION\t\tSet connection string" << endl;
    cout << "\t-l FILE\t\t\tSet log file name" << endl;
    cout << "\t-h\t\t\tPrint option help" << endl;
}

int main(int argc, char *argv[])
{
    if ( IsOptionExist(argv, argv+argc, "-h") )
    {
        PrintUsage();
        return 1;
    }

    string log_file = "";
    if ( IsOptionExist(argv, argv+argc, "-l") )
        log_file = GetOption(argv, argv+argc, "-l");

    string connection = "tcp://*:5570";
    if ( IsOptionExist(argv, argv+argc, "-c") )
        connection = GetOption(argv, argv+argc, "-c");

    Reactor reactor(log_file, connection);

    reactor.Start();

    return 0;
}
