include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})


set(get_test_SRCS
    get_test.cpp)

add_executable(get_test ${get_test_SRCS})

target_link_libraries(get_test zero_cache)

install(TARGETS get_test DESTINATION bin)


set(read_test_SRCS
    read_test.cpp)

add_executable(read_test ${read_test_SRCS})

target_link_libraries(read_test zero_cache)

install(TARGETS read_test DESTINATION bin)


set(array_test_SRCS
    array_test.cpp)

add_executable(array_test ${array_test_SRCS})

target_link_libraries(array_test zero_cache)

install(TARGETS array_test DESTINATION bin)
