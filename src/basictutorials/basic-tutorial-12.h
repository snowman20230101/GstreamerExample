//
// Created by wuwenbin on 2/20/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_TUTORIAL_12_H
#define GSTREAMEREXAMPLE_BASIC_TUTORIAL_12_H

#include <gst/gst.h>


typedef struct custom_data_12_ {
    gboolean is_live;
    GstElement *pipeline;
    GMainLoop *loop;
} custom_data_12;

int basic_tutorial_12_main(int argc, char *argv[]);

static void basic_tutorial_12_message_handle(GstBus *bus, GstMessage *msg, custom_data_12 *data);


#endif //GSTREAMEREXAMPLE_BASIC_TUTORIAL_12_H
