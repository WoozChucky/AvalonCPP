#include <Engine/Audio/AudioManager.h>
#include "Common/Logging/Log.h"
#include <thread>
#include <algorithm>
#include <SDL.h>

// Static function to bridge the callback
static void AudioRecordCallbackBridge(void *userdata, U8 *stream, int len) {
    static_cast<AudioManager*>(userdata)->AudioRecordCallback(userdata, stream, len);
}

// Static function to bridge the callback
static void AudioPlaybackCallbackBridge(void *userdata, U8 *stream, int len) {
    static_cast<AudioManager*>(userdata)->AudioPlaybackCallback(userdata, stream, len);
}

bool AudioManager::Initialize(const AudioRecordedCallback& audioRecordedCallback) {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        // Handle initialization error
        throw std::runtime_error("SDL_Init failed");
    }

    SDL_AudioSpec desiredRecordingSpec;
    SDL_zero(desiredRecordingSpec);
    desiredRecordingSpec.freq = 44100;
    desiredRecordingSpec.format = AUDIO_S16;
    desiredRecordingSpec.channels = 2;
    desiredRecordingSpec.samples = 4096;
    desiredRecordingSpec.callback = AudioRecordCallbackBridge;
    desiredRecordingSpec.userdata = this;

    auto gRecordingDeviceCount = SDL_GetNumAudioDevices(SDL_TRUE);
    if(gRecordingDeviceCount < 1)
    {
        LOG_ERROR("audio", "Unable to get audio capture device! SDL Error: {}", SDL_GetError());
        return false;
    }

    for(int i = 0; i < gRecordingDeviceCount; ++i)
    {
        //Get capture device name
        const char* deviceName = SDL_GetAudioDeviceName(i, SDL_TRUE);
        LOG_DEBUG("audio", "Capture Device {} = {}", i, deviceName);
    }

    auto gPlaybackDeviceCount = SDL_GetNumAudioDevices(SDL_FALSE);
    if(gPlaybackDeviceCount < 1)
    {
        LOG_ERROR("audio", "Unable to get audio playback device! SDL Error: {}", SDL_GetError());
        return false;
    }

    for(int i = 0; i < gPlaybackDeviceCount; ++i)
    {
        //Get capture device name
        const char* deviceName = SDL_GetAudioDeviceName(i, SDL_FALSE);
        LOG_DEBUG("audio", "Output Device {} = {}", i, deviceName);
    }

    //Open recording device
    _recordingDeviceId = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, SDL_TRUE), SDL_TRUE, &desiredRecordingSpec, &_recordingSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    // Device failed to open
    if(_recordingDeviceId == 0)
    {
        //Report error
        LOG_ERROR("audio", "Failed to open recording device! SDL Error: {}", SDL_GetError());
        return false;
    }

    //Default audio spec
    SDL_AudioSpec desiredPlaybackSpec;
    SDL_zero(desiredPlaybackSpec);
    desiredPlaybackSpec.freq = 44100;
    desiredPlaybackSpec.format = AUDIO_S16; // AUDIO_F32;
    desiredPlaybackSpec.channels = 2;
    desiredPlaybackSpec.samples = 4096;
    desiredPlaybackSpec.callback = AudioPlaybackCallbackBridge;
    desiredPlaybackSpec.userdata = this;

    //Open playback device
    _playbackDeviceId = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, SDL_FALSE), SDL_FALSE, &desiredPlaybackSpec, &_playbackSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE );
    //Device failed to open
    if(_playbackDeviceId == 0)
    {
        //Report error
        LOG_ERROR("audio", "Failed to open playback device! SDL Error: {}", SDL_GetError());
        return false;
    }

    //Calculate per sample bytes
    int recordingBytesPerSample = _recordingSpec.channels * (SDL_AUDIO_BITSIZE(_recordingSpec.format) / 8);
    //Calculate bytes per second
    int recordingBytesPerSecond = _recordingSpec.freq * recordingBytesPerSample;
    //Calculate buffer size
    auto recordingBufferInitialSize = RECORDING_BUFFER_SECONDS * recordingBytesPerSecond;

    _recordingBuffer.Resize(recordingBufferInitialSize);

    //Calculate per sample bytes
    int playbackBytesPerSample = _playbackSpec.channels * (SDL_AUDIO_BITSIZE(_playbackSpec.format) / 8);
    //Calculate bytes per second
    int playbackBytesPerSecond = _playbackSpec.freq * playbackBytesPerSample;
    //Calculate buffer size
    auto playbackBufferInitialSize = RECORDING_BUFFER_SECONDS * playbackBytesPerSecond;

    _playbackBuffer = new CircularBuffer(playbackBufferInitialSize);

    _audioStream = SDL_NewAudioStream(
            _recordingSpec.format, _recordingSpec.channels, _recordingSpec.freq,
            _playbackSpec.format, _playbackSpec.channels, _playbackSpec.freq
    );

    if(_audioStream == nullptr)
    {
        LOG_ERROR("audio", "Failed to create audio stream! SDL Error: {}", SDL_GetError());
        return false;
    }

    if (audioRecordedCallback != nullptr) {
        _audioRecordedCallback = audioRecordedCallback;
    }

    _audioEncoder.Initialize(kSampleRate, kChannels, kMaxFrameSize);
    _audioDecoder.Initialize(kSampleRate, kChannels, kMaxFrameSize);

    LOG_INFO("audio", "System initialized");
    return true;
}

void AudioManager::Shutdown() {
    _isRecording = false;
    _isPlaying = false;
    // Stop audio device
    SDL_PauseAudioDevice(_recordingDeviceId, SDL_TRUE);
    SDL_PauseAudioDevice(_playbackDeviceId, SDL_TRUE);

    //Unlock callback
    SDL_UnlockAudioDevice(_recordingDeviceId);
    SDL_UnlockAudioDevice(_playbackDeviceId);

    // Release the buffers
    _recordingBuffer.Release();
    delete _playbackBuffer;
    _playbackBuffer = nullptr;

    SDL_FreeAudioStream(_audioStream);

    SDL_Quit();

    LOG_INFO("audio", "Shutdown OK");
}

void AudioManager::RecordAudio(const RecordFinishedCallback& callback) {
    if (_isRecording) {
        return;
    }
    _isRecording = true;
    std::thread recordThread(&AudioManager::RecordAudioThread, this, callback);
    recordThread.detach();
}

void AudioManager::StopRecording() {
    if (!_isRecording) {
        return;
    }
    _isRecording = false;
    SDL_PauseAudioDevice(_recordingDeviceId, SDL_TRUE);
    SDL_AudioStreamFlush(_audioStream);

    // Clear the recording buffer
    _recordingBuffer.Release();
}

void AudioManager::PlaybackRecording() {
    if (_isPlaying) {
        return;
    }
    _isPlaying = true;
    std::thread playbackThread(&AudioManager::PlaybackRecordingThread, this);
    playbackThread.detach();
}

void AudioManager::StopPlayback() {
    if (!_isPlaying) {
        return;
    }
    _isPlaying = false;
    SDL_PauseAudioDevice(_playbackDeviceId, SDL_TRUE);

    // Clear the playback buffer
   // _playbackBuffer.Release();
}

AudioManager* AudioManager::Instance() {
    static AudioManager instance;
    return &instance;
}

void AudioManager::AudioRecordCallback(void *userdata, U8 *stream, int len) {
    //Copy audio from stream
    if (_audioRecordedCallback != nullptr) {
        /*
        std::vector<U8> pcmData = std::vector<U8>(stream, stream + len);
        std::vector<U8> encodedData;
        encodedData.reserve(16384);

        if (!_audioEncoder.Encode(&pcmData, &encodedData)) {
            return;
        }

        std::vector<U8> decodedData;
        decodedData.reserve(16384);

        if (!_audioDecoder.Decode(&encodedData, &decodedData)) {
            return;
        }
        */

        _audioRecordedCallback(stream, len);
    } else {
        SDL_AudioStreamPut(_audioStream, stream, len);
    }
}

void AudioManager::OnAudioReceived(U8 *stream, int len) {
    //Copy audio from stream
    SDL_AudioStreamPut(_audioStream, stream, len);
}

void AudioManager::AudioPlaybackCallback(void *userdata, U8 *stream, int len) {
    // First we need to check if there's any data in the playback buffer, if not, we can just return
    if (_playbackBuffer->IsEmpty()) {
        SDL_memset(stream, 0, len); // fill the stream with silence
        return;
    }

    int bytesToCopy = std::min(len, (int)_playbackBuffer->Size());

    auto tempBuffer =  _playbackBuffer->Read(bytesToCopy);
    std::memcpy(stream,  tempBuffer.data(), bytesToCopy);

    // If there's not enough data in the buffer, fill the rest of the stream with silence
    if (bytesToCopy < len) {
        SDL_memset(stream + bytesToCopy, 0, len - bytesToCopy);
    }
}

void AudioManager::RecordAudioThread(const RecordFinishedCallback& callback) {

    SDL_PauseAudioDevice( _recordingDeviceId, SDL_FALSE );

    while(_isRecording)
    {
        //Lock callback
        SDL_LockAudioDevice( _recordingDeviceId );

        //Unlock callback
        SDL_UnlockAudioDevice( _recordingDeviceId );
    }

    // Call the callback function if it's not nullptr
    if(callback != nullptr)
    {
        callback();
    }

    LOG_DEBUG("audio", "Recording thread finished");
}

void AudioManager::PlaybackRecordingThread() {
    SDL_PauseAudioDevice( _playbackDeviceId, SDL_FALSE );

    while(_isPlaying || SDL_AudioStreamAvailable(_audioStream) > 0)
    {
        //Lock callback
        SDL_LockAudioDevice( _playbackDeviceId );

        // Copy audio from stream
        int available = SDL_AudioStreamAvailable(_audioStream);
        if (available > 0) {
            LOG_DEBUG("audio", "Playback thread copying {} bytes", available);
            std::vector<char> tempBuffer(available);
            SDL_AudioStreamGet(_audioStream, tempBuffer.data(), available);

            _playbackBuffer->Write(tempBuffer);
        }

        //Unlock callback
        SDL_UnlockAudioDevice( _playbackDeviceId );
    }

    LOG_INFO("audio", "Playback thread finished");
}


