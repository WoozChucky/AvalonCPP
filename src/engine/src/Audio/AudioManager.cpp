#if 0
#include <Engine/Audio/AudioManager.h>
#include "Common/Logging/Log.h"
#include <thread>
#include <algorithm>
#include <SDL.h>
#include <zlib.h>
#include <cassert>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

using namespace Avalon::Engine;

// Static function to bridge the callback
static void AudioRecordCallbackBridge(void *userdata, U8 *stream, int len) {
    static_cast<AudioManager*>(userdata)->AudioRecordCallback(userdata, stream, len);
}

// Static function to bridge the callback
static void AudioPlaybackCallbackBridge(void *userdata, U8 *stream, int len) {
    static_cast<AudioManager*>(userdata)->AudioPlaybackCallback(userdata, stream, len);
}

bool AudioManager::Initialize(AudioSettings& settings, const AudioRecordedCallback& audioRecordedCallback) {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        // Handle initialization error
        throw std::runtime_error("SDL_Init failed");
    }

    _settings = &settings;

    if (!OpenRecordingDevice()) {
        return false;
    }

    if (!OpenPlaybackDevice()) {
        return false;
    }

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

    Playback();

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

    _audioRecordedCallback = nullptr;

    SDL_FreeAudioStream(_audioStream);

    SDL_Quit();

    LOG_INFO("audio", "Shutdown OK");
}

bool AudioManager::OpenAudioDevice(std::string& deviceName, SDL_AudioSpec& desiredSpec,  SDL_AudioSpec& returnedSpec, SDL_AudioDeviceID& deviceId, bool isRecording) {
    // Maximum number of attempts to open the device
    const int maxAttempts = 2;

    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        // If the device name is not specified or the previous attempt failed, get the default device
        if (deviceName.empty() || deviceId == 0) {
            deviceName = SDL_GetAudioDeviceName(0, isRecording ? SDL_TRUE : SDL_FALSE);
        }

        // Try to open the device
        deviceId = SDL_OpenAudioDevice(deviceName.c_str(), isRecording ? SDL_TRUE : SDL_FALSE, &desiredSpec, &returnedSpec, 0);

        // If the device was successfully opened, break the loop
        if (deviceId != 0) {
            break;
        }
    }

    // If the device could not be opened after the maximum number of attempts, report an error
    if (deviceId == 0) {
        LOG_ERROR("audio", "Failed to open {} device! SDL Error: {}", isRecording ? "recording" : "playback", SDL_GetError());
        return false;
    }

    return true;
}

bool AudioManager::OpenRecordingDevice() {
    SDL_AudioSpec desiredRecordingSpec;
    SDL_zero(desiredRecordingSpec);
    desiredRecordingSpec.freq = 48000;
    desiredRecordingSpec.format = AUDIO_S16;
    desiredRecordingSpec.channels = 2;
    desiredRecordingSpec.samples = 4096;
    desiredRecordingSpec.callback = AudioRecordCallbackBridge;
    desiredRecordingSpec.userdata = this;

    return OpenAudioDevice(_settings->InputDevice, desiredRecordingSpec, _recordingSpec, _recordingDeviceId, true);
}

bool AudioManager::OpenPlaybackDevice() {
    SDL_AudioSpec desiredPlaybackSpec;
    SDL_zero(desiredPlaybackSpec);
    desiredPlaybackSpec.freq = 48000;
    desiredPlaybackSpec.format = AUDIO_S16;
    desiredPlaybackSpec.channels = 2;
    desiredPlaybackSpec.samples = 4096;
    desiredPlaybackSpec.callback = AudioPlaybackCallbackBridge;
    desiredPlaybackSpec.userdata = this;

    return OpenAudioDevice(_settings->OutputDevice, desiredPlaybackSpec, _playbackSpec, _playbackDeviceId, false);
}

std::vector<std::string> AudioManager::GetInputDevices() {
    std::vector<std::string> devices;
    int numDevices = SDL_GetNumAudioDevices(SDL_TRUE);
    devices.reserve(numDevices);
    for (int i = 0; i < numDevices; i++) {
        devices.emplace_back(SDL_GetAudioDeviceName(i, SDL_TRUE));
    }
    return devices;
}

std::vector<std::string> AudioManager::GetOutputDevices() {
    std::vector<std::string> devices;
    int numDevices = SDL_GetNumAudioDevices(SDL_FALSE);
    devices.reserve(numDevices);
    for (int i = 0; i < numDevices; i++) {
        devices.emplace_back(SDL_GetAudioDeviceName(i, SDL_FALSE));
    }
    return devices;
}

void AudioManager::RecordAudio(const RecordFinishedCallback& callback) {
    if (_isRecording) {
        return;
    }
    _isRecording = true;

    SDL_PauseAudioDevice( _recordingDeviceId, SDL_FALSE );

    LOG_DEBUG("audio", "Recording thread finished");
}

void AudioManager::StopRecording() {
    if (!_isRecording) {
        return;
    }
    _isRecording = false;
    SDL_PauseAudioDevice(_recordingDeviceId, SDL_TRUE);
    SDL_AudioStreamFlush(_audioStream);
}

void AudioManager::Playback() {
    if (_isPlaying) {
        return;
    }
    _isPlaying = true;
    SDL_PauseAudioDevice( _playbackDeviceId, SDL_FALSE );
    LOG_INFO("audio", "Playback thread finished");
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

void compress_memory(void *in_data, size_t in_data_size, std::vector<uint8_t> &out_data)
{
    std::vector<uint8_t> buffer;

    const size_t BUFSIZE = 128 * 1024;
    uint8_t temp_buffer[BUFSIZE];

    z_stream strm;
    strm.zalloc = 0;
    strm.zfree = 0;
    strm.next_in = reinterpret_cast<uint8_t *>(in_data);
    strm.avail_in = in_data_size;
    strm.next_out = temp_buffer;
    strm.avail_out = BUFSIZE;

    deflateInit(&strm, Z_BEST_COMPRESSION);

    while (strm.avail_in != 0)
    {
        int res = deflate(&strm, Z_NO_FLUSH);
        assert(res == Z_OK);
        if (strm.avail_out == 0)
        {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFSIZE;
        }
    }

    int deflate_res = Z_OK;
    while (deflate_res == Z_OK)
    {
        if (strm.avail_out == 0)
        {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFSIZE;
        }
        deflate_res = deflate(&strm, Z_FINISH);
    }

    assert(deflate_res == Z_STREAM_END);
    buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE - strm.avail_out);
    deflateEnd(&strm);

    out_data.swap(buffer);
}

void uncompress_memory(const std::vector<uint8_t>& in_data, std::vector<uint8_t>& out_data) {
    std::vector<uint8_t> buffer;

    const size_t BUFSIZE = 128 * 1024;
    uint8_t temp_buffer[BUFSIZE];

    z_stream strm;
    strm.zalloc = 0;
    strm.zfree = 0;
    strm.next_in = const_cast<uint8_t*>(in_data.data());
    strm.avail_in = in_data.size();
    strm.next_out = temp_buffer;
    strm.avail_out = BUFSIZE;

    inflateInit(&strm);

    while (strm.avail_in != 0) {
        int res = inflate(&strm, Z_NO_FLUSH);
        assert(res != Z_STREAM_ERROR);
        switch (res) {
            case Z_NEED_DICT:
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&strm);
                std::cerr << "Error while decompressing data" << std::endl;
                return;
        }

        if (strm.avail_out == 0) {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFSIZE;
        }
    }

    int inflate_res = Z_OK;
    while (inflate_res == Z_OK) {
        if (strm.avail_out == 0) {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFSIZE;
        }
        inflate_res = inflate(&strm, Z_FINISH);
        switch (inflate_res) {
            case Z_NEED_DICT:
            case Z_STREAM_ERROR:
                inflateEnd(&strm);
                std::cerr << "Error while decompressing data" << std::endl;
                return;
        }
    }

    assert(inflate_res == Z_STREAM_END);
    buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE - strm.avail_out);
    inflateEnd(&strm);

    out_data.swap(buffer);
}

void AudioManager::AudioRecordCallback(void *userdata, U8 *stream, int len) {
    if (!_isRecording) {
        return;
    }

    const int num_samples = len / sizeof(S16);
    S16* samples = (S16*)stream;
    for (int i = 0; i < num_samples; i++) {
        samples[i] *= _settings->InputVolume / 100.0f;
    }

    std::vector<U8> compresed;

    compress_memory(stream, len, compresed);

    std::vector<U8> uncompressed;

    uncompress_memory(compresed, uncompressed);

    SDL_AudioStreamPut(_audioStream, uncompressed.data(), uncompressed.size());

    if (_audioRecordedCallback != nullptr) {
        //_audioRecordedCallback(stream, len);
    }
}

void AudioManager::OnAudioReceived(U8 *stream, int len) {
    if (!_isPlaying) {
        return;
    }
    SDL_AudioStreamPut(_audioStream, stream, len);
}

void AudioManager::AudioPlaybackCallback(void *userdata, U8 *stream, int len) {

    const int convertedBytes = SDL_AudioStreamGet(_audioStream, stream, len);

    if (convertedBytes > 0) {

        const int num_samples = convertedBytes / sizeof(S16);
        S16* samples = (S16*)stream;
        for (int i = 0; i < num_samples; i++) {
            samples[i] *= _settings->OutputVolume / 100.0f;
        }

    }

    len -= convertedBytes;
    stream += convertedBytes;
    if (len > 0) {
        SDL_memset(stream, '\0', len); // fill the rest of the stream with silence
    }
}

std::string &AudioManager::GetOutputDeviceName() {
    return _settings->OutputDevice;
}

std::string &AudioManager::GetInputDeviceName() {
    return _settings->InputDevice;
}

#endif