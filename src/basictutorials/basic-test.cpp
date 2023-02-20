//
// Created by wuwenbin on 2/17/23.
//

#include "basic-test.h"

/**
 * 创建 element
 *
 * @param argc
 * @param argv
 * @return
 */
int create_element(int argc, char *argv[]) {
    GstElement *element;
    gst_init(&argc, &argv);

    element = gst_element_factory_make("fakesrc", "source");
    if (!element) {
        g_print("Failed to create element of type 'fakesrc' \n");
        return -1;
    }
    gchar *name;
    g_object_get(GST_OBJECT(element), "name", &name, NULL);
    g_print("create element success! element name is %s\n", name);
    g_free(name);

    gst_object_unref(GST_OBJECT(element));
    return 0;
}

/**
 * 定义工厂创建element
 *
 * @param argc
 * @param argv
 * @return
 */
int create_element_by_factory(int argc, char *argv[]) {
    GstElementFactory *factory;
    GstElement *element;
    gst_init(&argc, &argv);
    factory = gst_element_factory_find("fakesrc");
    if (!factory) {
        g_print("Failed to find factory of type 'fakesrc'\n");
        return -1;
    }

    element = gst_element_factory_create(factory, "source");
    if (!element) {
        g_print("Failed to create element, even though its factory exits!\n");
    }

    g_print("create element success by factory.!\n");

    gst_object_unref(GST_OBJECT(element));
    return 0;
}

/**
 * 测试 gst 工厂 category
 *
 * @param argc
 * @param argv
 * @return
 */
int test_factory_plugin_category(int argc, char *argv[]) {
    GstElementFactory *factory;
    gst_init(&argc, &argv);
    factory = gst_element_factory_find("audiotestsrc");
    if (!factory) {
        g_print("You don't have the 'audiotestsrc' element installed!\n");
        return -1;
    }

    /* display information */
    g_print("The '%s' element is a member of the category %s.\n"
            "Description: %s\n",
            gst_plugin_feature_get_name(GST_PLUGIN_FEATURE(factory)),
            gst_element_factory_get_klass(factory),
            gst_element_factory_get_description(factory));

    return 0;
}

/**
 * 测试 连接 element
 *
 * @param argc
 * @param argv
 * @return
 */
int test_link_elements(int argc, char *argv[]) {
    GstElement *pipeline;
    GstElement *source, *filter, *sink;
    gst_init(&argc, &argv);

    pipeline = gst_pipeline_new("test-link-pipeline");
    if (!pipeline) {
        g_print("pipeline == null. \n");
    }

    source = gst_element_factory_make("fakesrc", "source");
    if (!source) {
        g_print("source == null \n");
    }

    filter = gst_element_factory_make("identity", "filter");
    if (!filter) {
        g_print("filter == null \n");
    }

    sink = gst_element_factory_make("fakesink", "sink");
    if (!sink) {
        g_print("sink == null \n");
    }
    // must add elements to pipeline before linking them.
    gst_bin_add_many(GST_BIN(pipeline), source, filter, sink, NULL);

    // link
    if (!gst_element_link_many(source, filter, sink, NULL)) {
        g_warning("Failed to link elements!");
    }

    // 一定要回收
    gst_object_unref(pipeline);

    g_print("success link elements !\n");
    return 0;
}

/**
 * test sometimes pad
 *
 * @param argc
 * @param argv
 * @return
 */
int test_sometimes_pad(int argc, char *argv[]) {
    GstElement *pipeline, *source, *demux;
    GMainLoop *loop;

    gst_init(&argc, &argv);
    pipeline = gst_pipeline_new("test-sometimes-pipeline");
    if (!pipeline) {
        g_print("pipeline == null \n");
    }

    source = gst_element_factory_make("filesrc", "source");
    if (!source) {
        g_print("source == null \n");
    }
    const char *fileName = AUDIO_FILE_OGG;
    g_object_set(source, "location", fileName, NULL);

    demux = gst_element_factory_make("oggdemux", "demuxer");
    if (!demux) {
        g_print("demux == null \n");
    }

    // put together a pipeline.
    gst_bin_add_many(GST_BIN(pipeline), source, demux, NULL);
    gst_element_link_pads(source, "src", demux, "sink");

    // listen for newly created pads.
    g_signal_connect(demux, "pad-added", G_CALLBACK(test_sometimes_pad_added_handle), NULL);

    g_signal_connect(demux, "pad-removed", G_CALLBACK(test_sometimes_pad_removed_handle), NULL);

    // start the pipeline
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
    loop = g_main_loop_new(nullptr, FALSE);
    g_print("now start looper....\n");
    g_main_loop_run(loop);
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(pipeline));
    g_print("just stop looper....\n");
    return 0;
}

static void test_sometimes_pad_added_handle(GstElement *element, GstPad *pad, gpointer data) {
    gchar *name;
    name = gst_pad_get_name(pad);
    g_print("A new pad %s was created.\n", name);
    g_free(name);
}

static void test_sometimes_pad_removed_handle(GstElement *element, GstPad *pad, gpointer data) {
    gchar *name;
    name = gst_pad_get_name(pad);
    g_print("A pad %s was removed.\n", name);
    g_free(name);
}

/**
 * Hello World 测试
 *
 * @param argc
 * @param argv
 * @return
 */
int test_hello_world(int argc, char *argv[]) {
    GMainLoop *loop;
    GstBus *bus;
    gst_init(&argc, &argv);
    loop = g_main_loop_new(nullptr, FALSE);

    GstElement *pipeline, *source, *parser, *decoder, *conv, *sink;
    pipeline = gst_pipeline_new("audio-player-pipeline");
    if (!pipeline) {
        g_print("pipeline == null\n");
    }

    source = gst_element_factory_make("filesrc", "file-source");
    if (!source) {
        g_print("source == null\n");
    }

    parser = gst_element_factory_make("oggdemux", "ogg-parser");
    if (!parser) {
        g_print("parser == null\n");
    }

    decoder = gst_element_factory_make("vorbisdec", "vorbis-decoder");
    if (!decoder) {
        g_print("decoder == null\n");
    }

    conv = gst_element_factory_make("audioconvert", "converter");
    if (!conv) {
        g_print("conv == null\n");
    }

    sink = gst_element_factory_make("alsasink", "alsa-output");
    if (!sink) {
        g_print("sink == null\n");
    }

    /* set filename property on the file source. Also add a message handler. */
    g_object_set(G_OBJECT(source), "location", AUDIO_FILE_OGG, NULL);

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus, hello_world_bus_call_handle, loop);
    gst_object_unref(bus);

    /* put all elements in a bin */
    // bin是一个大的逻辑组 相距
    gst_bin_add_many(GST_BIN(pipeline), source, parser, decoder, conv, sink, NULL);
    /**
     * link together - note that we cannot link the parser and
     * decoder yet, becuse the parser uses dynamic pads. For that,
     * we set a pad-added signal handler.
     */
    gst_element_link(source, parser);
    gst_element_link_many(decoder, conv, sink, NULL);
    g_signal_connect(parser, "pad-added", G_CALLBACK(hello_world_pad_added_handle), decoder);

    /* Now set to playing and iterate. */
    g_print("Setting to PLAYING\n");
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_print("Running\n");
    g_main_loop_run(loop);

    /* clean up nicely */
    g_print("Returned, stopping playback\n");
    gst_element_set_state(pipeline, GST_STATE_NULL);
    g_print("Deleting pipeline\n");

    gst_object_unref(GST_OBJECT(pipeline));
    return 0;
}

static gboolean hello_world_bus_call_handle(GstBus *bus, GstMessage *msg, gpointer data) {
    GstMessageType msgType = GST_MESSAGE_TYPE(msg);
    const gchar *msgTypeName = gst_message_type_get_name(msgType);
    g_print("hello_world_bus_call_handle() msgType : %d, msgTypeName : %s\n", msgType, msgTypeName);

    GstState old_state, new_state, pending_state;
    gst_message_parse_state_changed(msg, &old_state, &new_state, &pending_state);
    g_print("                 Pipeline state changed from %s to %s:\n",
            gst_element_state_get_name(old_state), gst_element_state_get_name(new_state));

    auto *loop = (GMainLoop *) (data);
    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_EOS: {
            g_print("End-of-stream\n");
            g_main_loop_quit(loop);
            break;
        }
        case GST_MESSAGE_ERROR: {
            gchar *debug;
            GError *err;
            gst_message_parse_error(msg, &err, &debug);
            g_free(debug);
            g_print("hello_world_bus_call_handle() Error: %s\n", err->message);
            g_error_free(err);
            g_main_loop_quit(loop);
            break;
        }
        default:
            break;
    }
    return TRUE;
}

static void hello_world_pad_added_handle(GstElement *element, GstPad *new_pad, gpointer data) {
    GstPad *sinkpad;
    auto *p_decoder = (GstElement *) data;
    g_print("Dynamic pad created, linking parser/decoder\n");
    sinkpad = gst_element_get_static_pad(p_decoder, "sink");
    gst_pad_link(new_pad, sinkpad);
    gst_object_unref(sinkpad);
}