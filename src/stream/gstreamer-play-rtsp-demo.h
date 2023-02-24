//
// Created by wuwenbin on 2/21/23.
//

#ifndef GSTREAMEREXAMPLE_GSTREAMER_PLAY_RTSP_DEMO_H
#define GSTREAMEREXAMPLE_GSTREAMER_PLAY_RTSP_DEMO_H

#include <gst-def.h>
#include <gst/gst.h>

/* Structure to contain all our information, so we can pass it to callbacks */
typedef struct custom_data_play_rtsp_ {
    GstElement *pipeline;
    GstElement *source;
    GstElement *depay;
    GstElement *parse;
    GstElement *avdec;
    GstElement *convert;
    GstElement *resample;
    GstElement *sink;
} custom_data_play_rtsp;

/**
 * Handler for the pad-added signal
 *
 * @param src
 * @param pad
 * @param data
 */
static void pad_added_handler(GstElement *src, GstPad *new_pad, custom_data_play_rtsp *data);

int play_rtsp_main(int argc, char *argv[]);


#endif //GSTREAMEREXAMPLE_GSTREAMER_PLAY_RTSP_DEMO_H
