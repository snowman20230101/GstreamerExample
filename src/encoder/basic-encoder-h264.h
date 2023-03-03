//
// Created by wuwenbin on 2/28/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_ENCODER_H264_H
#define GSTREAMEREXAMPLE_BASIC_ENCODER_H264_H

#include <cstdint>
#include <x264.h>
#include <x265.h>
#include <vpx/vpx_codec.h>
#include <vpx/vp8cx.h>

//#define fourcc    0x30385056
#define interface (&vpx_codec_vp8_cx_algo) // vpx_codec_iface_t

static int width = 1280, height = 720;
static uint8_t *buff;
static int y_size = width * height;

/**
 * test h265 encode
 *
 * @param srcFile
 * @param desFile
 * @param frame_num
 * @return
 */
int encoder_h265_test(const char *srcFile, const char *desFile, int csp, int frame_num);

/**
 * test h264 encode
 *
 * @param srcFile
 * @param desFile
 * @param frame_num
 * @return
 */
int encoder_h264_test(const char *srcFile, const char *desFile, int csp, int frame_num);

/**
 *
 * @param mem
 * @param val
 */
static void mem_put_le16(char *mem, unsigned int val);

/**
 *
 * @param mem
 * @param val
 */
static void mem_put_le32(char *mem, unsigned int val);

/**
 *
 * @param outfile
 * @param pkt
 */
static void write_ivf_frame_header(FILE *outfile, const vpx_codec_cx_pkt_t *pkt);

/**
 *
 * @param outfile
 * @param cfg
 * @param frame_cnt
 */
static void write_ivf_file_header(FILE *outfile, const vpx_codec_enc_cfg_t *cfg, int frame_cnt);

/**
 * test vpx(vp8) encode
 *
 * @param srcFile
 * @param desFile
 * @return
 */
int encoder_vpx_test(const char *srcFile, const char *desFile);

#endif //GSTREAMEREXAMPLE_BASIC_ENCODER_H264_H
