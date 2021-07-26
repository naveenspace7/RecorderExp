//
// Created by jan1ein on 7/20/21.
//

#include "AudioEngine.h"

const int * AudioEngine::getSamples(int n_samples)
{
//    AAudioStream_read(m_stream, m_data, n_samples, 1000);
    return m_data;
}

//
//oboe::DataCallbackResult
//RecordingCallback::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
//    return processRecordingFrames(audioStream, static_cast<int16_t *>(audioData), numFrames * audioStream->getChannelCount());
//}
//
//oboe::DataCallbackResult
//RecordingCallback::processRecordingFrames(oboe::AudioStream *audioStream, int16_t *audioData, int32_t numFrames) {
//
//    LOGD(TAG, "processRecordingFrames(): ");
//    int32_t framesWritten = mSoundRecording->write(audioData, numFrames);
//    return oboe::DataCallbackResult::Continue;
//
//}

/////////////////////

void AudioEngine::SetupParams(oboe::AudioStreamBuilder* builder)
{
    using namespace oboe;
    builder->setDeviceId(VoiceRecognition);
    builder->setDirection(Direction::Input);
    builder->setSharingMode(SharingMode::Exclusive);
    builder->setPerformanceMode(PerformanceMode::LowLatency);
    builder->setAudioApi(AudioApi::AAudio);
    builder->setFormat(AudioFormat::I16);
//    builder->setChannelCount(ChannelCount::Stereo);
}

bool AudioEngine::StartEngine()
{
    using namespace oboe;

    Result resultState;

    AudioStreamBuilder builder;
    SetupParams(&builder);

    resultState = builder.openStream(&mStream);
    if (resultState != Result::OK)
    {
        LOGE("Error while opening stream: %s", convertToText(resultState));
        return false;
    }

    resultState = mStream->requestStart();
    if (resultState != Result::OK)
    {
        LOGE("Error while requesting the stream to start: %s", convertToText(resultState));
        return false;
    }

//    ClearStreamBuffer();

    return true;
}

bool AudioEngine::StopEngine()
{

}

bool AudioEngine::ClearStreamBuffer()
{
    using namespace oboe;
    Result resultState = mStream->requestFlush();

    if (resultState != Result::OK) {
        LOGE("Error while requesting the stream to flush: %s", convertToText(resultState));
        return false;
    }

    return true;
}

oboe::DataCallbackResult AudioEngine::onAudioReady(oboe::AudioStream * oboeStream, void * audioData, int32_t nFrames)
{
    const int64_t timeoutNs = 10;
    auto result = mStream->read(audioData, nFrames, timeoutNs);
    if (result == oboe::Result::OK)
    {
        if (result.value() < nFrames)
//            samplesPerframe
            memset(static_cast<int16_t*>(audioData) + result.value() * 10, 0, (nFrames - result.value()) * mStream->getBytesPerFrame());
        return oboe::DataCallbackResult::Continue;
    }

    return oboe::DataCallbackResult::Stop;
}

std::pair<const int *, int> GetSamples(int n_samples)
{

}