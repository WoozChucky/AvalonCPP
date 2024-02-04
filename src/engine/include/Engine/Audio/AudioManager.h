#pragma once
#include <Common/Types.h>
#include <SDL2/SDL_audio.h>
#include <functional>

typedef std::function<void()> RecordFinishedCallback;

class AudioManager {

public:
    bool Initialize();
    void Shutdown();

    void RecordAudio(U32 seconds, const RecordFinishedCallback& = nullptr);
    void PlaybackRecording();

    static AudioManager* Instance();

    void AudioRecordCallback(void* userdata, U8* stream, int len );
    void AudioPlaybackCallback(void* userdata, U8* stream, int len);

private:

    static constexpr int MAX_RECORDING_DEVICES = 10;
    static constexpr int MAX_PLAYBACK_DEVICES = 10;

    //Maximum recording time
    static constexpr int MAX_RECORDING_SECONDS = 60;
    //Maximum recording time plus padding
    static constexpr int RECORDING_BUFFER_SECONDS = MAX_RECORDING_SECONDS + 1;

    AudioManager() = default;
    ~AudioManager() = default;
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    void RecordAudioThread(U32 seconds, const RecordFinishedCallback& = nullptr);
    void PlaybackRecordingThread();

    SDL_AudioDeviceID _recordingDeviceId = 0;
    SDL_AudioSpec _playbackSpec;
    U8* _recordingBuffer = nullptr;
    U32 _recordingBufferByteSize = 0;
    U32 _recordingBufferPosition = 0;
    U32 _recordingBufferMaxPosition = 0;


    SDL_AudioDeviceID _playbackDeviceId = 0;
    SDL_AudioSpec _recordingSpec;
    U8* _playbackBuffer = nullptr;
    U32 _playbackBufferByteSize = 0;
    U32 _playbackBufferPosition = 0;
    U32 _playbackBufferMaxPosition = 0;

};

#define sAudio AudioManager::Instance()