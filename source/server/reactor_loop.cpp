#include "reactor_loop.h"

#include <czmq.h>
#include <iostream>

#include "container.h"
#include "debug.h"
#include "types.h"

using namespace std;
using namespace zero_cache;

static const int kThreadCreationDelay = 1000 * 1000;

static Command GetCommand(zframe_t* frame)
{
    Command command = kSet;
    zframe_t* set_frame = zframe_new(&command, sizeof(Command));

    if ( zframe_eq(frame, set_frame) )
        command = kSet;
    else
       command = kGet;

    zframe_destroy(&set_frame);

    return command;
}

void* zero_cache::ReactorLoop(void* reactor_args)
{
    /* FIXME: Split this function to sub-functions */
    ReactorArgs* args = static_cast<ReactorArgs*>(reactor_args);

    while (true)
    {
        if ( zmq_poll(args->items, 1, -1) == -1 )
            args->debug->Log() << "ReactorLoop() - error = " << zmq_strerror(zmq_errno()) << endl;

        if ( args->items[0].revents & ZMQ_POLLIN )
        {
            zmsg_t* msg = zmsg_recv(args->socket);
            assert( msg != NULL );
            zframe_t* command = zmsg_pop(msg);
            zframe_t* key = zmsg_pop(msg);

            if ( GetCommand(command) == kSet )
            {
                zframe_t* data = zmsg_pop(msg);
                char* key_str = zframe_strdup(key);
                //args->debug->Log() << "set: key = " << zframe_strdup(key) << " data = " << zframe_strhex(data) << endl;
                args->container->WriteData(string(key_str), data);
                free(key_str);
                zframe_destroy(&data);
            }

            if ( GetCommand(command) == kGet )
            {
                //args->debug->Log() << "get: key = " << zframe_strdup(key);
                zframe_t* data = args->container->ReadData(zframe_strdup(key));

                if ( data == NULL )
                    data = zframe_new(NULL, 0);

                //args->debug->Log() << " data = " << zframe_strhex(data) << endl;
                zframe_send(&data, args->socket, 0);
            }

            zframe_destroy(&key);
            zframe_destroy(&command);
            zmsg_destroy(&msg);
        }
    }
    zctx_destroy(&args->context);
}
