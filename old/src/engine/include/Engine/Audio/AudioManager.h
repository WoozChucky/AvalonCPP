#pragma once
#include <Common/Types.h>
#include <Common/Utilities/MessageBuffer.h>
#include <SDL2/SDL_audio.h>
#include <functional>
#include "AudioEncoder.h"
#include "AudioDecoder.h"
#include "Common/Utilities/CircularBuffer.h"
#include <Engine/Settings.h>

using namespace Avalon::Engine;

typedef std::function<void()> RecordFinishedCallback;
typedef std::function<void(U8* stream, int len)> AudioRecordedCallback;

class AudioManager {

public:
    bool Initialize(AudioSettings& settings, const AudioRecordedCallback& audioRecordedCallback = nullptr);
    void Shutdown();

    void RecordAudio(const RecordFinishedCallback& = nullptr);
    void StopRecording();
    void Playback();
    void StopPlayback();

    bool IsRecording() const { return _isRecording; }
    bool IsPlaying() const { return _isPlaying; }

    std::vector<std::string> GetInputDevices();
    std::vector<std::string> GetOutputDevices();

    static AudioManager* Instance();

    void AudioRecordCallback(void* userdata, U8* stream, int len );
    void AudioPlaybackCallback(void* userdata, U8* stream, int len);
    void OnAudioReceived(U8* stream, int len);

    std::string& GetOutputDeviceName();
    std::string& GetInputDeviceName();

private:

    AudioSettings* _settings;

    //Maximum recording time
    static constexpr int MAX_RECORDING_SECONDS = 10;
    //Maximum recording time plus padding
    static constexpr int RECORDING_BUFFER_SECONDS = MAX_RECORDING_SECONDS + 1;

    AudioManager() = default;
    ~AudioManager() = default;
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    bool OpenAudioDevice(std::string& deviceName, SDL_AudioSpec& desiredSpec, SDL_AudioSpec& returnedSpec, SDL_AudioDeviceID& deviceId, bool isRecording);
    bool OpenRecordingDevice();
    bool OpenPlaybackDevice();

    SDL_AudioDeviceID _recordingDeviceId = 0;
    SDL_AudioSpec _recordingSpec;
    bool _isRecording = false;

    SDL_AudioStream *_audioStream = nullptr;
    SDL_AudioDeviceID _playbackDeviceId = 0;
    SDL_AudioSpec _playbackSpec;
    bool _isPlaying = false;

    AudioRecordedCallback _audioRecordedCallback = nullptr;

    AudioEncoder _audioEncoder;
    AudioDecoder _audioDecoder;
};

#define sAudio AudioManager::Instance()
