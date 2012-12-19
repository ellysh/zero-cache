include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(common_LIB_SRCS
    connection.cpp
    debug.cpp
    functions.cpp
    socket.cpp
    speaker.cpp)

add_library(common STATIC ${common_LIB_SRCS})

if(UNIX)
    target_link_libraries(common pthread ${ZMQ_LIBRARY} ${CZMQ_LIBRARY})
endif(UNIX)

install(FILES
            connection.h
            debug.h
            types_zcache.h
            socket.h
        DESTINATION include/${PROJECT_NAME})
