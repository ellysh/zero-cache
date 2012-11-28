include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(thread_test_SRCS
    thread_test.cpp)

add_executable(thread_test ${thread_test_SRCS})

target_link_libraries(thread_test zero_cache)

install(TARGETS thread_test DESTINATION bin)
