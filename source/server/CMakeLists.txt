include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(zero_cached_SRCS
    container.cpp
    program_options.cpp
    server.cpp
    zero_cache.cpp)

add_executable(zero-cache ${zero_cached_SRCS})

if(UNIX)
    target_link_libraries(zero-cache common)
endif(UNIX)

install(TARGETS zero-cache DESTINATION bin)
