include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(zero_cached_SRCS
    container.cpp
    port_counter.cpp
    key_list.cpp
    program_options.cpp
    reactor.cpp
    registrar.cpp
    zero_cache.cpp)

add_executable(zero-cache ${zero_cached_SRCS})

if(UNIX)
    target_link_libraries(zero-cache common ${ZMQ_LIBRARY} ${CZMQ_LIBRARY})
endif(UNIX)

install(TARGETS zero-cache DESTINATION bin)
