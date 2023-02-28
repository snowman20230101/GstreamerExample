//
// Created by wuwenbin on 2/17/23.
// TODO https://gstreamer.freedesktop.org/media
// https://github.com/goldze/MVVMHabit
//

#ifndef GSTREAMEREXAMPLE_GST_DEF_H
#define GSTREAMEREXAMPLE_GST_DEF_H

#include <string>
#include <cstring>

/// rtsp
#define TEST_URI_264 "rtsp://101.43.184.19:554/test.264"
#define TEST_URI_MKV "rtsp://101.43.184.19:554/hanggai_lunhui.mkv"
#define TEST_URI_AAC "rtsp://101.43.184.19:554/hanggai-lunhui.aac"
#define TEST_URI_WEBM "rtsp://101.43.184.19:554/sintel_trailer-480p.webm"
#define TEST_URI_OGV "rtsp://101.43.184.19:554/sintel_trailer-480p.ogv" // ffplay play failed.

#if defined(__APPLE__)
#define TEST_FILE_H264 "/home/wuwenbn/test.h264"
#define TEST_FILE_OGG "/home/wuwenbin/test.ogg"
#define TEST_FILE_WEBM "/home/wuwenbin/sintel_trailer-480p.webm"
#define TEST_FILE_MP4 "/Volumes/AospHD/TubeGet/video/hanggai_lunhui.mp4"

#define TEST_SAVE_FILE_MP4 "/home/wuwenbin/video/save_1.mp4"
#else

#define TEST_URI_264_LOCAL "rtsp://192.168.56.129:8554/hanggai.264"

/// local file
#define TEST_FILE_H264 "/home/wuwenbn/video/test.h264"
#define TEST_FILE_OGG "/home/wuwenbin/video/test.ogg"
#define TEST_FILE_WEBM "/home/wuwenbin/video/sintel_trailer-480p.webm"
#define TEST_FILE_MP4 "/home/wuwenbin/video/hanggai_lunhui.mp4"

///
#define TEST_SAVE_FILE_MP4 "/home/wuwenbin/video/save_1.mp4"
#endif

static std::string getMp4File() {
    std::string uri("file://");
    uri.append(TEST_FILE_MP4);
    return uri;
}

static std::string getWebmFile() {
    std::string uri("file://");
    uri.append(TEST_FILE_WEBM);
    return uri;
}

#endif //GSTREAMEREXAMPLE_GST_DEF_H
