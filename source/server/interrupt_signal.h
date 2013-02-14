#include <signal.h>

namespace zero_cache
{

#define ERR_INTERRUPT   0x4

static bool gIsInterrupt = false;

static void SignalHandler(int signal_value)
{
    gIsInterrupt = true;
}

static void AssignSignalHandler(void)
{
    struct sigaction action;
    action.sa_handler = SignalHandler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
}

}
