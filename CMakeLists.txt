cmake_minimum_required(VERSION 3.16)
project(gstreamerExample)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        src/common
        src/stream
        src/basictutorials
)

# linux 平台
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    #
    set(gstreamer_dir /usr/lib/x86_64-linux-gnu)

    include_directories(
            /usr/include/gstreamer-1.0
            /usr/include/glib-2.0
            /usr/include/gtk-3.0
            /usr/lib/x86_64-linux-gnu/glib-2.0/include # Special introduction
            /usr/include/atk-1.0
            /usr/include/pango-1.0
            /usr/include/cairo
            /usr/include/harfbuzz
            /usr/include/gdk-pixbuf-2.0
    )

    # 将第三方库作为动态库引用
    add_library(gstreamer SHARED IMPORTED)
    add_library(gst_base SHARED IMPORTED)
    add_library(gst_pbutils SHARED IMPORTED)
    add_library(gst_video SHARED IMPORTED)
    add_library(gst_audio SHARED IMPORTED)
    add_library(gst_net SHARED IMPORTED)

    #指定第三方库的绝对路径
    set_target_properties(gstreamer PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgstreamer-1.0.so)
    set_target_properties(gst_base PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgstbase-1.0.so)
    set_target_properties(gst_pbutils PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgstpbutils-1.0.so)
    set_target_properties(gst_video PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgstvideo-1.0.so)
    set_target_properties(gst_audio PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgstaudio-1.0.so)
    set_target_properties(gst_net PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgstnet-1.0.so)

    add_library(glib SHARED IMPORTED)
    add_library(gobject SHARED IMPORTED)
    add_library(gtk_30 SHARED IMPORTED)
    add_library(gdk_30 SHARED IMPORTED)
    add_library(gdk_pixbuf SHARED IMPORTED)
    add_library(cairo SHARED IMPORTED)
    add_library(atk SHARED IMPORTED)
    add_library(harfbuzz SHARED IMPORTED)
    add_library(pango SHARED IMPORTED)

    set_target_properties(glib PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libglib-2.0.so)
    set_target_properties(gobject PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgobject-2.0.so)
    set_target_properties(gtk_30 PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgtk-3.so)
    set_target_properties(gdk_30 PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgdk-3.so)
    set_target_properties(gdk_pixbuf PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libgdk_pixbuf-2.0.so)
    set_target_properties(cairo PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libcairo.so)
    set_target_properties(atk PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libatk-1.0.so)
    set_target_properties(harfbuzz PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libharfbuzz.so)
    set_target_properties(pango PROPERTIES IMPORTED_LOCATION ${gstreamer_dir}/libpango-1.0.so)

    # mac 平台
elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    set(gstreamer_dir /usr/local/Cellar/gstreamer/1.18.5)
    set(glib_dir /usr/local/Cellar/glib/2.70.4)
    include_directories(
            ${gstreamer_dir}/include/gstreamer-1.0
            ${glib_dir}/include/glib-2.0
            ${glib_dir}/include/gio-unix-2.0
    )

    # gstreamer 需要这种模式
    link_libraries(
            ${gstreamer_dir}/lib/libgstreamer-1.0.0.dylib
            ${gstreamer_dir}/lib/libgstnet-1.0.0.dylib
            ${gstreamer_dir}/lib/libgstcontroller-1.0.0.dylib
            ${gstreamer_dir}/lib/libgstcheck-1.0.0.dylib
            ${gstreamer_dir}/lib/libgstbase-1.0.0.dylib
            ${glib_dir}/lib/libglib-2.0.0.dylib
            ${glib_dir}/lib/libgobject-2.0.dylib
            ${glib_dir}/lib/libgio-2.0.dylib
            ${glib_dir}/lib/libgmodule-2.0.dylib
            ${glib_dir}/lib/libgthread-2.0.dylib
    )
endif ()

add_executable(
        gstreamerExample main.cpp
        src/common/gst-def.h
        src/common/Logger.cpp src/common/Logger.h
        src/common/Timestamp.cpp src/common/Timestamp.h
        src/stream/GstreamerPusherRtmp.cpp src/stream/GstreamerPusherRtmp.h
        src/stream/GstreamerPlayRtsp.cpp src/stream/GstreamerPlayRtsp.h
        src/basictutorials/basic-test.cpp src/basictutorials/basic-test.h
        src/basictutorials/basic-tutorial-3.cpp src/basictutorials/basic-tutorial-3.h
        src/basictutorials/basic-tutorial-4.h src/basictutorials/basic-tutorial-4.cpp
        src/basictutorials/basic-tutorial-5.h src/basictutorials/basic-tutorial-5.cpp
        src/basictutorials/basic-tutorial-6.h src/basictutorials/basic-tutorial-6.cpp
        src/basictutorials/basic-tutorial-7.h src/basictutorials/basic-tutorial-7.cpp
        src/basictutorials/basic-tutorial-8.h src/basictutorials/basic-tutorial-8.cpp
        src/basictutorials/basic-tutorial-9.h src/basictutorials/basic-tutorial-9.cpp
        src/basictutorials/basic-tutorial-12.h src/basictutorials/basic-tutorial-12.cpp
        src/basictutorials/basic-tutorial-13.h src/basictutorials/basic-tutorial-13.cpp src/basictutorials/basic-tutorial-2.h src/basictutorials/basic-tutorial-2.cpp src/basictutorials/basic-tutorial-1.h src/basictutorials/basic-tutorial-1.cpp)

message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME} ")
message("CMAKE_HOST_SYSTEM: ${CMAKE_HOST_SYSTEM} ")

message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} ")
message("CMAKE_SYSTEM: ${CMAKE_SYSTEM} ")

message("CMAKE_HOST_UNIX: ${CMAKE_HOST_UNIX} ")
message("CMAKE_HOST_WIN32: ${CMAKE_HOST_WIN32} ")

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(
            gstreamerExample
            gstreamer
            gst_pbutils
            gst_video
            gst_audio
            gst_base
            gst_net
            glib gobject
            gtk_30
            gdk_30
            gdk_pixbuf
            cairo
            atk
            harfbuzz
            pango
    )
elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    #    target_link_libraries(gstreamerExample)
endif ()