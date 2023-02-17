//
// Created by wuwenbin on 2/15/23.
//

#include <cstdio>
#include "GstreamerPusherRtmp.h"

int GstreamerPusherRtmp::main_push(int argc, const std::string &filename) {
    frame_width = 1280;
    frame_height = 720;
    frame_rate = 25;
//    frame_bps = 1500000;
    printf("width:%d, height:%d, rate:%d, bps:%d.\n", frame_width, frame_height, frame_rate, 1);

    printf("============= v4l2 rtmp gst init start ============\n");
    gst_init(NULL, NULL);
    printf("=========== create v4l2 rtmp pipeline =============\n");

    // create pipeline
    GstData.pipeline = gst_pipeline_new("file_rtmp");

    // create elements by factory
    GstData.filesrc = gst_element_factory_make("filesrc", "filesrc");
    GstData.queue = gst_element_factory_make("queue", "queue");
    GstData.h264parse = gst_element_factory_make("h264parse", "h264parse");
    GstData.flvmux = gst_element_factory_make("flvmux", "flvmux");
    GstData.rtmpsink = gst_element_factory_make("rtmpsink", "rtmpsink");

    if (!GstData.pipeline || !GstData.filesrc || !GstData.queue ||
        !GstData.h264parse || !GstData.flvmux || !GstData.rtmpsink) {
        g_printerr("One element could not be created... Exit\n");
        return -1;
    }

    printf("============ link v4l2 rtmp pipeline ==============\n");
    GstCaps *caps_file_src;
    caps_file_src = gst_caps_new_simple("video/x-h264", "stream-format", G_TYPE_STRING, "byte-stream",
                                        "alignment", G_TYPE_STRING, "au",
                                        "width", G_TYPE_INT, frame_width,
                                        "height", G_TYPE_INT, frame_height,
                                        "framerate", GST_TYPE_FRACTION, frame_rate, 1, NULL);
    GstCaps *caps_flv_sink;
    caps_flv_sink = gst_caps_new_simple("video/x-h264", "stream-format", G_TYPE_STRING, "avc",
                                        "alignment", G_TYPE_STRING, "au",
                                        "width", G_TYPE_INT, frame_width,
                                        "height", G_TYPE_INT, frame_height,
                                        "framerate", GST_TYPE_FRACTION, frame_rate, 1, NULL);
    //
    g_object_set(G_OBJECT(GstData.filesrc), "location", filename.c_str(), NULL);
    g_object_set(G_OBJECT(GstData.rtmpsink), "location", "rtmp://101.43.184.19:1935/live/room_1", NULL);

    // 总线
    GstData.bus = gst_pipeline_get_bus(GST_PIPELINE(GstData.pipeline));
    // 设置消息处理器到管道的总线上, 来创建一个消息处理器来侦听管道
    GstData.bus_watch_id = gst_bus_add_watch(GstData.bus, (GstBusFunc) bus_msg_call, (gpointer) &GstData);
    gst_object_unref(GstData.bus);

    // bin add
    gst_bin_add_many(GST_BIN(GstData.pipeline), GstData.filesrc, GstData.queue,
                     GstData.h264parse, GstData.flvmux, GstData.rtmpsink, NULL);

    // link filter
    if (gst_element_link_filtered(GstData.filesrc, GstData.queue, caps_file_src) != TRUE) {
        g_printerr("GstData.filesrc could not link GstData.queue\n");
        gst_object_unref(GstData.pipeline);
        return -1;
    }
    gst_caps_unref(caps_file_src);

    // link element
    if (gst_element_link(GstData.queue, GstData.h264parse) != TRUE) {
        g_printerr("GstData.queue could not link GstData.h264parse\n");
        gst_object_unref(GstData.pipeline);
        return -1;
    }

    if (gst_element_link_filtered(GstData.h264parse, GstData.flvmux, caps_flv_sink) != TRUE) {
        g_printerr("GstData.h264parse could not link GstData.flvmux\n");
        gst_object_unref(GstData.pipeline);
        return -1;
    }
    gst_caps_unref(caps_flv_sink);

    if (gst_element_link(GstData.flvmux, GstData.rtmpsink) != TRUE) {
        g_printerr("GstData.h264parse could not link GstData.flvmux\n");
        gst_object_unref(GstData.pipeline);
        return -1;
    }

    printf("========= link v4l2 rtmp pipeline running ==========\n");
    gst_element_set_state(GstData.pipeline, GST_STATE_PLAYING);

    GstData.loop = g_main_loop_new(nullptr, FALSE);    // Create gstreamer loop
    g_main_loop_run(GstData.loop); // Loop will run until receiving EOS (end-of-stream), will block here

    printf("g_main_loop_run returned, stopping rtmp!\n");

    gst_element_set_state(GstData.pipeline, GST_STATE_NULL); // Stop pipeline to be released
    printf("Deleting pipeline\n");

    gst_object_unref(GstData.pipeline); // This will also delete all pipeline elements
    g_source_remove(GstData.bus_watch_id);
    g_main_loop_unref(GstData.loop);

    return 0;
}

/**
 * 使用侦听器对总线进行侦听
 *
 * @param bus
 * @param msg
 * @param pGstData
 * @return
 */
gboolean GstreamerPusherRtmp::bus_msg_call(GstBus *bus, GstMessage *msg, GstDataStruct *pGstData) {
    gchar *debug;
    GError *error;
    GMainLoop *loop = pGstData->loop;

    GST_DEBUG("got message %s", gst_message_type_get_name(GST_MESSAGE_TYPE(msg)));
    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_EOS:
            printf("End of stream\n");
            g_main_loop_quit(loop);
            break;
        case GST_MESSAGE_ERROR:
            gst_message_parse_error(msg, &error, &debug);
            g_free(debug);
            g_printerr("Error: %s\n", error->message);
            g_error_free(error);
            g_main_loop_quit(loop);
            break;
        default:
            break;
    }

    return TRUE;
}