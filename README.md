# Tempered
This project is fork from original devlopment made here: 
https://github.com/edorfaus/TEMPered

It contains many patches sourced from various others git repository and pull
requests from origin repository. 

It should support allmost all known PC Sensors devices.

There is also included as submodule a temper git repository which contain a python implementation. 
It is not used at all, just included if needed to test or implement new devices. 

# Compilation on Debian

Packages/Software required: 

* cmake
* libhidapi-dev
* g++


# Original Readme
This project is a C implementation of a library and program to read all the
various types of TEMPer thermometer and hygrometer USB devices, as produced by
RDing Technology and sold under the name PCsensor.

This is, of course, complicated by the fact that I currently only have one
variant of those devices myself, namely the TEMPerV1.2 USB HID device, and by
them creating a whole bunch of technically different devices under the same
names - yet often reusing the same hardware (including USB IDs) for different
devices with different features.

Hence, only a few of the devices are currently supported, but I'm working to
add support for as many as I can, as quickly as I can. I will need help here.

See the DEVICES file for more information on the currently known devices and
how well they work (if at all).


In addition to the library itself, this project includes these utilities:
- enumerate: lists the recognized devices attached to the system
- tempered : reads the sensors of either all found devices, or those specified
    as parameters, and prints the readings to standard output.
- hid-query: sends an arbitrary query to a user-specified HID device, and
    prints the returned result as hex bytes. This is mostly useful when adding
    support for new devices or during debugging, and can be a little dangerous.

There are also some examples for how to use the library in the examples
directory, for those who want or need to write their own custom program.


To build this project, you'll need to have a built copy of HIDAPI[1] on your
system somewhere, and a working installation of the CMake[2] build system.

First, you either run make in the top-level directory, or create a build
directory and run cmake yourself - then change into the build dir and run make.



[1] The HIDAPI library can be found here: http://www.signal11.us/oss/hidapi/
with source on GitHub here: https://github.com/signal11/hidapi
This project uses features not available in version 0.6; use 0.7 or newer.

If your system has a dev package for it, that should work, if not, you'll have
to build it yourself (I suggest in a "hidapi" dir next to the "TEMPered" dir,
as the autodetection will look for it there). This will probably require the
-dev packages for libudev and/or libusb-1.0.


[2] If CMake is not available in your distro's package system, it can be found
here: http://www.cmake.org/
This project is using version 2.8, but might be compatible with some earlier
versions - 2.8 is what my system has, so I haven't tested anything older.
