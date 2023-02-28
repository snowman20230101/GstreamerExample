//
// Created by windy on 2023/2/25.
// rtsp流保存为mp4文件。
//

#include "gstreamer-save-mp4-file-demp.h"
#include "gst-def.h"

// gst-launch-1.0 rtspsrc location=rtsp://192.168.56.129:8554/hanggai.264 ! rtph264depay ! h264parse ! avdec_h264 ! tee name=t ! queue leaky=1 ! videoconvert ! autovideosink sync=false t. ! queue !  x264enc ! filesink location=rtsp_test1.mp4

int save_file_mp4_main(int argc, char *argv[]) {
    custom_data_save_file data;

    GstBus *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;
    gboolean terminate = FALSE;

    gst_init(&argc, &argv);

    data.source = gst_element_factory_make("rtspsrc", "source");
    g_object_set(G_OBJECT (data.source), "latency", 2000, NULL);
    g_object_set(G_OBJECT (data.source), "location", TEST_URI_264, NULL);
    g_signal_connect (data.source, "pad-added", G_CALLBACK(save_mp4_source_pad_added_handler), &data);

    data.depay = gst_element_factory_make("rtph264depay", "depay");
    data.parse = gst_element_factory_make("h264parse", "parse");
    g_object_set(G_OBJECT(data.parse), "config-interval", -1, NULL); // TODO sps pps 要加入在每一gop中

    data.decoder = gst_element_factory_make("avdec_h264", "decoder");
    data.videoConvert = gst_element_factory_make("videoconvert", "convert");
    data.encoder = gst_element_factory_make("x264enc", "encoder");

    GstElementFactory *gstElementFactory = gst_element_factory_find("mp4mux");
    data.mp4mux = gst_element_factory_create(gstElementFactory, "mp4-mux");

    data.sink = gst_element_factory_make("filesink", "sink");
    g_object_set(G_OBJECT(data.sink), "location", TEST_SAVE_FILE_MP4, NULL);
    g_object_set(G_OBJECT(data.sink), "sync", FALSE, NULL);

    data.pipeline = gst_pipeline_new("save-file-pipeline");

    if (!data.pipeline || !data.source || !data.depay || !data.parse ||
        !data.decoder || !data.videoConvert || !data.encoder || !data.mp4mux || !data.sink) {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }

    gst_bin_add_many(GST_BIN(data.pipeline), data.source, data.depay,
                     data.parse, data.decoder, data.videoConvert, data.encoder, data.mp4mux, data.sink, NULL);

    if (!gst_element_link_many(data.depay, data.parse, data.decoder,
                               data.videoConvert, data.encoder, data.mp4mux, data.sink, NULL)) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

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

static void save_mp4_source_pad_added_handler(GstElement *src, GstPad *new_pad, custom_data_save_file *data) {
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