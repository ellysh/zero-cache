Zero Cache 2.2 version
======================

INTRODUCTION
------------

Zero Cache is a open source, high-performance, kernel space memory caching system.

Zero Cache is able to store data of any type that are addressed by
index numbers. It provides the minimal response time thanks to direct memory
copying between the user space and kernel space.

BUILDING
--------

You need the CMake build system, C++ and C compilers to build this software.

1. Generate makefiles with CMake build system.<br/>
Type one of these commands to build debug or release versions of the zero-cache:

    $ cmake -D CMAKE_BUILD_TYPE=Debug CMakeLists.txt

    $ cmake -D CMAKE_BUILD_TYPE=Release CMakeLists.txt

2. Build binaries with C++ and C compilers:

    $ make

3. Build debian package if you use Debian-based Linux distribution:

    $ make deb

You can find debian packages in the `zero-cache/bin/deb` directory.

INSTALLING
----------

Debian-based Linux distribution users can install debian packages from
`zero-cache/bin/deb` directory.

Another way is installing with Makefile default mechanism:

    $ make install

USAGE
-----

First of all you must load the server zero-cache module into your kernel:

    $ insmod source/server/zero_cache.ko

The `zero_cache` device file will be created at the `/dev` directory. Now the
zero-cache server is ready to work.

You can interact with zero-cache server directly with `ioctl` function. Another
way is usage `Client` interface class for your C++ applications.

EXAMPLES
--------

This is example of typical C++ client application:

    #include <zero-cache/typed_client.h>

    using namespace zero_cache;

    int main()
    {
        TypedClient client;

        size_t index = 0;
        long data = 1024;

        client.Writelong(index, data);

        long result = client.ReadLong(index);

        return 0;
    }

This is example of typical C client application:

    #include <zero-cache/zero_cache.h>

    int main()
    {
        int dev_file;

        dev_file = open(DEVICE_FILE_NAME, 0);

        long data;
        data = 1024;

        Package package;
        package.index = 0;
        memcpy(&package.data, data, PACKAGE_DATA_SIZE);

        ioctl(dev_file, IOCTL_WRITE_VALUE, &package);

        long result;

        package.index = 0;
        ioctl(dev_file, IOCTL_READ_VALUE, &package);
        memcpy(result, &package.data, PACKAGE_DATA_SIZE);

        close(dev_file);

        return 0;
    }

COPYING
-------

Free use of this software is granted under the terms of the GNU Lesser General
Public License (LGPL). For details see the file `LICENSE` included with the zero-cache distribution.
