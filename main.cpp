#include <iostream>
#include <gst/gst.h>

#include "basic-test.h"
#include <basic-tutorial-3.h>
#include "basic-tutorial-4.h"
#include "basic-tutorial-5.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, Gstreamer !" << std::endl;
    const char *gst_version = gst_version_string();
    printf("gstreamer version is %s\n", gst_version);

//    create_element(argc, argv);

//    create_element_by_factory(argc, argv);

//    test_factory_plugin_category(argc, argv);

//    test_link_elements(argc, argv);

//    test_sometimes_pad(argc, argv);

//    test_hello_world(argc, argv);

//    basic_tutorial_3_main(argc, argv);

//    basic_tutorial_4_main(argc, argv);

//    basic_tutorial_5_main(argc, argv);

    return 0;
}
