#include <iostream>
#include <gst/gst.h>
#include <cairo.h>

#include "basic-test.h"
#include "basic-tutorial-1.h"
#include "basic-tutorial-2.h"
#include <basic-tutorial-3.h>
#include "basic-tutorial-4.h"
#include "basic-tutorial-5.h"
#include "basic-tutorial-6.h"
#include "basic-tutorial-7.h"
#include "basic-tutorial-8.h"
#include "basic-tutorial-9.h"
#include "basic-tutorial-12.h"
#include "basic-tutorial-13.h"

#include "gstreamer-play-rtsp-demo.h"
#include "gstreamer-save-file-demo.h"
#include "gstreamer-save-mp4-file-demp.h"

#include "playback-tutorial-1.h"
#include "playback-tutorial-2.h"
#include "basic-encoder-h264.h"

extern "C" {
#include <libavutil/avutil.h>
}

#include <opencv2/opencv.hpp>

int ext_encoder_h26x_test() {
    const char *srcFile = "/home/wuwenbin/video/test.yuv";

    const char *desFile_1 = "/home/wuwenbin/video/out/test_420.h265";
    const char *desFile_2 = "/home/wuwenbin/video/out/test_422.h265";
    const char *desFile_3 = "/home/wuwenbin/video/out/test_444.h265";
//    encoder_h265_test(srcFile, desFile_1, X265_CSP_I420, 0);
    encoder_h265_test(srcFile, desFile_2, X265_CSP_I422, 0);
//    encoder_h265_test(srcFile, desFile_3, X265_CSP_I444, 0);

    const char *desFile_4 = "/home/wuwenbin/video/out/abc_420.h264";
    const char *desFile_5 = "/home/wuwenbin/video/out/abc_422.h264";
    const char *desFile_6 = "/home/wuwenbin/video/out/abc_444.h264";
//    encoder_h264_test(srcFile, desFile_4, X264_CSP_I420, 0);
//    encoder_h264_test(srcFile, desFile_5, X264_CSP_I422, 0);
//    encoder_h264_test(srcFile, desFile_6, X264_CSP_I444, 0);
    return 0;
}

int main(int argc, char *argv[]) {
    std::cout << "Hello, Gstreamer !" << std::endl;
    const char *gst_version = gst_version_string();
    printf("gstreamer version is %s\n", gst_version);

    const char *cairo_version = cairo_version_string();
    printf("cairo version is %s\n", cairo_version);

    printf("x265 version is %s.\n", x265_version_str);
    printf("vpx version %s\n", vpx_codec_build_config());
    printf("ffmpeg version is %s \n\n", av_version_info());

//    create_element(argc, argv);

//    create_element_by_factory(argc, argv);

//    test_factory_plugin_category(argc, argv);

//    test_link_elements(argc, argv);

//    test_sometimes_pad(argc, argv);

//    test_hello_world(argc, argv);

//    basic_tutorial_1_main(argc, argv);

//    basic_tutorial_2_main(argc, argv);

//    basic_tutorial_3_main(argc, argv);

//    basic_tutorial_4_main(argc, argv);

//    basic_tutorial_5_main(argc, argv);

//    basic_tutorial_6_main(argc, argv);

//    basic_tutorial_7_main(argc, argv);

//    basic_tutorial_8_main(argc, argv);

//    basic_tutorial_9_main(argc, argv);

//    basic_tutorial_12_main(argc, argv);

//    basic_tutorial_13_main(argc, argv);

//    play_rtsp_main(argc, argv);

//    save_file_main(argc, argv);

//    save_file_mp4_main(argc, argv);

//    play_back_tutorial_1_main(argc, argv);

//    play_back_tutorial_2_main(argc, argv);

//    ext_encoder_h26x_test();

    return 0;
}
