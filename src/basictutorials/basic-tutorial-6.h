//
// Created by wuwenbin on 2/17/23.
//



#ifndef GSTREAMEREXAMPLE_BASIC_TUTORIAL_6_H
#define GSTREAMEREXAMPLE_BASIC_TUTORIAL_6_H

#include <gst/gst.h>

int basic_tutorial_6_main(int argc, char *argv[]);

static gboolean print_field(GQuark field, const GValue *value, gpointer pfx);

static void print_caps(const GstCaps *caps, const gchar *pfx);

static void print_pad_templates_information(GstElementFactory *factory);

static void print_pad_capabilities(GstElement *element, gchar *pad_name);


#endif //GSTREAMEREXAMPLE_BASIC_TUTORIAL_6_H
