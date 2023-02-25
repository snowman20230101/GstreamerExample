//
// Created by windy on 2023/2/25.
//

#ifndef GSTREAMEREXAMPLE_GSTREAMER_SAVE_MP4_FILE_DEMP_H
#define GSTREAMEREXAMPLE_GSTREAMER_SAVE_MP4_FILE_DEMP_H

#include <gst/gst.h>

#include "gstreamer-save-file-demo.h"

int save_file_mp4_main(int argc, char *argv[]);

static void save_mp4_source_pad_added_handler(GstElement *src, GstPad *new_pad, custom_data_save_file *data);

#endif //GSTREAMEREXAMPLE_GSTREAMER_SAVE_MP4_FILE_DEMP_H
