cmake_minimum_required(VERSION 3.31)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# TODO: Put this section in a function
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME LANGUAGES CXX)
string(REPLACE " " "_" ProjectId ${ProjectId})# Set the project name using the above code.

project(${ProjectId} VERSION 0.0.1.0) # This is where you set your applications version
enable_language(CXX)

# Options Section.
option(USE_MOLD "Use mold linker instead of system default" OFF)

# Generates the compile_commands.json file, which is used
# by several outside packages and some IDEs.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make sure the compiler we are using can handle the standard we want to use.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++26" COMPILER_SUPPORTS_CXX26)
if (COMPILER_SUPPORTS_CXX26)
    set(CMAKE_CXX_STANDARD 26)
else ()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++26 support. Please use a different C++ compiler.")
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use mold for linking
if (USE_MOLD)
    find_program(HAVE_MOLD mold)
    if (HAVE_MOLD)
        message(STATUS "Using mold linker")
        add_link_options(-fuse-ld=mold)
    else ()
        message(STATUS "mold linker not found in system, using default linker")
    endif (HAVE_MOLD)
else ()
    message(STATUS "Using default linker")
endif (USE_MOLD)

# Subproject source files
set(PROJECT_SOURCES
        src/main.cpp
)

# Subproject header files
set(PROJECT_HEADERS
        ${CMAKE_BINARY_DIR}/config.h
)

# Clean up any duplicate source files that may have snuck in.
list(REMOVE_DUPLICATES "${PROJECT_SOURCES}")
list(REMOVE_DUPLICATES "${PROJECT_HEADERS}")

# Used for some IDEs (Visual Studio?)
source_group("${ProjectId}" FILES ${PROJECT_SOURCES})
source_group("${ProjectId}" FILES ${PROJECT_HEADERS})

# Lowercase the output binary file
string(TOLOWER ${ProjectId} ${ProjectId}_BINARY_NAME)

## Building the config.h file.
set(name ${CMAKE_PROJECT_NAME})

set(compiler_name ${CMAKE_CXX_COMPILER_ID})
set(compiler_version ${CMAKE_CXX_COMPILER_VERSION})
set(host_machine ${CMAKE_HOST_SYSTEM_NAME})
set(cpu_family ${CMAKE_HOST_SYSTEM_PROCESSOR})

set(major ${PROJECT_VERSION_MAJOR})
set(minor ${PROJECT_VERSION_MINOR})
set(patch ${PROJECT_VERSION_PATCH})
set(compile ${PROJECT_VERSION_TWEAK})

# Generate the config.h file.
configure_file(
        ${PROJECT_SOURCE_DIR}/src/config.h.in
        ${PROJECT_BINARY_DIR}/config.h
)

## Add the subprojects binary file to be compiled
add_executable(
        ${${ProjectId}_BINARY_NAME}
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
)

# Core source and header elements
target_include_directories(${${ProjectId}_BINARY_NAME} PRIVATE "${CMAKE_BINARY_DIR}")
target_include_directories(${${ProjectId}_BINARY_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src/")

# download CPM.cmake
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.8/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=78ba32abdf798bc616bab7c73aac32a17bbd7b06ad9e26a6add69de8f3ae4791
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# Use CPM to handle dependencies
#CPMAddPackage("gh:[Github Dependency Repo]@version")

# Target libraries
#set(PROJECT_LIBRARIES [Libraries Pulled In By CPM])
#target_link_libraries(${${ProjectId}_BINARY_NAME PRIVATE ${PROJECT_LIBRARIES})

# Target defines
#target_compile_definitions(${${ProjectId}_BINARY_NAME PRIVATE VARIABLE=VALUE)

# Shared compiler options
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    target_include_directories(${${ProjectId}_BINARY_NAME} SYSTEM PRIVATE "/usr/include")
    add_compile_options(-Wall -pipe -fPIC -fdiagnostics-color=always)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # using Clang
    target_compile_options(${${ProjectId}_BINARY_NAME} PRIVATE -Wall -Werror -Wpedantic -pipe -fPIC -fcolor-diagnostics -stdlib=libc++ -Wnon-gcc)

    target_include_directories(${${ProjectId}_BINARY_NAME} SYSTEM PRIVATE "/usr/include/c++/v1/")

    target_link_options(${${ProjectId}_BINARY_NAME} PRIVATE -stdlib=libc++ -lc++ -lc++abi)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # TODO: Microsoft Visual Studio C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    # TODO: Intel C++
endif ()
