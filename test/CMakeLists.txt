include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})


set(reactor_test_SRCS
    reactor_test.cpp)

add_executable(reactor_test ${reactor_test_SRCS})

target_link_libraries(reactor_test zero_cache)

install(TARGETS reactor_test DESTINATION bin)


set(get_test_SRCS
    get_test.cpp)

add_executable(get_test ${get_test_SRCS})

target_link_libraries(get_test zero_cache)

install(TARGETS get_test DESTINATION bin)
