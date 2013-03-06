include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})


set(get_test_SRCS
    get_test.cpp)

add_executable(get_test ${get_test_SRCS})

target_link_libraries(get_test zero_cache)

install(TARGETS get_test DESTINATION bin)


set(stress_value_test_SRCS
    stress_value_test.cpp)

add_executable(stress_value_test ${stress_value_test_SRCS})

target_link_libraries(stress_value_test zero_cache)

install(TARGETS stress_value_test DESTINATION bin)


set(array_test_SRCS
    array_test.cpp)

add_executable(array_test ${array_test_SRCS})

target_link_libraries(array_test zero_cache)

install(TARGETS array_test DESTINATION bin)


set(stress_array_test_SRCS
    stress_array_test.cpp)

add_executable(stress_array_test ${stress_array_test_SRCS})

target_link_libraries(stress_array_test zero_cache)

install(TARGETS stress_array_test DESTINATION bin)
