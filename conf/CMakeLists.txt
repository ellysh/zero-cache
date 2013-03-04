install(FILES zero-cache.conf DESTINATION /etc/ld.so.conf.d)
install(FILES zero-cache.pc DESTINATION /usr/lib/pkgconfig)
install(FILES 70-zero-cache.rules DESTINATION /etc/udev/rules.d)
