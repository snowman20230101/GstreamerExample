//
// Created by wuwenbin on 2/20/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_TUTORIAL_1_H
#define GSTREAMEREXAMPLE_BASIC_TUTORIAL_1_H

#include <gst/gst.h>

#include "gst-def.h"

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

int basic_tutorial_1_main(int argc, char *argv[]);

#ifdef __cplusplus
};
#endif

#endif //GSTREAMEREXAMPLE_BASIC_TUTORIAL_1_H
