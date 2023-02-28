//
// Created by wuwenbin on 2/28/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_ENCODER_H264_H
#define GSTREAMEREXAMPLE_BASIC_ENCODER_H264_H

#include <cstdint>
#include <x264.h>
#include <x265.h>

/**
 *
 *
 * @param srcFile
 * @param desFile
 * @param frame_num
 * @return
 */
int encoder_h265_test(const char *srcFile, const char *desFile, int frame_num);

/**
 *
 *
 * @param srcFile
 * @param desFile
 * @param frame_num
 * @return
 */
int encoder_h264_test(const char *srcFile, const char *desFile, int frame_num);

#endif //GSTREAMEREXAMPLE_BASIC_ENCODER_H264_H
