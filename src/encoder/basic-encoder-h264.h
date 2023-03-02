//
// Created by wuwenbin on 2/28/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_ENCODER_H264_H
#define GSTREAMEREXAMPLE_BASIC_ENCODER_H264_H

#include <cstdint>
#include <x264.h>
#include <x265.h>
#include <vpx/vpx_codec.h>

static int width = 1280, height = 720;
static uint8_t *buff;
static int y_size = width * height;

/**
 *
 *
 * @param srcFile
 * @param desFile
 * @param frame_num
 * @return
 */
int encoder_h265_test(const char *srcFile, const char *desFile, int csp, int frame_num);

/**
 *
 *
 * @param srcFile
 * @param desFile
 * @param frame_num
 * @return
 */
int encoder_h264_test(const char *srcFile, const char *desFile, int csp, int frame_num);

//const char *get_vpx_version() {
//    return vpx_codec_version_str();
//}

#endif //GSTREAMEREXAMPLE_BASIC_ENCODER_H264_H
