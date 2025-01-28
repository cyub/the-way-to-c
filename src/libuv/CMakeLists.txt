# 查找 libuv 库
find_package(libuv REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(helloword helloworld/main.c)
target_link_libraries(helloword PRIVATE libuv::uv)

add_executable(default-loop default-loop/main.c)
target_link_libraries(default-loop PRIVATE libuv::uv)

add_executable(idle-basic idle-basic/main.c)
target_link_libraries(idle-basic PRIVATE libuv::uv)

add_executable(uvcat uvcat/main.c)
target_link_libraries(uvcat PRIVATE libuv::uv)

add_executable(uvtee uvtee/main.c)
target_link_libraries(uvtee PRIVATE libuv::uv)

add_executable(onchange onchange/main.c)
target_link_libraries(onchange PRIVATE libuv::uv)