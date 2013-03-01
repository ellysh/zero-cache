include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})


set(get_test_SRCS
    get_test.cpp)

add_executable(get_test ${get_test_SRCS})

target_link_libraries(get_test zero_cache)

install(TARGETS get_test DESTINATION bin)
