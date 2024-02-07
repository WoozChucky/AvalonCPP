#pragma once

#include <Common/Types.h>
#include <Common/Logging/Log.h>
#include <opus.h>
#include <vector>


class AudioEncoder
{
public:
    AudioEncoder() = default;
    ~AudioEncoder() {
        if (_encoder != nullptr) {
            opus_encoder_destroy(_encoder);
        }
        if (_inputBuffer != nullptr) {
            delete[] _inputBuffer;
            _inputBuffer = nullptr;
        }
        if (_outputBuffer != nullptr) {
            delete[] _outputBuffer;
            _outputBuffer = nullptr;
        }
    };

    bool Initialize(S32 sampleRate, U16 channels, S32 frameSize) {
        _sampleRate = sampleRate;
        _channels = channels;
        _frameSize = frameSize;

        if (_encoder != nullptr) {
            opus_encoder_destroy(_encoder);
        }

        _encoder = opus_encoder_create(_sampleRate, _channels, OPUS_APPLICATION_VOIP, nullptr);
        if (_encoder == nullptr) {
            LOG_ERROR("audio", "Failed to create Opus encoder");
            return false;
        }

        opus_encoder_ctl(_encoder, OPUS_SET_BITRATE(kBitrate));
        opus_encoder_ctl(_encoder, OPUS_SET_FORCE_CHANNELS(2));
        opus_encoder_ctl(_encoder, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE)); // Optimize for voice signals
        opus_encoder_ctl(_encoder, OPUS_SET_BANDWIDTH(OPUS_AUTO)); // Automatically select the bandwidth
        opus_encoder_ctl(_encoder, OPUS_SET_COMPLEXITY(10)); // Adjust complexity as needed
        opus_encoder_ctl(_encoder, OPUS_SET_INBAND_FEC(0)); // Disable in-band Forward Error Correction (FEC)
        opus_encoder_ctl(_encoder, OPUS_SET_PACKET_LOSS_PERC(0)); // Set packet loss percentage (if applicable)

        return true;
    }

    bool Encode(U8* pcmData, size_t pcmLength, U8* encodedData, size_t& encodedLength) {
        if (_encoder == nullptr) {
            LOG_ERROR("audio", "Opus encoder is not initialized");
            return false;
        }

        if (_inputBuffer == nullptr) {
            _inputBuffer = new opus_int16[_channels * _frameSize];
        }

        for (int i = 0; i < (_channels * _frameSize); i++)
            _inputBuffer[i] = pcmData[i];

        if (_outputBuffer == nullptr) {
            _outputBuffer = new U8[kMaxOutputSize];
        }

        int encodedSize = opus_encode(_encoder, _inputBuffer, _frameSize, _outputBuffer, kMaxOutputSize);
        if (encodedSize <= 0) {
            LOG_ERROR("audio", "Failed to encode audio: {}", opus_strerror(encodedSize));
            delete[] _inputBuffer;
            _inputBuffer = nullptr;
            delete[] _outputBuffer;
            _outputBuffer = nullptr;
            return false;
        }

        encodedLength = encodedSize;
        memcpy(encodedData, _outputBuffer, encodedSize);

        delete[] _inputBuffer;
        _inputBuffer = nullptr;
        delete[] _outputBuffer;
        _outputBuffer = nullptr;

        return true;
    }

private:

    static constexpr U32 kBitrate = 32000;
    static constexpr U32 kMaxOutputSize = 16384;

    OpusEncoder* _encoder = nullptr;
    opus_int16* _inputBuffer;
    U8* _outputBuffer;

    S32 _sampleRate;
    S32 _frameSize;
    U16 _channels;

};
