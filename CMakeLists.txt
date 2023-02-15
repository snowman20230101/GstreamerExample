cmake_minimum_required(VERSION 3.16)
project(gstreamerExample)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    set(gst_root_dir /usr/lib/x86_64-linux-gnu)

    include_directories(
            /usr/include/gstreamer-1.0
            /usr/include/glib-2.0
            /usr//lib/x86_64-linux-gnu/glib-2.0/include
    )
endif ()

include_directories(
        src/common
        src/stream
)

message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME} ")
message("CMAKE_HOST_SYSTEM: ${CMAKE_HOST_SYSTEM} ")

message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} ")
message("CMAKE_SYSTEM: ${CMAKE_SYSTEM} ")

message("CMAKE_HOST_UNIX: ${CMAKE_HOST_UNIX} ")
message("CMAKE_HOST_WIN32: ${CMAKE_HOST_WIN32} ")

#将第三方库作为动态库引用
add_library(gstreamer SHARED IMPORTED)
add_library(gst_base SHARED IMPORTED)
add_library(glib SHARED IMPORTED src/stream/Gstream_push_rtmp.cpp src/stream/Gstream_push_rtmp.h)
add_library(gobject SHARED IMPORTED)

#指定第三方库的绝对路径
set_target_properties(gstreamer PROPERTIES IMPORTED_LOCATION ${gst_root_dir}/libgstreamer-1.0.so)
set_target_properties(gst_base PROPERTIES IMPORTED_LOCATION ${gst_root_dir}/libgstbase-1.0.so)
set_target_properties(glib PROPERTIES IMPORTED_LOCATION ${gst_root_dir}/libglib-2.0.so)
set_target_properties(gobject PROPERTIES IMPORTED_LOCATION ${gst_root_dir}/libgobject-2.0.so)

add_executable(gstreamerExample main.cpp
        src/common/Logger.cpp src/common/Logger.h
        src/common/Timestamp.cpp src/common/Timestamp.h
        src/stream/GstreamerPusherRtmp.cpp src/stream/GstreamerPusherRtmp.h)

target_link_libraries(gstreamerExample gstreamer gst_base glib gobject)
