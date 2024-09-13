project(
    'Project', # Change Me
    'cpp',
    version: '0.0.0', # This is overridden in the conf_data section
    default_options: ['cpp_std=c++20', 'warning_level=3', 'buildtype=debug'],
    meson_version: '>=1.4.1',
)

executable_name = 'project' # Change Me
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

project_src = [
    'src/main.cpp',
]

project_include_directories = [
    include_directories('src/'),
]

project_cpp_args = []
project_link_args = []
math = cpp.find_library('m', required: false)

project_deps = [math]

if cpp_family == 'gcc'
    project_cpp_args += ['-fdiagnostics-color=always']
    project_include_directories += [include_directories('/usr/include/')]
elif cpp_family == 'clang'
    project_cpp_args += ['-fcolor-diagnostics', '-stdlib=libc++', '-Wnon-gcc']

    project_include_directories += [
        include_directories('/usr/include/c++/v1/'),
    ]

    project_link_args += [
        '-lc++',
        '-lc++abi',
    ]

else
    # Do something else for MSVC?
endif

project = executable(
    executable_name,
    project_src,
    install: true,
    dependencies: project_deps,
    include_directories: project_include_directories,
    cpp_args: project_cpp_args,
    link_args: project_link_args,
)

install_data('LICENSE', install_dir: join_paths('share/doc', executable_name))
