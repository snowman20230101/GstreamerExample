//
// Created by wuwenbin on 2/16/23.
//

#ifndef GSTREAMEREXAMPLE_GSTREAMERPLAYRTSP_H
#define GSTREAMEREXAMPLE_GSTREAMERPLAYRTSP_H

#include <gst/gst.h>

#define RTSP_URL "rtsp://101.43.184.19:554/test.264"

class GstreamerPlayRtsp {
public:
    GstreamerPlayRtsp() {
        gst_init(nullptr, nullptr);
    }

    int rtsp_save_h264(const char *rtsp_url);

    int play(const char *url);

private:
    static void cb_new_rtsp_src_pad(GstElement *element, GstPad *pad, gpointer user_data);

    static void on_pad_added(GstElement *element, GstPad *pad, gpointer data);

private:
    GstElement *pipeline, *source, *rtpdepay, *parse, *decodebin, *sink;
    GstElement *filter;
    GstElement *fileSink;
};

static void read_video_props(GstCaps *caps);

#endif //GSTREAMEREXAMPLE_GSTREAMERPLAYRTSP_H
