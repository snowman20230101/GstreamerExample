//
// Created by wuwenbin on 2/17/23.
//

#ifndef GSTREAMEREXAMPLE_GST_DEF_H
#define GSTREAMEREXAMPLE_GST_DEF_H

#include <string>

/// this is a test media url
// TODO https://gstreamer.freedesktop.org/media

#define VIDEO_FILE_264 "/home/wuwenbin/hanggai.264"

#define AUDIO_FILE_OGG "/home/wuwenbin/test.ogg"

#define TEST_URI_FILE "/home/wuwenbin/sintel_trailer-480p.webm"

#define TEST_URI "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm"

#define TEST_FILE_URI "file:///home/wuwenbin/sintel_trailer-480p.webm"

#define TEST_FILE_HANGGAI "file:///home/wuwenbin/hanggai_lunhui.mp4"

static std::string getHangGai() {
    std::string uri("playbin uri=");
    uri.append(TEST_FILE_HANGGAI);
    return uri;
}


#endif //GSTREAMEREXAMPLE_GST_DEF_H
