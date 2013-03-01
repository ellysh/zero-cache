include_directories(${COMMON_INCLUDE_DIRS})
link_directories(${COMMON_LIBDIR})

set(common_LIB_SRCS
    debug.cpp
    package.cpp
    thread.cpp)

add_library(common STATIC ${common_LIB_SRCS})

if(UNIX)
    target_link_libraries(common pthread)
endif(UNIX)

install(FILES
            debug.h
            package.h
            types_zcache.h
        DESTINATION include/${PROJECT_NAME})
