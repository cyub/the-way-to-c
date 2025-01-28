cmake_minimum_required(VERSION 3.5.0)
project(code-examples VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(libuv)

# 定义源文件列表
set(SOURCE_FILES
    read_allopt.c
    read_opt.c
    getopt.c
    getopt_long.c
    getopt_long_customopt.c
    getopt_long_mode.c
    getopt_remain.c
)

# 遍历源文件列表，为每个源文件添加可执行目标
foreach(SOURCE_FILE ${SOURCE_FILES})
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE) # 获取文件名称
    add_executable(${TARGET_NAME} ${SOURCE_FILE})
endforeach()
