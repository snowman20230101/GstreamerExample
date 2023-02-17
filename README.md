# GstreamerExample

This is linux plugin.

gst-inspect-1.0 alsasink
Factory Details:
Rank                     primary (256)
Long-name                Audio sink (ALSA)
Klass                    Sink/Audio
Description              Output to a sound card via ALSA
Author                   Wim Taymans <wim@fluendo.com>

Plugin Details:
Name                     alsa
Description              ALSA plugin library
Filename                 /usr/lib/x86_64-linux-gnu/gstreamer-1.0/libgstalsa.so
Version                  1.16.3
License                  LGPL
Source module            gst-plugins-base
Source release date      2020-10-21
Binary package           GStreamer Base Plugins (Ubuntu)
Origin URL               https://launchpad.net/distros/ubuntu/+source/gst-plugins-base1.0

GObject
+----GInitiallyUnowned
+----GstObject
+----GstElement
+----GstBaseSink
+----GstAudioBaseSink
+----GstAudioSink
+----GstAlsaSink

Pad Templates:
SINK template: 'sink'
Availability: Always
Capabilities:
audio/x-raw
format: { (string)S8, (string)U8, (string)S16LE, (string)S16BE, (string)U16LE, (string)U16BE, (string)S24_32LE, (string)S24_32BE, (string)U24_32LE, (string)U24_32BE, (string)S32LE, (string)S32BE, (string)U32LE, (string)U32BE, (string)S24LE, (string)S24BE, (string)U24LE, (string)U24BE, (string)S20LE, (string)S20BE, (string)U20LE, (string)U20BE, (string)S18LE, (string)S18BE, (string)U18LE, (string)U18BE, (string)F32LE, (string)F32BE, (string)F64LE, (string)F64BE }
layout: interleaved
rate: [ 1, 2147483647 ]
channels: [ 1, 2147483647 ]
audio/x-ac3
framed: true
audio/x-eac3
framed: true
audio/x-dts
framed: true
block-size: { (int)512, (int)1024, (int)2048 }
audio/mpeg
mpegversion: 1
mpegaudioversion: [ 1, 3 ]
parsed: true

Clocking Interaction:
element is supposed to provide a clock but returned NULL
Element has no URI handling capabilities.

Pads:
SINK: 'sink'
Pad Template: 'sink'

Element Properties:
alignment-threshold : Timestamp alignment threshold in nanoseconds
flags: readable, writable
Unsigned Integer64. Range: 1 - 18446744073709551614 Default: 40000000
async               : Go asynchronously to PAUSED
flags: readable, writable
Boolean. Default: true
blocksize           : Size in bytes to pull per buffer (0 = default)
flags: readable, writable
Unsigned Integer. Range: 0 - 4294967295 Default: 4096
buffer-time         : Size of audio buffer in microseconds, this is the minimum latency that the sink reports
flags: readable, writable
Integer64. Range: 1 - 9223372036854775807 Default: 200000
can-activate-pull   : Allow pull-based scheduling
flags: readable, writable
Boolean. Default: false
card-name           : Human-readable name of the sound card
flags: readable
String. Default: "Ensoniq AudioPCI"
device              : ALSA device, as defined in an asound configuration file
flags: readable, writable
String. Default: "default"
device-name         : Human-readable name of the sound device
flags: readable
String. Default: null
discont-wait        : Window of time in nanoseconds to wait before creating a discontinuity
flags: readable, writable
Unsigned Integer64. Range: 0 - 18446744073709551614 Default: 1000000000
drift-tolerance     : Tolerance for clock drift in microseconds
flags: readable, writable
Integer64. Range: 1 - 9223372036854775807 Default: 40000
enable-last-sample  : Enable the last-sample property
flags: readable, writable
Boolean. Default: false
last-sample         : The last sample received in the sink
flags: readable
Boxed pointer of type "GstSample"
latency-time        : The minimum amount of data to write in each iteration in microseconds
flags: readable, writable
Integer64. Range: 1 - 9223372036854775807 Default: 10000
max-bitrate         : The maximum bits per second to render (0 = disabled)
flags: readable, writable
Unsigned Integer64. Range: 0 - 18446744073709551615 Default: 0
max-lateness        : Maximum number of nanoseconds that a buffer can be late before it is dropped (-1 unlimited)
flags: readable, writable
Integer64. Range: -1 - 9223372036854775807 Default: -1
name                : The name of the object
flags: readable, writable
String. Default: "alsasink0"
parent              : The parent of the object
flags: readable, writable
Object of type "GstObject"
processing-deadline : Maximum processing deadline in nanoseconds
flags: readable, writable
Unsigned Integer64. Range: 0 - 18446744073709551615 Default: 20000000
provide-clock       : Provide a clock to be used as the global pipeline clock
flags: readable, writable
Boolean. Default: true
qos                 : Generate Quality-of-Service events upstream
flags: readable, writable
Boolean. Default: false
render-delay        : Additional render delay of the sink in nanoseconds
flags: readable, writable
Unsigned Integer64. Range: 0 - 18446744073709551615 Default: 0
slave-method        : Algorithm used to match the rate of the masterclock
flags: readable, writable
Enum "GstAudioBaseSinkSlaveMethod" Default: 1, "skew"
(0): resample         - GST_AUDIO_BASE_SINK_SLAVE_RESAMPLE
(1): skew             - GST_AUDIO_BASE_SINK_SLAVE_SKEW
(2): none             - GST_AUDIO_BASE_SINK_SLAVE_NONE
(3): custom           - GST_AUDIO_BASE_SINK_SLAVE_CUSTOM
sync                : Sync on the clock
flags: readable, writable
Boolean. Default: true
throttle-time       : The time to keep between rendered buffers (0 = disabled)
flags: readable, writable
Unsigned Integer64. Range: 0 - 18446744073709551615 Default: 0
ts-offset           : Timestamp offset in nanoseconds
flags: readable, writable
Integer64. Range: -9223372036854775808 - 9223372036854775807 Default: 0 
