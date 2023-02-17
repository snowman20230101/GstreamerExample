//
// Created by wuwenbin on 2/17/23.
//

#ifndef GSTREAMEREXAMPLE_BASIC_TEST_H
#define GSTREAMEREXAMPLE_BASIC_TEST_H

#include <gst/gst.h>
#include "gst-def.h"

/**
 * 错误一
 *
 * (python:2946615): GStreamer-CRITICAL **: 19:24:31.287:
 * Trying to dispose element rtph264depay0, but it is in PLAYING instead of the NULL state.
 * You need to explicitly set elements to the NULL state before
 * dropping the final reference, to allow them to clean up.
 * This problem may also be caused by a refcounting bug in the
 * application or some element
 *
 * TODO 访问源码
 * https://gitlab.freedesktop.org/gstreamer/
 *
 *
 *
 */

/**
 * 创建 element
 *
 * @param argc
 * @param argv
 * @return
 */
int create_element(int argc, char *argv[]);

/**
 * 定义工厂创建element
 *
 * @param argc
 * @param argv
 * @return
 */
int create_element_by_factory(int argc, char *argv[]);

/**
 * 测试 gst 工厂 category
 *
 * @param argc
 * @param argv
 * @return
 */
int test_factory_plugin_category(int argc, char *argv[]);

/**
 * 测试 连接 element
 *
 * @param argc
 * @param argv
 * @return
 */
int test_link_elements(int argc, char *argv[]);

/**
 * test sometimes pad
 *
 * @param argc
 * @param argv
 * @return
 */
int test_sometimes_pad(int argc, char *argv[]);

static void test_sometimes_pad_added_handle(GstElement *element, GstPad *new_pad, gpointer data);

static void test_sometimes_pad_removed_handle(GstElement *element, GstPad *pad, gpointer data);

/**
 * Hello World 测试
 *
 * @param argc
 * @param argv
 * @return
 */
int test_hello_world(int argc, char *argv[]);

static void hello_world_pad_added_handle(GstElement *element, GstPad *new_pad, gpointer data);

static gboolean hello_world_bus_call_handle(GstBus *bus, GstMessage *msg, gpointer data);

#endif //GSTREAMEREXAMPLE_BASIC_TEST_H
