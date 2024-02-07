#pragma once
#include <Common/Types.h>
#include <Common/Utilities/MessageBuffer.h>
#include <SDL2/SDL_audio.h>
#include <opus/opus.h>
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

    void RecordAudioThread(const RecordFinishedCallback& = nullptr);
    void PlaybackRecordingThread();

    SDL_AudioDeviceID _recordingDeviceId = 0;
    SDL_AudioSpec _recordingSpec;
    MessageBuffer _recordingBuffer;
    bool _isRecording = false;

    SDL_AudioStream *_audioStream = nullptr;
    SDL_AudioDeviceID _playbackDeviceId = 0;
    SDL_AudioSpec _playbackSpec;
    CircularBuffer* _playbackBuffer;
    bool _isPlaying = false;

    AudioRecordedCallback _audioRecordedCallback = nullptr;

    // Define Opus parameters
    AudioEncoder _audioEncoder;
    AudioDecoder _audioDecoder;
    static constexpr int kSampleRate = 48000;    // Sample rate (Hz)
    static constexpr int kChannels = 1;           // Number of audio channels (stereo)
    static constexpr int kApplication = OPUS_APPLICATION_VOIP; // Opus application mode for VoIP
    static constexpr int kMaxFrameSize = 960;     // Maximum frame size in samples (20 ms at 48 kHz)
    static constexpr int kBitrate = 24000;        // Target bitrate for stereo audio (24 kbps)

};

#define sAudio AudioManager::Instance()
