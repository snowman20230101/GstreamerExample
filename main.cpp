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

#include "playback-tutorial-1.h"
#include "playback-tutorial-2.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, Gstreamer !" << std::endl;
    const char *gst_version = gst_version_string();
    printf("gstreamer version is %s\n", gst_version);

    const char *cairo_version = cairo_version_string();
    printf("cairo version is %s\n", cairo_version);
//    create_element(argc, argv);

//    create_element_by_factory(argc, argv);

//    test_factory_plugin_category(argc, argv);

//    test_link_elements(argc, argv);

//    test_sometimes_pad(argc, argv);

    test_hello_world(argc, argv);

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

//    play_back_tutorial_1_main(argc, argv);

//    play_back_tutorial_2_main(argc, argv);

    return 0;
}
