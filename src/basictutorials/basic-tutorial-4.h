//
// Created by wuwenbin on 2/17/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_TUTORIAL_4_H
#define GSTREAMEREXAMPLE_BASIC_TUTORIAL_4_H

#include <gst/gst.h>

/* Structure to contain all our information, so we can pass it around */
typedef struct custom_data_4_ {
    GstElement *playbin;  /* Our one and only element */
    gboolean playing;      /* Are we in the PLAYING state? */
    gboolean terminate;    /* Should we terminate execution? */
    gboolean seek_enabled; /* Is seeking enabled for this media? */
    gboolean seek_done;    /* Have we performed the seek already? */
    gint64 duration;       /* How long does this media last, in nanoseconds */
} custom_data_4;

int basic_tutorial_4_main(int argc, char *argv[]);

/* Forward definition of the message processing function */
static void basic_tutorial_4_handle_message(custom_data_4 *data, GstMessage *msg);

#endif //GSTREAMEREXAMPLE_BASIC_TUTORIAL_4_H
