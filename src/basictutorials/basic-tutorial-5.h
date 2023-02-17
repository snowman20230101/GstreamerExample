//
// Created by wuwenbin on 2/17/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_TUTORIAL_5_H
#define GSTREAMEREXAMPLE_BASIC_TUTORIAL_5_H

#include <cstring>

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>

#include <gdk/gdk.h>

#if defined (GDK_WINDOWING_X11)

#include <gdk/gdkx.h>

#elif defined (GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#elif defined (GDK_WINDOWING_QUARTZ)
#include <gdk/gdkquartz.h>
#endif

/* Structure to contain all our information, so we can pass it around */
typedef struct custom_data_5_ {
    GstElement *playbin;           /* Our one and only pipeline */

    GtkWidget *slider;              /* Slider widget to keep track of current position */
    GtkWidget *streams_list;        /* Text widget to display info about the streams */
    gulong slider_update_signal_id; /* Signal ID for the slider update signal */

    GstState state;                 /* Current state of the pipeline */
    gint64 duration;                /* Duration of the clip, in nanoseconds */
} custom_data_5;


int basic_tutorial_5_main(int argc, char *argv[]);

static void create_ui(custom_data_5 *data);

static void play_cb(GtkButton *button, custom_data_5 *data);

static void pause_cb(GtkButton *button, custom_data_5 *data);

static void stop_cb(GtkButton *button, custom_data_5 *data);

static void delete_event_cb(GtkWidget *widget, GdkEvent *event, custom_data_5 *data);

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, custom_data_5 *data);

static void slider_cb(GtkRange *range, custom_data_5 *data);

static gboolean refresh_ui(custom_data_5 *data);



static void realize_cb(GtkWidget *widget, custom_data_5 *data);

static void analyze_streams(custom_data_5 *data);

/**
 * element 回调 playBin
 *
 * @param playbin
 * @param stream
 * @param data
 */
static void tags_cb(GstElement *playbin, gint stream, custom_data_5 *data);

/**
 * bus 回调
 *
 * @param bus
 * @param msg
 * @param data
 */
static void error_cb(GstBus *bus, GstMessage *msg, custom_data_5 *data);

static void eos_cb(GstBus *bus, GstMessage *msg, custom_data_5 *data);

static void state_changed_cb(GstBus *bus, GstMessage *msg, custom_data_5 *data);

static void application_cb(GstBus *bus, GstMessage *msg, custom_data_5 *data);

#endif //GSTREAMEREXAMPLE_BASIC_TUTORIAL_5_H
