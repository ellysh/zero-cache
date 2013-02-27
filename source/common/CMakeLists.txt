include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(common_LIB_SRCS
    connection.cpp
    debug.cpp
    functions.cpp
    package.cpp
    speaker.cpp)

add_library(common STATIC ${common_LIB_SRCS})

if(UNIX)
    target_link_libraries(common pthread ${ZMQ_LIBRARY})
endif(UNIX)

install(FILES
            connection.h
            debug.h
            package.h
            types_zcache.h
        DESTINATION include/${PROJECT_NAME})
