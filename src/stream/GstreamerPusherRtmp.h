//
// Created by wuwenbin on 2/15/23.
//

#ifndef GSTREAMEREXAMPLE_GSTREAMERPUSHERRTMP_H
#define GSTREAMEREXAMPLE_GSTREAMERPUSHERRTMP_H

#include <gst/gst.h>
#include <string>

typedef struct {
    GstElement *pipeline;
    GstElement *filesrc;
    GstElement *queue;
    GstElement *h264parse;
    GstElement *flvmux;
    GstElement *rtmpsink;
    GstBus *bus;
    guint bus_watch_id;
    guint sourceId;        /* To control the GSource */
    GMainLoop *loop;  /* GLib's Main Loop */
} GstDataStruct;

class GstreamerPusherRtmp {
public:
    int main_push(int argc, const std::string& filename);
private:
    static gboolean bus_msg_call(GstBus *bus, GstMessage *msg, GstDataStruct *pGstData);
private:
    GstDataStruct GstData;
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int frame_rate;
//    unsigned int frame_bps;
};

#endif //GSTREAMEREXAMPLE_GSTREAMERPUSHERRTMP_H
