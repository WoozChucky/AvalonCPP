#pragma once

#include <Common/Types.h>
#include <Common/Logging/Log.h>
#include <opus.h>
#include <vector>

class AudioDecoder
{
public:
    AudioDecoder() = default;
    ~AudioDecoder() {
        if (_decoder != nullptr) {
            opus_decoder_destroy(_decoder);
        }
    }

    bool Initialize(S32 sampleRate, U16 channels, S32 frameSize) {
        _sampleRate = sampleRate;
        _frameSize = frameSize;
        _channels = channels;

        if (_decoder != nullptr) {
            opus_decoder_destroy(_decoder);
        }

        _decoder = opus_decoder_create(_sampleRate, _channels, nullptr);
        if (_decoder == nullptr) {
            LOG_ERROR("audio", "Failed to create Opus decoder");
            return false;
        }

        return true;
    }

    bool Decode(U8* encodedData, size_t encodedLength, U8* pcmData, size_t &pcmLength) {

        if (_decoder == nullptr) {
            LOG_ERROR("audio", "Opus decoder is not initialized");
            return false;
        }

        int decodedSize = opus_decode(_decoder, encodedData, (opus_int32)encodedLength, out, (_channels * _frameSize), 0);
        if (decodedSize <= 0)
        {
            LOG_ERROR("audio", "Failed to decode audio: {}", opus_strerror(decodedSize));
            return false;
        }

        pcmLength = (_frameSize);
        memcpy(pcmData, out, pcmLength);

        // Clear the output buffers
        memset(out, 0, sizeof(out));
        memset(outUint8, 0, sizeof(outUint8));

        return true;

    }

private:
    OpusDecoder* _decoder = nullptr;
    S32 _sampleRate;
    S32 _frameSize;
    U16 _channels;

    opus_int16 out[(920)];
    // times 2, because uint8_t is just 1 Byte and uint16_t is two, so the actual framesize in bytes is 2 * OPUS_FRAMESIZE
    uint8_t outUint8[(2 * 1 * 920)];
};
