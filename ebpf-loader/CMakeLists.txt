cmake_minimum_required(VERSION 3.20)

project(ebpf_loader
    LANGUAGES C
)

find_path(LIBBPF_INCLUDE_DIR
    NAMES bpf/libbpf.h
    REQUIRED
)

find_library(LIBBPF_LIBRARY
    NAMES bpf
    REQUIRED
)

set(EBPF_SOURCE
    ${CMAKE_SOURCE_DIR}/src/bpf/exec_trace.bpf.c
)

find_program(CLANG_EXECUTABLE clang REQUIRED)

set(EBPF_OBJECT
    ${CMAKE_BINARY_DIR}/bpf/exec_trace.bpf.o
)

add_custom_command(
    OUTPUT ${EBPF_OBJECT}
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_BINARY_DIR}/bpf

    COMMAND ${CLANG_EXECUTABLE}
    -O2
    -g
    -target bpf
    -I/usr/include/x86_64-linux-gnu
    -c
    ${EBPF_SOURCE}
    -o ${EBPF_OBJECT}

    DEPENDS ${EBPF_SOURCE}

    COMMENT "Compiling eBPF program: exec_trace.bpf.c"
)

add_custom_target(ebpf_program ALL
    DEPENDS ${EBPF_OBJECT}
)

add_executable(ebpf_loader
    src/user/loader.c
)

target_compile_definitions(ebpf_loader PRIVATE
    BPF_OBJECT_PATH="${EBPF_OBJECT}"
)

target_include_directories(ebpf_loader PRIVATE
    ${LIBBPF_INCLUDE_DIR}
)

target_link_libraries(ebpf_loader PRIVATE
    ${LIBBPF_LIBRARY}
)