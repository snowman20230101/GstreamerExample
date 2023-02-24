//
// Created by wuwenbin on 2/22/23.
//

#include "gstreamer-save-file-demo.h"
#include "gst-def.h"

#define IS_H264 0

// https://trac.ffmpeg.org/wiki/Concatenate

int save_file_main(int argc, char *argv[]) {
    custom_data_save_file data;

    GstBus *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;
    gboolean terminate = FALSE;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    data.source = gst_element_factory_make("rtspsrc", "source");
    g_object_set(G_OBJECT (data.source), "latency", 2000, NULL);
    g_object_set(G_OBJECT (data.source), "location", TEST_URI_264_LOCAL, NULL);
    g_signal_connect (data.source, "pad-added", G_CALLBACK(save_h264_source_pad_added_handler), &data);

    data.depay = gst_element_factory_make("rtph264depay", "depay");
    data.parse = gst_element_factory_make("h264parse", "parse");
    g_object_set(G_OBJECT(data.parse), "config-interval", -1, NULL); // TODO sps pps 要加入在每一gop中

//    data.mp4mux = gst_element_factory_make("mp4mux", "mp4-mux");
    GstElementFactory *gstElementFactory = gst_element_factory_find("mp4mux");
    data.mp4mux = gst_element_factory_create(gstElementFactory, "mp4-mux");

    data.sink = gst_element_factory_make("filesink", "sink");
    g_object_set(G_OBJECT(data.sink), "location", "/home/wuwenbin/save.mp4", NULL);
    g_object_set(G_OBJECT (data.sink), "sync", FALSE, NULL);

    data.pipeline = gst_pipeline_new("save-file-pipeline");

    if (!data.pipeline || !data.source || !data.depay || !data.parse || !data.mp4mux || !data.sink) {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }

    gst_bin_add_many(GST_BIN(data.pipeline), data.source, data.depay, data.parse, data.mp4mux, data.sink, NULL);
#if IS_H264
    if (!gst_element_link_many(data.depay, data.parse, NULL)) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    // TODO You need to add elements to a pipeline/bin before linking them.
    GstCaps *new_caps = gst_caps_new_simple("video/x-h264",
                                            "stream-format", G_TYPE_STRING, "byte-stream",
                                            "parsed", G_TYPE_BOOLEAN, TRUE,
                                            NULL
    );

    if (!gst_element_link_filtered(data.parse, data.sink, new_caps)) {
        g_printerr("Element parse could not be linked to sink. \n");
        gst_object_unref(data.pipeline);
        return -1;
    }
    gst_caps_unref(new_caps);
#else
    if (!gst_element_link_many(data.depay, data.parse, NULL)) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    GstCaps *parse_new_caps = gst_caps_new_simple("video/x-h264",
                                                  "stream-format", G_TYPE_STRING, "avc",
                                                  "alignment", G_TYPE_STRING, "au",
                                                  "parsed", G_TYPE_BOOLEAN, TRUE,
                                                  NULL
    );

    if (!gst_element_link_filtered(data.parse, data.mp4mux, parse_new_caps)) {
        g_printerr("%d:Elements could not be linked filtered.\n", __LINE__);
        gst_object_unref(data.pipeline);
        return -1;
    }

    gst_caps_unref(parse_new_caps);

    if (!gst_element_link(data.mp4mux, data.sink)) {
        g_printerr("%d:Elements could not be linked.\n", __LINE__);
        gst_object_unref(data.pipeline);
        return -1;
    }

    GstPad *mp4_video_pad = gst_element_get_request_pad(data.mp4mux, "video_%u");
    g_print("Obtained request pad %s for video branch.\n", gst_pad_get_name(mp4_video_pad));
    GstPad *parse_src_pad = gst_element_get_static_pad(data.parse, "src");
    if (!parse_src_pad || !mp4_video_pad) {
        g_printerr("parse_src_pad == null or mp4_video_pad == null \n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    GstCaps *mp4_caps = gst_caps_new_simple("video/x-h264",
                                            "stream-format", G_TYPE_STRING, "avc",
                                            "alignment", G_TYPE_STRING, "au",
                                            "width", G_TYPE_INT, 1280,
                                            "height", G_TYPE_INT, 720,
                                            NULL
    );

    if (!gst_caps_is_fixed(mp4_caps)) {
        g_printerr("Failed to caps_is_fixed. \n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    if (!gst_element_factory_can_sink_all_caps(gstElementFactory, mp4_caps)) {
        g_printerr("Failed to set caps for pad.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    // TODO
//    if (!gst_pad_set_caps(mp4_video_pad, mp4_caps)) {
//        g_printerr("Failed to set caps for pad.\n");
//        gst_object_unref(data.pipeline);
//        return -1;
//    }

    gst_caps_unref(mp4_caps);

//    if (gst_pad_link(parse_src_pad, mp4_video_pad) != GST_PAD_LINK_OK) {
//        g_printerr("%d mp4mux pad could not be linked.\n", __LINE__);
//        gst_object_unref(data.pipeline);
//        return -1;
//    }

    if (gst_pad_link_full(parse_src_pad, mp4_video_pad, GST_PAD_LINK_CHECK_CAPS) != GST_PAD_LINK_OK) {
        g_printerr("%d mp4mux pad could not be linked.\n", __LINE__);
        gst_object_unref(data.pipeline);
        return -1;
    }

    gst_object_unref(parse_src_pad);
    gst_object_unref(mp4_video_pad);

#endif

    ret = gst_element_set_state(data.pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Unable to set the pipeline to the playing state.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    /* Listen to the bus */
    bus = gst_element_get_bus(data.pipeline);
    do {
        msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                         (GstMessageType) (GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR |
                                                           GST_MESSAGE_EOS));

        /* Parse message */
        if (msg != nullptr) {
            GError *err;
            gchar *debug_info;

            switch (GST_MESSAGE_TYPE (msg)) {
                case GST_MESSAGE_ERROR:
                    gst_message_parse_error(msg, &err, &debug_info);
                    g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
                    g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
                    g_clear_error(&err);
                    g_free(debug_info);
                    terminate = TRUE;
                    break;
                case GST_MESSAGE_EOS:
                    g_print("End-Of-Stream reached.\n");
                    terminate = TRUE;
                    break;
                case GST_MESSAGE_STATE_CHANGED:
                    /* We are only interested in state-changed messages from the pipeline */
                    if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
                        GstState old_state, new_state, pending_state;
                        gst_message_parse_state_changed(msg, &old_state, &new_state, &pending_state);
                        g_print("Pipeline state changed from %s to %s:\n",
                                gst_element_state_get_name(old_state), gst_element_state_get_name(new_state));
                    }
                    break;
                default:
                    /* We should not reach here */
                    g_printerr("Unexpected message received.\n");
                    break;
            }
            gst_message_unref(msg);
        }
    } while (!terminate);

    // Free resources
    gst_object_unref(bus);
    gst_element_set_state(data.pipeline, GST_STATE_NULL);
    gst_object_unref(data.pipeline);

    return 0;
}

static void save_h264_source_pad_added_handler(GstElement *src, GstPad *new_pad, custom_data_save_file *data) {
    GstPad *sink_pad = gst_element_get_static_pad(data->depay, "sink");
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = nullptr;
    GstStructure *new_pad_struct = nullptr;
    const gchar *new_pad_type = nullptr;

    g_print("Received new pad '%s' from '%s':\n", GST_PAD_NAME(new_pad), GST_ELEMENT_NAME(src));
    g_print("pad name is %s\n", gst_pad_get_name(new_pad));
    /* If our converter is already linked, we have nothing to do here */
    if (gst_pad_is_linked(sink_pad)) {
        g_print("We are already linked. Ignoring.\n");
        goto exit;
    }

    new_pad_caps = gst_pad_get_current_caps(new_pad);
    new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
    new_pad_type = gst_structure_get_name(new_pad_struct);

    ret = gst_pad_link(new_pad, sink_pad);
    if (GST_PAD_LINK_FAILED(ret)) {
        g_print("Type is '%s' but link failed.\n", new_pad_type);
    } else {
        g_print("Link succeeded (type '%s').\n", new_pad_type);
    }

    exit:

    if (new_pad_caps != nullptr)
        gst_caps_unref(new_pad_caps);

    gst_object_unref(sink_pad);
}