find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUV REQUIRED libuv)

include_directories(${LIBUV_INCLUDE_DIRS})
link_directories(${LIBUV_LIBRARY_DIRS})

add_executable(helloword helloworld/main.c)
target_link_libraries(helloword ${LIBUV_LIBRARIES})

add_executable(default-loop default-loop/main.c)
target_link_libraries(default-loop ${LIBUV_LIBRARIES})

add_executable(idle-basic idle-basic/main.c)
target_link_libraries(idle-basic ${LIBUV_LIBRARIES})

add_executable(uvcat uvcat/main.c)
target_link_libraries(uvcat ${LIBUV_LIBRARIES})

add_executable(uvtee uvtee/main.c)
target_link_libraries(uvtee ${LIBUV_LIBRARIES})

add_executable(onchange onchange/main.c)
target_link_libraries(onchange ${LIBUV_LIBRARIES})

add_executable(timer-handle timer-handle/main.c)
target_link_libraries(timer-handle ${LIBUV_LIBRARIES})

add_executable(file-request file-request/main.c)
target_link_libraries(file-request ${LIBUV_LIBRARIES})

add_executable(sync-readwrite sync-readwrite/main.c)
target_link_libraries(sync-readwrite ${LIBUV_LIBRARIES})