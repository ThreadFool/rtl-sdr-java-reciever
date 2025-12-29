#include <jni.h>
#include <rtl-sdr.h>

static rtlsdr_dev_t *dev = NULL;

JNIEXPORT jint JNICALL Java_threadfool_op_RtlSdr_open
  (JNIEnv *env, jobject obj, jint index)
{
    return rtlsdr_open(&dev, index);
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
