//
// Created by wuwenbin on 2/21/23.
//

#ifndef GSTREAMEREXAMPLE_PLAYBACK_TUTORIAL_2_H
#define GSTREAMEREXAMPLE_PLAYBACK_TUTORIAL_2_H

#include <gst/gst.h>

/* Structure to contain all our information, so we can pass it around */
typedef struct custom_data_play_back_2_ {
    GstElement *playbin;  /* Our one and only element */

    gint n_video;          /* Number of embedded video streams */
    gint n_audio;          /* Number of embedded audio streams */
    gint n_text;           /* Number of embedded subtitle streams */

    gint current_video;    /* Currently playing video stream */
    gint current_audio;    /* Currently playing audio stream */
    gint current_text;     /* Currently playing subtitle stream */

    GMainLoop *main_loop;  /* GLib's Main Loop */
} custom_data_play_back_2;


int play_back_tutorial_2_main(int argc, char *argv[]);

/* Forward definition for the message and keyboard processing functions */
static gboolean play_back_2_handle_message(GstBus *bus, GstMessage *msg, custom_data_play_back_2 *data);

static gboolean play_back_2_handle_keyboard(GIOChannel *source, GIOCondition cond, custom_data_play_back_2 *data);

#endif //GSTREAMEREXAMPLE_PLAYBACK_TUTORIAL_2_H
