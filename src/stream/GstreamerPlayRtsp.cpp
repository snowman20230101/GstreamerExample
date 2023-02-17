//
// Created by wuwenbin on 2/16/23.
//

#include "GstreamerPlayRtsp.h"

// gst-launch-1.0 rtspsrc location=rtsp://192.168.1.165/554 rtph264depay ! h264parse ! video/x-h264, stream-format=byte-stream ! filesink localtion=fq_20230203.h264

int GstreamerPlayRtsp::rtsp_save_h264(const char *rtsp_url) {
    pipeline = gst_pipeline_new("rtsp-player");
    if (!pipeline) {
        g_print("pipeline == null \n");
        return -1;
    }

    source = gst_element_factory_make("rtspsrc", "source");
    if (!source) {
        g_print("source == null \n");
        return -1;
    }

    rtpdepay = gst_element_factory_make("rtph264depay", "depayl");
    if (!rtpdepay) {
        g_print("rtppay == null \n");
        return -1;
    }

    parse = gst_element_factory_make("h264parse", "parse");
    if (!parse) {
        g_print("parse == null \n");
        return -1;
    }

    fileSink = gst_element_factory_make("filesink", "file-sink");
    if (!fileSink) {
        g_print("fileSink == null \n");
        return -1;
    }

    g_object_set(G_OBJECT(source), "latency", 200, NULL);
    g_object_set(G_OBJECT(source), "location", rtsp_url, NULL);

    g_object_set(G_OBJECT(fileSink), "sync", FALSE, NULL); // TODO 作用
    g_object_set(G_OBJECT(fileSink), "location", "/home/wuwenbin/a.h264", NULL);

    gst_bin_add_many(GST_BIN(pipeline), source, rtpdepay, NULL);
    g_signal_connect(source, "pad-added", G_CALLBACK(cb_new_rtsp_src_pad), rtpdepay);
    GstCaps *caps = gst_caps_new_simple("video/x-h264", "stream-format", G_TYPE_STRING, "byte-stream", NULL);

    if (!gst_element_link_filtered(rtpdepay, parse, caps)) {
        g_printerr("rtpdepay could not link parse\n");
        gst_object_unref(pipeline);
        return -1;
    }

    gst_caps_unref(caps);

    if (gst_element_link(parse, fileSink) != TRUE) {
        g_printerr("parse could not link fileSink \n");
        gst_object_unref(pipeline);
        return -1;
    }

    //
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    GstBus *bus = gst_element_get_bus(pipeline);
    GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                                 (GstMessageType) (GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
    if (msg) {
        gst_message_unref(msg);
    }

    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    return 0;
}

int GstreamerPlayRtsp::play(const char *url) {
    pipeline = gst_pipeline_new("rtsp-player");
    if (!pipeline) {
        g_print("pipeline == null \n");
        return -1;
    }

    source = gst_element_factory_make("rtspsrc", "source");
    if (!source) {
        g_print("source == null \n");
        return -1;
    }

    rtpdepay = gst_element_factory_make("rtph264depay", "depayl");
    if (!rtpdepay) {
        g_print("rtppay == null \n");
        return -1;
    }

    parse = gst_element_factory_make("h264parse", "parse");
    if (!parse) {
        g_print("parse == null \n");
        return -1;
    }

    decodebin = gst_element_factory_make("openh264dec", "decode");
    if (!decodebin) {
        g_print("decodebin == null \n");
        return -1;
    }

    sink = gst_element_factory_make("xvimagesink", "sink");
    if (!sink) {
        g_print("sink == null \n");
        return -1;
    }

    g_object_set(G_OBJECT(source), "latency", 200, NULL);
    g_object_set(G_OBJECT(source), "location", url, NULL);

    g_object_set(G_OBJECT(sink), "sync", FALSE, NULL); // TODO 作用

    filter = gst_element_factory_make("capsfilter", "filter");
    if (!filter) {
        g_print("filter == null \n");
        return -1;
    }

    GstCaps *filterCaps = gst_caps_from_string("application/x-rtp"); // rtph264depay 這個 element 上有 Capabilities 就是 這個
    g_object_set(G_OBJECT(filter), "caps", filterCaps, NULL);
    g_object_unref(filterCaps);

    gst_bin_add_many(GST_BIN(pipeline), source, rtpdepay, NULL);
    g_signal_connect(source, "pad-added", G_CALLBACK(cb_new_rtsp_src_pad), rtpdepay);

    gst_bin_add_many(GST_BIN(pipeline), parse, NULL);
    if (!gst_element_link(rtpdepay, parse)) {
        g_print("\n NOPE \n");
        return -1;
    }

    gst_bin_add_many(GST_BIN(pipeline), decodebin, sink, NULL);
    if (!gst_element_link_many(parse, decodebin, sink, NULL)) {
        g_print("\nFailed to link parse to sink. \n");
        return -1;
    }

    g_signal_connect(rtpdepay, "pad-added", G_CALLBACK(on_pad_added), parse);

    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    GstBus *bus = gst_element_get_bus(pipeline);
    GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                                 (GstMessageType) (GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
    if (msg) {
        gst_message_unref(msg);
    }

    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    return 0;
}

void GstreamerPlayRtsp::cb_new_rtsp_src_pad(GstElement *element, GstPad *pad, gpointer user_data) {
    gchar *name;
    GstCaps *p_caps;
    gchar *description;
    GstElement *p_trph264depay;

    name = gst_pad_get_name(pad);
    g_print("A new pad %s was created. \n", name);

    p_caps = gst_pad_get_pad_template_caps(pad);
    description = gst_caps_to_string(p_caps);
    g_print("description:%s\n", description);
    g_free(description);

    p_trph264depay = GST_ELEMENT(user_data);
    if (!gst_element_link_pads(element, name, p_trph264depay, "sink")) {
        g_print("Failed to link elements 3\n");
    }

    g_free(name);
}

void GstreamerPlayRtsp::on_pad_added(GstElement *element, GstPad *pad, gpointer data) {
    GstPad *sinkpad;
    auto *decoder = (GstElement *) data;
    /* We can now link this pad with the rtsp-decoder sink pad */
    g_print("Dynamic pad created, linking source/demuxer\n");
    sinkpad = gst_element_get_static_pad(decoder, "sink");
    gst_pad_link(pad, sinkpad);
    gst_object_unref(sinkpad);
}

static void read_video_props(GstCaps *caps) {
    gint width = 0, height = 0;
    const GstStructure *str;
    g_return_if_fail(gst_caps_is_fixed(caps));
    str = gst_caps_get_structure(caps, 0);
    if (!gst_structure_get_int(str, "width", &width)
        || !gst_structure_get_int(str, "height", &height)) {
        g_print("No width/height available \n");
    }
    g_print("The Video size of this set of capabilities is %dx%d \n", width, height);
}
























