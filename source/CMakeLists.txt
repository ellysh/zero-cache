exec_program("uname -r" OUTPUT_VARIABLE UNAME)

install(FILES
            server/zero_cache.ko
            DESTINATION /lib/modules/${UNAME}/kernel/lib)

install(FILES
            server/zero_cache.h
            DESTINATION include/${PROJECT_NAME})

add_subdirectory(client)
add_subdirectory(common)
