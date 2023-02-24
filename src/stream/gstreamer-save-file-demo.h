//
// Created by wuwenbin on 2/22/23.
//

#ifndef GSTREAMEREXAMPLE_GSTREAMER_SAVE_FILE_DEMO_H
#define GSTREAMEREXAMPLE_GSTREAMER_SAVE_FILE_DEMO_H

#include <gst/gst.h>

typedef struct custom_data_save_file_ {
    GstElement *pipeline;
    GstElement *source;
    GstElement *depay;
    GstElement *parse;
    GstElement *mp4mux;
    GstElement *sink;
} custom_data_save_file;

int save_file_main(int argc, char *argv[]);

static void save_h264_source_pad_added_handler(GstElement *src, GstPad *pad, custom_data_save_file *data);

/**
 * 获取到的数据是BGRx，比需要的BGR多一个通道，需要进行转换
 *
 * @param BGR
 * @param BGRx
 * @param width
 * @param height
 */
static void cvtColorBGRx2BGR(guint8 *BGR, const guint8 *BGRx, int width, int height) {
    for (int h = 0; h < height; h++) {
        for (int w = 0, w1 = 0; w < width * 3; w += 3, w1 += 4) {
            BGR[w] = BGRx[w1];
            BGR[w + 1] = BGRx[w1 + 1];
            BGR[w + 2] = BGRx[w1 + 2];
        }
        BGR += width * 3; // 指针位移
        BGRx += width * 4;
    }
}

#endif //GSTREAMEREXAMPLE_GSTREAMER_SAVE_FILE_DEMO_H
