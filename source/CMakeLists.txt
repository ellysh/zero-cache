exec_program("uname -r" OUTPUT_VARIABLE UNAME)

install(FILES server/zero_cache.ko DESTINATION /lib/modules/${UNAME}/kernel/lib)

add_subdirectory(client)
add_subdirectory(common)
