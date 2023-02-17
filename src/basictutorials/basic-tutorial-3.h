//
// Created by wuwenbin on 2/17/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_TUTORIAL_3_H
#define GSTREAMEREXAMPLE_BASIC_TUTORIAL_3_H

#include <gst/gst.h>

/* Structure to contain all our information, so we can pass it to callbacks */
typedef struct {
    GstElement *pipeline;
    GstElement *source;
    GstElement *convert;
    GstElement *sink;
} CustomData;

/* basic tutorial 3 demo main */
int basic_tutorial_3_main(int argc, char *argv[]);

/* Handler for the pad-added signal */
static void basic_tutorial_3_pad_added_handler(GstElement *src, GstPad *new_pad, CustomData *data);


#endif //GSTREAMEREXAMPLE_BASIC_TUTORIAL_3_H
