//
// Created by jan1ein on 7/20/21.
//

#ifndef NATIVEEXAMPLE_AUDIOENGINE_H
#define NATIVEEXAMPLE_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include <android/input.h>
#include <utility>

#include <android/log.h>

#define  LOG_TAG    "AudioEngine"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

class Arr {
public:
    int * m_data;
    int m_size;

    Arr(int size): m_size(size) {
        m_data = new int[m_size];
    }

    void fill(int n) {
        for (int i = 0; i < m_size; i++) {
            m_data[i] = n;
        }
    }

    ~Arr() {
        delete[] m_data;
    }
};

//class RecordingCallback : public oboe::AudioStreamCallback {
//
//private:
////    const char* TAG = "RecordingCallback:: %s";
////    oboe::SoundRecording* mSoundRecording = nullptr;
//
//public:
//    RecordingCallback() = default;
//
////    explicit RecordingCallback(oboe::SoundRecording* recording) {
////        mSoundRecording = recording;
////    }
//
//    oboe::DataCallbackResult
//    onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames);
//
//    oboe::DataCallbackResult
//    processRecordingFrames(oboe::AudioStream *audioStream, int16_t *audioData, int32_t numFrames);
//};

class AudioEngine: oboe::AudioStreamDataCallback {

private:
    oboe::AudioStream *mStream;
    int m_data[1000];

public:

    oboe::DataCallbackResult onAudioReady(oboe::AudioStream * oboeStream, void * audioData, int32_t nFrames);
    bool StartEngine();
    bool StopEngine();
    bool ClearStreamBuffer();
    std::pair<const int *, int> GetSamples(int n_samples);
    void SetupParams(oboe::AudioStreamBuilder* builder);

//    const int * GetSamples(int n_samples);

    int getNumber()
    {
        return 7;
    }

    Arr getArray()
    {
        Arr a(10);
        a.fill(8);
        return a;
    }


    const int * getSamples(int);
};


#endif //NATIVEEXAMPLE_AUDIOENGINE_H
