Basic C++ Boiler Plate using the Meson/Ninja Build System 

Basic startup
meson setup buildDir
meson compile -C buildDir

To use clang++ on Linux
meson setup --native-file profiles/clang-linux.ini
meson compile -C buildDir

To use gcc on Linux
meson setup --native-file profiles/gcc-linux.ini
meson compile -C buildDir

