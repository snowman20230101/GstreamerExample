//
// Created by wuwenbin on 2/28/23.
//

#include "basic-encoder-h264.h"

#include <cstdlib>

int encoder_h265_test(const char *srcFile, const char *desFile, int frame_num) {
    int width = 1280, height = 720;
    int csp = X265_CSP_I420;
    int ret;
    char *buff;
    int y_size = width * height;

    FILE *fb_src = fopen(srcFile, "rb");
    FILE *fb_des = fopen(desFile, "wb");

    x265_param *param = x265_param_alloc();
    x265_param_default_preset(param, "ultrafast", "fastdecode");

    param->bRepeatHeaders = 1; // write sps,pps before keyframe.
    param->bAnnexB = 1; //
    param->sourceWidth = width;
    param->sourceHeight = height;
    param->internalCsp = csp;
    param->fpsNum = 25;
    param->fpsDenom = 1;
    param->keyframeMax = 2 * 25;

    param->rc.bitrate = 1024 * 512; // 设置编码码率512kbps
    ret = x265_param_apply_profile(param, x265_profile_names[0]);
    if (ret == 0) {
        printf("x265_param_apply_profile()  ... \n");
    }
    x265_encoder *encoder = x265_encoder_open(param);
    if (!encoder) {
        printf("x265 open encoder failed. err. \n");
        return -1;
    }

    x265_picture *picture = x265_picture_alloc();
    x265_picture_init(param, picture);

    switch (csp) {
        case X265_CSP_I420: {
            buff = static_cast<char *>(malloc(y_size * 3 / 2));
            picture->planes[0] = buff;
            picture->planes[1] = buff + y_size;
            picture->planes[2] = buff + y_size * 5 / 4;
            picture->stride[0] = width;
            picture->stride[1] = width;
            picture->stride[2] = width;
            break;
        }
        case X265_CSP_I444: {
            buff = static_cast<char *>(malloc(y_size * 3));
            picture->planes[0] = buff;
            picture->planes[1] = buff + y_size;
            picture->planes[2] = buff + y_size * 2;
            picture->stride[0] = width;
            picture->stride[1] = width / 2;
            picture->stride[2] = width / 2;
            break;
        }
        default:
            printf("Colorspace Not Support.\n");
            break;
    }

    // detect frame number
    if (frame_num == 0) {
        fseek(fb_src, 0, SEEK_END);
        switch (csp) {
            case X265_CSP_I444:
                frame_num = (int) ftell(fb_src) / (y_size * 3);
                break;
            case X265_CSP_I420:
                frame_num = (int) ftell(fb_src) / (y_size * 3 / 2);
                break;
            default:
                printf("Colorspace Not Support.\n");
                return -1;
        }
        fseek(fb_src, 0, SEEK_SET);
    }

    x265_nal *pp_nal;
    uint32_t pi_nal;
    for (int i = 0; i < frame_num; ++i) {
        switch (csp) {
            case X265_CSP_I420: {
                fread(picture->planes[0], 1, y_size, fb_src);
                fread(picture->planes[1], 1, y_size / 4, fb_src);
                fread(picture->planes[2], 1, y_size / 4, fb_src);
                break;
            }
            case X265_CSP_I444: {
                fread(picture->planes[0], 1, y_size, fb_src);
                fread(picture->planes[1], 1, y_size, fb_src);
                fread(picture->planes[2], 1, y_size, fb_src);
                break;
            }
            default:
                break;
        }

        ret = x265_encoder_encode(encoder, &pp_nal, &pi_nal, picture, nullptr);
        if (ret == 0) {
            printf("x265_encoder_encode() ... \n");
        }
        printf("Succeed encode %5d frames\n", i);
        for (int j = 0; j < pi_nal; ++j) {
            fwrite(pp_nal[j].payload, 1, pp_nal[j].sizeBytes, fb_des);
        }
    }

    //Flush Decoder
    while (true) {
        ret = x265_encoder_encode(encoder, &pp_nal, &pi_nal, nullptr, nullptr);
        if (ret == 0) {
            break;
        }
        printf("Flush 1 frame.\n");

        for (int j = 0; j < pi_nal; j++) {
            fwrite(pp_nal[j].payload, 1, pp_nal[j].sizeBytes, fb_des);
        }
    }

    x265_encoder_close(encoder);
    x265_picture_free(picture);
    x265_param_free(param);
    free(buff);
    fclose(fb_src);
    fclose(fb_des);
    return 0;
}

int encoder_h264_test(const char *srcFile, const char *desFile, int frame_num) {
    x264_param_t param;
//    x264_param_default(&param);
    x264_param_default_preset(&param, "ultrafast", "zerolatency");

    return 0;
}