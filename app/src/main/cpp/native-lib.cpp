#include <jni.h>
#include <string>

#include "AudioEngine.h"

static AudioEngine* audioEngine = new AudioEngine();

//#define  LOG_TAG    "JNI"
//#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
//#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
//#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
//#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

extern "C" {

JNIEXPORT jstring JNICALL Java_com_example_nativeexample_MainActivity_stringFromJNI(JNIEnv *env,
                                                                                    jobject /* this */)
{
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jint JNICALL Java_com_example_nativeexample_MainActivity_addNums(JNIEnv *env, jobject /* this */,
                                                    jint a, jint b)
{
    AudioEngine ae;
    int s = ae.getNumber();
    return a + b + s;
}

JNIEXPORT jintArray JNICALL Java_com_example_nativeexample_MainActivity_getArr(JNIEnv *env,
                                                                          jobject /* this */)
{
    AudioEngine ae;
    int s = ae.getNumber();
    Arr xarr = ae.getArray();
    xarr.fill(7);

    int * data = xarr.m_data;
    int d_size = xarr.m_size;

    jintArray res = env->NewIntArray(d_size);
    env->SetIntArrayRegion(res, 0, d_size, data);

    return res;
}

////////////

// Start Recorder
JNIEXPORT jboolean JNICALL Java_com_example_nativeexample_MainActivity_jniStartRecording(JNIEnv *env,
                                                                                         jobject /* this */)
{
    return audioEngine->StartEngine();
//    return true;
}

// Stop Recorder
JNIEXPORT jboolean JNICALL Java_com_example_nativeexample_MainActivity_jniStopRecording(JNIEnv *env,
                                                                                        jobject /* this */)
{
    return true;

}

// Clear Stream
JNIEXPORT jboolean JNICALL Java_com_example_nativeexample_MainActivity_jniClearStream(JNIEnv *env,
                                                                                      jobject /* this */)
{
//    LOGD("Clear Streams");
    return true;
}

JNIEXPORT jintArray JNICALL Java_com_example_nativeexample_MainActivity_jniGetSamples(JNIEnv *env,
                                                                                   jobject /* this */,
                                                                                   jint n_samples)
{
//    LOGD("Get Samples");
//    jintArray jni_data = env->NewIntArray(n_samples);
//    const int * data = audioEngine->getSamples(n_samples);
//    env->SetIntArrayRegion(jni_data, 0, n_samples, data);
//    return jni_data;
}
}