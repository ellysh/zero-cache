include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(zero_cache_LIB_SRCS
    client.cpp
    client_typed.cpp)

add_library(zero_cache SHARED ${zero_cache_LIB_SRCS})

if(UNIX)
    target_link_libraries(zero_cache common)
endif(UNIX)

install(TARGETS zero_cache DESTINATION lib/${PROJECT_NAME})

install(FILES
            client.h
            client_typed.h
        DESTINATION include/${PROJECT_NAME})
