//
// Created by wuwenbin on 2/17/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_TUTORIAL_9_H
#define GSTREAMEREXAMPLE_BASIC_TUTORIAL_9_H

#include <cstring>
#include <gst/gst.h>
#include <gst/pbutils/pbutils.h>

/* Structure to contain all our information, so we can pass it around */
typedef struct custom_data_9_ {
    GstDiscoverer *discoverer;
    GMainLoop *loop;
} custom_data_9;

int basic_tutorial_9_main(int argc, char **argv);

/* Print a tag in a human-readable format (name: value) */
static void print_tag_foreach(const GstTagList *tags, const gchar *tag, gpointer user_data);

/* Print information regarding a stream */
static void print_stream_info(GstDiscovererStreamInfo *info, gint depth);

/* Print information regarding a stream and its substreams, if any */
static void print_topology(GstDiscovererStreamInfo *info, gint depth);

static void on_discovered_cb(GstDiscoverer *discoverer, GstDiscovererInfo *info, GError *err, custom_data_9 *data);

static void on_finished_cb(GstDiscoverer *discoverer, custom_data_9 *data);

#endif //GSTREAMEREXAMPLE_BASIC_TUTORIAL_9_H
