#pragma once
#include <Common/Types.h>
#include <Common/Utilities/MessageBuffer.h>
#include <SDL2/SDL_audio.h>
#include <opus/opus.h>
#include <functional>

typedef std::function<void()> RecordFinishedCallback;
typedef std::function<void(U8* stream, int len)> AudioRecordedCallback;

class AudioManager {

public:
    bool Initialize(const AudioRecordedCallback& audioRecordedCallback = nullptr);
    void Shutdown();

    void RecordAudio(const RecordFinishedCallback& = nullptr);
    void StopRecording();
    void PlaybackRecording();
    void StopPlayback();

    static AudioManager* Instance();

    void AudioRecordCallback(void* userdata, U8* stream, int len );
    void AudioPlaybackCallback(void* userdata, U8* stream, int len);
    void OnAudioReceived(U8* stream, int len);

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

    AudioRecordedCallback _audioRecordedCallback = nullptr;

    // Define Opus encoder parameters
    OpusEncoder* encoder;
    static constexpr int kSampleRate = 44100;    // Sample rate (Hz)
    static constexpr int kChannels = 2;           // Number of audio channels (stereo)
    static constexpr int kApplication = OPUS_APPLICATION_VOIP; // Opus application mode for VoIP
    static constexpr int kMaxFrameSize = 960;     // Maximum frame size in samples (20 ms at 48 kHz)
    static constexpr int kBitrate = 24000;        // Target bitrate for stereo audio (24 kbps)

};

#define sAudio AudioManager::Instance()
