#include <libusb.h>
#include <rtl-sdr.h>
#include <jni.h>
#include <stdio.h>

static rtlsdr_dev_t *dev = NULL;

JNIEXPORT jint JNICALL
Java_threadfool_op_RtlSdr_open(JNIEnv *env, jobject obj, jint index) {
    uint32_t count = rtlsdr_get_device_count();
    printf("RTL-SDR devices: %u\n", count);

    for (uint32_t i = 0; i < count; i++) {
        printf("Device %u: %s\n", i, rtlsdr_get_device_name(i));
    }

    int r = rtlsdr_open(&dev, index);
    if (r < 0) {
        fprintf(stderr, "rtlsdr_open failed with code %d\n", r);

        libusb_context *ctx;
        libusb_init(&ctx);
        libusb_device **list;
        ssize_t cnt = libusb_get_device_list(ctx, &list);
        printf("libusb sees %ld devices\n", cnt);
        libusb_free_device_list(list, 1);
        libusb_exit(ctx);

        return r;
    }

    rtlsdr_set_tuner_gain_mode(dev, 0);
    rtlsdr_reset_buffer(dev);
    return 0;
}

JNIEXPORT jint JNICALL Java_threadfool_op_RtlSdr_setCenterFreq
  (JNIEnv *env, jobject obj, jint freq)
{
    return rtlsdr_set_center_freq(dev, freq);
}

JNIEXPORT jint JNICALL Java_threadfool_op_RtlSdr_setSampleRate
  (JNIEnv *env, jobject obj, jint rate)
{
    return rtlsdr_set_sample_rate(dev, rate);
}

JNIEXPORT jint JNICALL Java_threadfool_op_RtlSdr_setGain
  (JNIEnv *env, jobject obj, jint gain)
{
    rtlsdr_set_tuner_gain_mode(dev, 1);
    return rtlsdr_set_tuner_gain(dev, gain);
}

JNIEXPORT jint JNICALL Java_threadfool_op_RtlSdr_resetBuffer
  (JNIEnv *env, jobject obj)
{
    return rtlsdr_reset_buffer(dev);
}

JNIEXPORT jint JNICALL Java_threadfool_op_RtlSdr__read
  (JNIEnv *env, jobject obj, jbyteArray arr, jint len)
{
    jbyte *buf = (*env)->GetByteArrayElements(env, arr, NULL);
    int n_read = 0;

    rtlsdr_read_sync(dev, (unsigned char *)buf, len, &n_read);

    (*env)->ReleaseByteArrayElements(env, arr, buf, 0);
    return n_read;
}

JNIEXPORT void JNICALL Java_threadfool_op_RtlSdr__close
  (JNIEnv *env, jobject obj)
{
    if (dev) {
        rtlsdr_close(dev);
        dev = NULL;
    }
}
