include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(common_LIB_SRCS
    answer.cpp
    connection.cpp
    debug.cpp
    functions.cpp
    package.cpp
    request.cpp
    socket.cpp
    speaker.cpp
    thread.cpp)

add_library(common STATIC ${common_LIB_SRCS})

if(UNIX)
    target_link_libraries(common pthread ${ZMQ_LIBRARY})
endif(UNIX)

install(FILES
            answer.h
            connection.h
            debug.h
            package.h
            socket.h
            types_zcache.h
        DESTINATION include/${PROJECT_NAME})
