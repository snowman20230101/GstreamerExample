//
// Created by wuwenbin on 2/17/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_TUTORIAL_8_H
#define GSTREAMEREXAMPLE_BASIC_TUTORIAL_8_H

#include <gst/gst.h>
#include <gst/audio/audio.h>

#define CHUNK_SIZE 1024   /* Amount of bytes we are sending in each buffer */
#define SAMPLE_RATE 44100 /* Samples per second we are sending */

/* Structure to contain all our information, so we can pass it to callbacks */
typedef struct custom_data_8_ {
    GstElement *pipeline, *app_source, *tee, *audio_queue, *audio_convert1, *audio_resample, *audio_sink;
    GstElement *video_queue, *audio_convert2, *visual, *video_convert, *video_sink;
    GstElement *app_queue, *app_sink;

    guint64 num_samples;   /* Number of samples generated so far (for timestamp generation) */
    gfloat a, b, c, d;     /* For waveform generation */

    guint sourceid;        /* To control the GSource */

    GMainLoop *main_loop;  /* GLib's Main Loop */
} custom_data_8;

int basic_tutorial_8_main(int argc, char *argv[]);

static gboolean push_data(custom_data_8 *data);

static void start_feed(GstElement *source, guint size, custom_data_8 *data);

#endif //GSTREAMEREXAMPLE_BASIC_TUTORIAL_8_H
