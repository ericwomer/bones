project(
    'Project', # Change Me
    'cpp',
    version: '0.0.0', # This is overridden in the conf_data section
    default_options: ['cpp_std=c++26', 'warning_level=3', 'buildtype=debug'],
    meson_version: '>=1.4.1',
)

executable_name = meson.project_name() # Change Me

pkgconfig = import('pkgconfig')
cpp = meson.get_compiler('cpp')
cpp_family = cpp.get_id()

conf_data = configuration_data()
conf_data.set('name', meson.project_name())

conf_data.set('compiler_name', cpp.get_id())
conf_data.set('compiler_version', cpp.version())
conf_data.set('host_machine', host_machine.system())
conf_data.set('cpu_family', build_machine.cpu_family())

conf_data.set('major', '0')
conf_data.set('minor', '0')
conf_data.set('patch', '1')
conf_data.set('compile', '0')

configure_file(
    input: 'src/config.h.in',
    output: 'config.h',
    configuration: conf_data,
)

source = [
    'src/main.cpp',
]

includes = [
    include_directories('src/'),
]

cxxflags = []
ldflags = []

math = cpp.find_library('m', required: false)

deps = [math]

if cpp_family == 'gcc'
    cxxflags += ['-fdiagnostics-color=always']
    includes += [include_directories('/usr/include/')]
elif cpp_family == 'clang'
    cxxflags += ['-fcolor-diagnostics', '-stdlib=libc++', '-Wnon-gcc']

    includes += [
        include_directories('/usr/include/c++/v1/'),
    ]

  if get_option('nognu')
    ldflags += [
      '-L' + get_option('libcxx_prefix') + '/lib',
      '-Wl,--rpath=' + get_option('libcxx_prefix') + '/lib',
      '-stdlib=libc++',
      '--rtlib=compiler-rt',
      '--unwindlib=libunwind',
      '-lc++',
      '-lc++abi',
      '-lunwind'
    ]
  else 
    ldflags += [
      '-stdlib=libc++',
      '-lc++',
      '-lc++abi'
      ]
  endif


else
    # Do something else for MSVC?
endif

project = executable(
    executable_name,
    source,
    install: true,
    dependencies: deps,
    include_directories: includes,
    cpp_args: cxxflags,
    link_args: ldflags,
)

install_data('LICENSE', install_dir: join_paths('share/doc', executable_name))
