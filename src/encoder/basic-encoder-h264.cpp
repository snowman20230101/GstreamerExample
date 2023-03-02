//
// Created by wuwenbin on 2/28/23.
//

#include "basic-encoder-h264.h"
#include <cstdlib>

int encoder_h265_test(const char *srcFile, const char *desFile, int csp, int frame_num) {
    int frames = frame_num;
    int ret;
    FILE *fb_src = fopen(srcFile, "rb");
    FILE *fb_des = fopen(desFile, "wb");

    // 申请参数
    x265_param *param = x265_param_alloc();
    x265_param_default(param);

    param->bRepeatHeaders = 1; // write sps,pps before keyframe.
    param->bAnnexB = 1; //
    param->sourceWidth = width;
    param->sourceHeight = height;
    param->internalCsp = csp;
    param->fpsNum = 25;
    param->fpsDenom = 1;
//    param->levelIdc = 32;
//    param->keyframeMax = 2 * 25;

//    param->rc.bitrate = 1024 * 512; // 设置编码码率512kbps
    ret = x265_param_apply_profile(param, x265_profile_names[9]);
    if (ret == 0) {
        printf("x265_param_apply_profile()  success ... \n");
    }

    // 打开编码器
    x265_encoder *encoder = x265_encoder_open(param);
    if (!encoder) {
        printf("x265 open encoder failed. err. \n");
        return -1;
    }

    // 申请图片内存
    x265_picture *picture = x265_picture_alloc();
    x265_picture_init(param, picture);

    switch (csp) {
        case X265_CSP_I420: {
            // YUV 420，由 4 个 Y 分量共用一套 UV 分量 4:1:1
            buff = static_cast<uint8_t *>(malloc(y_size * 3 / 2));
            picture->planes[0] = buff; //  这里是指针指向第一个buff指针位置，如同这个buff=0
            picture->planes[1] = buff + y_size; // 指针偏移 y_size
            picture->planes[2] = buff + y_size * 5 / 4; // + y_size + y_size / 4;
            picture->stride[0] = width;
            picture->stride[1] = width / 2;
            picture->stride[2] = width / 2;
            break;
        }
        case X265_CSP_I422: {
            // YUV 422，由 2 个 Y 分量共用一套 UV 分量
            buff = static_cast<uint8_t *>(malloc(y_size * 2));
            picture->planes[0] = buff;
            picture->planes[1] = buff + y_size;
            picture->planes[2] = buff + y_size * 3 / 2; // + y_size + y_size / 2;
            picture->stride[0] = width;
            picture->stride[1] = width / 2;
            picture->stride[2] = width / 2;
            break;
        }
        case X265_CSP_I444: {
            // YUV 444，不共用，一个 Y 分量使用一套 UV 分量
            buff = static_cast<uint8_t *>(malloc(y_size * 3));
            picture->planes[0] = buff;
            picture->planes[1] = buff + y_size;
            picture->planes[2] = buff + y_size * 2;
            picture->stride[0] = width;
            picture->stride[1] = width;
            picture->stride[2] = width;
            break;
        }
        default:
            printf("Colorspace Not Support.\n");
            break;
    }

    // detect frame number
    if (frames == 0) {
        fseek(fb_src, 0, SEEK_END);
        switch (csp) {
            case X265_CSP_I420:
                frames = (int) (ftell(fb_src) / (y_size * 3 / 2));
                break;
            case X265_CSP_I422:
                frames = (int) ftell(fb_src) / (y_size * 2);
                break;
            case X265_CSP_I444:
                frames = (int) ftell(fb_src) / (y_size * 3);
                break;
            default:
                printf("Colorspace Not Support.\n");
                return -1;
        }

        printf("total frames %d \n", frames);
        fseek(fb_src, 0, SEEK_SET);
    }

    x265_nal *pp_nal;
    uint32_t pi_nal;
    for (int i = 0; i < frames; ++i) {
        switch (csp) {
            case X265_CSP_I420: {
                fread(picture->planes[0], 1, y_size, fb_src);
                fread(picture->planes[1], 1, y_size / 4, fb_src);
                fread(picture->planes[2], 1, y_size / 4, fb_src);
                break;
            }
            case X265_CSP_I422: {
                fread(picture->planes[0], 1, y_size, fb_src);
                fread(picture->planes[1], 1, y_size / 2, fb_src);
                fread(picture->planes[2], 1, y_size / 2, fb_src);
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
        printf("Succeed encode %d frames, ret:%d, pi_nal:%d \n", i, ret, pi_nal);
        for (int j = 0; j < pi_nal; ++j) {
            fwrite(pp_nal[j].payload, 1, pp_nal[j].sizeBytes, fb_des);
        }
    }

    // flush encoder
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

int encoder_h264_test(const char *srcFile, const char *desFile, int csp, int frame_num) {
    int frames = frame_num;
    int ret;
    FILE *fb_src = fopen(srcFile, "rb");
    FILE *fb_des = fopen(desFile, "wb");

    x264_param_t param;
    x264_param_default(&param);

    param.i_csp = csp;
    param.i_bframe = 0; // 不要B帧
    param.i_width = width;
    param.i_height = height;
    param.i_level_idc = 32; // base_line 3.2 编码规格

    // 帧率
    param.i_fps_num = 25;
    param.i_fps_den = 1;
    param.i_timebase_num = param.i_fps_num;
    param.i_timebase_den = param.i_fps_den;
    param.i_threads = 1;
    param.i_keyint_max = 50;
    param.i_keyint_min = 24;
    param.i_bitdepth = 8;

    param.rc.i_rc_method = X264_RC_ABR;  // 参数i_rc_method表示码率控制，CQP(恒定质量)，CRF(恒定码率)，ABR(平均码率)
    param.rc.i_bitrate = 800000 / 1000;
    param.rc.i_vbv_max_bitrate = 800000 / 1000 * 1.2; // 瞬时最大码率
    param.rc.i_vbv_buffer_size = 800000 / 1000; // 设置了i_vbv_max_bitrate必须设置此参数，码率控制区大小,单位kbps

    param.b_vfr_input = 0; // 用fps而不是时间戳来计算帧间距离
    param.b_repeat_headers = 1; // 是否复制sps和pps放在每个关键帧的前面 该参数设置是让每个关键帧(I帧)都附带sps/pps
    param.b_annexb = 1;

    x264_param_apply_profile(&param, x264_profile_names[0]);
    x264_t *encoder = x264_encoder_open(&param);
    if (!encoder) {
        printf("Failed to open encoder. \n");
    }
    auto *picture = new x264_picture_t;
//    x264_picture_init(&picture);
    x264_picture_alloc(picture, param.i_csp, param.i_width, param.i_height);

    switch (csp) {
        case X264_CSP_I420: {
            // YUV 420，由 4 个 Y 分量共用一套 UV 分量 4:1:1
            buff = static_cast<uint8_t *>(malloc(y_size * 3 / 2));
            picture->img.plane[0] = buff;
            picture->img.plane[1] = buff + y_size;
            picture->img.plane[2] = buff + y_size + y_size / 4;
            picture->img.i_stride[0] = width;
            picture->img.i_stride[1] = width / 2;
            picture->img.i_stride[2] = width / 2;
            break;
        }
        case X264_CSP_I422: {
            // YUV 422，由 2 个 Y 分量共用一套 UV 分量
            buff = static_cast<uint8_t *>(malloc(y_size * 2));
            picture->img.plane[0] = buff;
            picture->img.plane[1] = buff + y_size;
            picture->img.plane[2] = buff + y_size + y_size / 2;
            picture->img.i_stride[0] = width;
            picture->img.i_stride[1] = width;
            picture->img.i_stride[2] = width;
            break;
        }
        case X264_CSP_I444: {
            // YUV 444，不共用，一个 Y 分量使用一套 UV 分量
            buff = static_cast<uint8_t *>(malloc(y_size * 3));
            picture->img.plane[0] = buff;
            picture->img.plane[1] = buff + y_size;
            picture->img.plane[2] = buff + y_size + y_size;
            picture->img.i_stride[0] = width;
            picture->img.i_stride[1] = width;
            picture->img.i_stride[2] = width;
            break;
        }
        default:
            printf("Colorspace Not Support.\n");
            break;
    }

    // detect frame number
    if (frames == 0) {
        fseek(fb_src, 0, SEEK_END);
        switch (csp) {
            case X264_CSP_I420:
                frames = (int) (ftell(fb_src) / (y_size * 3 / 2));
                break;
            case X264_CSP_I422:
                frames = (int) ftell(fb_src) / (y_size * 2);
                break;
            case X264_CSP_I444:
                frames = (int) ftell(fb_src) / (y_size * 3);
                break;
            default:
                printf("Colorspace Not Support.\n");
                return -1;
        }
        printf("total frames %d \n", frames);
        fseek(fb_src, 0, SEEK_SET);
    }

    x264_nal_t *pp_nal;
    int pi_nal;
    int i_frame_size = 0;
    x264_picture_t pic_out;
    for (int i = 0; i < frames; ++i) {
        switch (csp) {
            case X264_CSP_I420: {
                fread(picture->img.plane[0], 1, y_size, fb_src);
                fread(picture->img.plane[1], 1, y_size / 4, fb_src);
                fread(picture->img.plane[2], 1, y_size / 4, fb_src);
                break;
            }
            case X264_CSP_I422: {
                fread(picture->img.plane[0], 1, y_size, fb_src);
                fread(picture->img.plane[1], 1, y_size / 2, fb_src);
                fread(picture->img.plane[2], 1, y_size / 2, fb_src);
                break;
            }
            case X264_CSP_I444: {
                fread(picture->img.plane[0], 1, y_size, fb_src);
                fread(picture->img.plane[1], 1, y_size, fb_src);
                fread(picture->img.plane[2], 1, y_size, fb_src);
                break;
            }
            default:
                break;
        }

        picture->i_pts = i;
        i_frame_size = x264_encoder_encode(encoder, &pp_nal, &pi_nal, picture, &pic_out);
        if (i_frame_size < 0) {
            printf("Failed to encoder. \n");
            goto end;
        }
        printf("Succeed encode %5d frames, i_frame_size:%d, pi_nal:%d \n", i, i_frame_size, pi_nal);
        for (int j = 0; j < pi_nal; ++j) {
            fwrite(pp_nal[j].p_payload, 1, pp_nal[j].i_payload, fb_des);
        }
    }

    // flush encoder
    while (true) {
        i_frame_size = x264_encoder_encode(encoder, &pp_nal, &pi_nal, nullptr, &pic_out);
        if (i_frame_size == 0) {
            break;
        }

        printf("Flush 1 frame .\n");
        for (int j = 0; j < pi_nal; ++j) {
            fwrite(pp_nal[j].p_payload, 1, pp_nal[j].i_payload, fb_des);
        }
    }

    end:
    // 释放资源
    x264_encoder_close(encoder);
    x264_picture_clean(picture);
    return 0;
}