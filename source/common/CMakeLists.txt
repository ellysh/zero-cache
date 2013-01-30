include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(common_LIB_SRCS
    answer.cpp
    connection.cpp
    debug.cpp
    functions.cpp
    request.cpp
    socket.cpp
    speaker.cpp
    thread.cpp)

add_library(common STATIC ${common_LIB_SRCS})

if(UNIX)
    target_link_libraries(common pthread ${ZMQ_LIBRARY})
endif(UNIX)

install(FILES
            connection.h
            debug.h
            types_zcache.h
            socket.h
        DESTINATION include/${PROJECT_NAME})
