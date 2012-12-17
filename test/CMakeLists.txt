include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})


set(get_test_SRCS
    get_test.cpp)

add_executable(get_test ${get_test_SRCS})

target_link_libraries(get_test zero_cache)

install(TARGETS get_test DESTINATION bin)


set(speed_test_SRCS
    speed_test.cpp)

add_executable(speed_test ${speed_test_SRCS})

target_link_libraries(speed_test zero_cache)

install(TARGETS speed_test DESTINATION bin)


set(memory_leak_test_SRCS
    memory_leak_test.cpp)

add_executable(memory_leak_test ${memory_leak_test_SRCS})

target_link_libraries(memory_leak_test zero_cache)

install(TARGETS memory_leak_test DESTINATION bin)


set(read_test_SRCS
    read_test.cpp)

add_executable(read_test ${read_test_SRCS})

target_link_libraries(read_test zero_cache)

install(TARGETS read_test DESTINATION bin)


set(cross_test_SRCS
    cross_test.cpp)

add_executable(cross_test ${cross_test_SRCS})

target_link_libraries(cross_test zero_cache)

install(TARGETS cross_test DESTINATION bin)


set(tcp_test_SRCS
    tcp_test.cpp)

add_executable(tcp_test ${tcp_test_SRCS})

target_link_libraries(tcp_test zero_cache)

install(TARGETS tcp_test DESTINATION bin)
