//
// Created by wuwenbin on 2/20/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_TUTORIAL_13_H
#define GSTREAMEREXAMPLE_BASIC_TUTORIAL_13_H

#include <string>
#include <gst/gst.h>

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

typedef struct custom_data_13_ {
    GstElement *pipeline;
    GstElement *video_sink;
    GMainLoop *loop;

    gboolean playing;             /* Playing or Paused */
    gdouble rate;                 /* Current playback rate (can be negative) */
} custom_data_13;

int basic_tutorial_13_main(int argc, char *argv[]);

#endif //GSTREAMEREXAMPLE_BASIC_TUTORIAL_13_H
