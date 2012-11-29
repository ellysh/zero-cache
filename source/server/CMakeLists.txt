include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(zero_cached_SRCS
    container.cpp
    debug.cpp
    debug_client.cpp
    reactor.cpp
    zero_cached)

add_executable(zero_cached ${zero_cached_SRCS})

if(UNIX)
    target_link_libraries(zero_cached pthread ${Boost_LIBRARIES} ${ZMQ_LIBRARY} ${CZMQ_LIBRARY})
endif(UNIX)

install(TARGETS zero_cached DESTINATION bin)
