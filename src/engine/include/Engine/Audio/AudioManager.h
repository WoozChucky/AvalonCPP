#pragma once
#include <Common/Types.h>
#include <Common/Utilities/MessageBuffer.h>
#include <SDL2/SDL_audio.h>
#include <functional>

typedef std::function<void()> RecordFinishedCallback;

class AudioManager {

public:
    bool Initialize();
    void Shutdown();

    void RecordAudio(const RecordFinishedCallback& = nullptr);
    void StopRecording();
    void PlaybackRecording();
    void StopPlayback();

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

    void RecordAudioThread(const RecordFinishedCallback& = nullptr);
    void PlaybackRecordingThread();

    SDL_AudioDeviceID _recordingDeviceId = 0;
    SDL_AudioSpec _recordingSpec;
    MessageBuffer _recordingBuffer;
    bool _isRecording = false;

    SDL_AudioStream *_audioStream = nullptr;
    SDL_AudioDeviceID _playbackDeviceId = 0;
    SDL_AudioSpec _playbackSpec;
    MessageBuffer _playbackBuffer;
    bool _isPlaying = false;

};

#define sAudio AudioManager::Instance()
