#include <Engine/Audio/AudioManager.h>
#include "Common/Logging/Log.h"
#include <thread>

// Static function to bridge the callback
static void AudioRecordCallbackBridge(void *userdata, U8 *stream, int len) {
    static_cast<AudioManager*>(userdata)->AudioRecordCallback(userdata, stream, len);
}

// Static function to bridge the callback
static void AudioPlaybackCallbackBridge(void *userdata, U8 *stream, int len) {
    static_cast<AudioManager*>(userdata)->AudioPlaybackCallback(userdata, stream, len);
}

bool AudioManager::Initialize() {

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
    _recordingDeviceId = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(1, SDL_TRUE), SDL_TRUE, &desiredRecordingSpec, &_recordingSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
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
    _recordingBufferByteSize = RECORDING_BUFFER_SECONDS * recordingBytesPerSecond;
    //Calculate max buffer use
    _recordingBufferMaxPosition = MAX_RECORDING_SECONDS * recordingBytesPerSecond;

    _recordingBuffer = new U8[_recordingBufferByteSize];
    std::memset(_recordingBuffer, 0, _recordingBufferByteSize);
    _recordingBufferPosition = 0;

    //Calculate per sample bytes
    int playbackBytesPerSample = _playbackSpec.channels * (SDL_AUDIO_BITSIZE(_playbackSpec.format) / 8);
    //Calculate bytes per second
    int playbackBytesPerSecond = _playbackSpec.freq * playbackBytesPerSample;
    //Calculate buffer size
    _playbackBufferByteSize = RECORDING_BUFFER_SECONDS * playbackBytesPerSecond;
    //Calculate max buffer use
    _playbackBufferMaxPosition = MAX_RECORDING_SECONDS * playbackBytesPerSecond;

    _playbackBuffer = new U8[_playbackBufferByteSize];
    std::memset(_playbackBuffer, 0, _playbackBufferByteSize);
    _playbackBufferPosition = 0;

    LOG_INFO("audio", "System initialized");
    return true;
}

void AudioManager::Shutdown() {
    // Stop audio device
    SDL_PauseAudioDevice(_recordingDeviceId, SDL_TRUE);
    SDL_PauseAudioDevice(_playbackDeviceId, SDL_TRUE);

    //Unlock callback
    SDL_UnlockAudioDevice(_recordingDeviceId);
    SDL_UnlockAudioDevice(_playbackDeviceId);

    if( _recordingBuffer != nullptr )
    {
        delete[] _recordingBuffer;
        _recordingBuffer = nullptr;
    }

    if ( _playbackBuffer != nullptr )
    {
        delete [] _playbackBuffer;
        _playbackBuffer = nullptr;
    }

    LOG_INFO("audio", "Shutdown OK");
}

void AudioManager::RecordAudio(U32 seconds, const RecordFinishedCallback& callback) {
    std::thread recordThread(&AudioManager::RecordAudioThread, this, seconds, callback);
    recordThread.detach();
}

AudioManager* AudioManager::Instance() {
    static AudioManager instance;
    return &instance;
}

void AudioManager::AudioRecordCallback(void *userdata, U8 *stream, int len) {
    //Copy audio from stream
    std::memcpy(&_recordingBuffer[ _recordingBufferPosition ], stream, len);
    //Move along buffer
    _recordingBufferPosition += len;
}

void AudioManager::AudioPlaybackCallback(void *userdata, U8 *stream, int len) {
    //Copy audio from stream
    std::memcpy(&_playbackBuffer[ _playbackBufferPosition ], stream, len);
    //Move along buffer
    _playbackBufferPosition += len;
}

void AudioManager::RecordAudioThread(U32 seconds, const RecordFinishedCallback& callback) {
    auto startTime = std::chrono::high_resolution_clock::now();

    SDL_PauseAudioDevice( _recordingDeviceId, SDL_FALSE );

    while(true)
    {
        //Lock callback
        SDL_LockAudioDevice( _recordingDeviceId );

        //Finished recording
        if(_recordingBufferPosition > _recordingBufferMaxPosition)
        {
            //Stop recording audio
            SDL_PauseAudioDevice( _recordingDeviceId, SDL_TRUE );
            break;
        }

        // Check if the specified number of seconds has passed
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        if(elapsedSeconds >= seconds)
        {
            //Stop recording audio
            SDL_PauseAudioDevice( _recordingDeviceId, SDL_TRUE );
            break;
        }

        //Unlock callback
        SDL_UnlockAudioDevice( _recordingDeviceId );
    }

    // Call the callback function if it's not nullptr
    if(callback != nullptr)
    {
        callback();
    }
}

void AudioManager::PlaybackRecording() {

}
