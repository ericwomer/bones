
project(
    'Barebones',
    'cpp',
    version : '0.0.0', # This is oveverridden in the conf_data section
    default_options:
    [
        'cpp_std=c++17',
        'warning_level=1'
    ],
    meson_version: '>=0.48.0'
    )

executable_name = 'bones'
pkgconfig = import('pkgconfig')
cpp = meson.get_compiler('cpp')

bones_src = [
    'src/main.cpp'
    ]

bones_include_directories = [
    include_directories('src/') # , Shouldn't have to hardcode in libc++'s include dir
    # include_directories('/usr/lib/llvm-8/include/c++/v1/')
    ]

bones_cflags = [
    '-stdlib=libc++'
    ]

bones_ldflags = [
    '-lc++',
    '-lc++abi'
    ]

math = cpp.find_library('m', required: false)

bones_deps = [
    math
    ]

bones = executable(
    executable_name,
    bones_src,
    dependencies: bones_deps,
    include_directories: bones_include_directories,
    cpp_args: bones_cflags,
    link_args: bones_ldflags
)

