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

add_executable(tcp-server tcp-server/main.c)
target_include_directories(tcp-server PRIVATE ${CMAKE_BINARY_DIR}/include) # 将生成的 config.h 文件添加到编译中

add_executable(tcp-client tcp-client/main.c)
target_include_directories(tcp-client PRIVATE ${CMAKE_BINARY_DIR}/include)

add_executable(udp-server udp-server/main.c)
target_include_directories(udp-server PRIVATE ${CMAKE_BINARY_DIR}/include)

add_executable(udp-client udp-client/main.c)
target_include_directories(udp-client PRIVATE ${CMAKE_BINARY_DIR}/include)

add_executable(tcp-echo-server tcp-echo-server/main.c)
target_link_libraries(tcp-echo-server ${LIBUV_LIBRARIES})

add_executable(tcp-echo-client tcp-echo-client/main.c)
target_link_libraries(tcp-echo-client ${LIBUV_LIBRARIES})

add_executable(udp-dhcp udp-dhcp/main.c)
target_link_libraries(udp-dhcp ${LIBUV_LIBRARIES})

add_executable(dns dns/main.c)
target_link_libraries(dns ${LIBUV_LIBRARIES})

add_executable(interfaces interfaces/main.c)
target_link_libraries(interfaces ${LIBUV_LIBRARIES})

add_executable(if interfaces/if.c)

add_executable(queue-work queue-work/main.c)
target_link_libraries(queue-work ${LIBUV_LIBRARIES})
