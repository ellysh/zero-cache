include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(zero_cached_SRCS
    container.cpp
    reactor.cpp
    reactor_loop.cpp
    zero_cached.cpp)

add_executable(zero_cached ${zero_cached_SRCS})

if(UNIX)
    target_link_libraries(zero_cached common ${ZMQ_LIBRARY} ${CZMQ_LIBRARY})
endif(UNIX)

install(TARGETS zero_cached DESTINATION bin)
