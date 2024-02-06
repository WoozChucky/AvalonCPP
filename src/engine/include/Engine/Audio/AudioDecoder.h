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

    bool Decode(std::vector<U8>* encodedData, std::vector<U8>* pcmData) {

        if (_decoder == nullptr) {
            LOG_ERROR("audio", "Opus decoder is not initialized");
            return false;
        }

        int decodedSize = opus_decode(_decoder, &encodedData->at(0), (opus_int32)encodedData->size(), out, (_channels * _frameSize), 0);
        if (decodedSize <= 0)
        {
            LOG_ERROR("audio", "Failed to decode audio: {}", opus_strerror(decodedSize));
            return false;
        }

        // transform opusint16 to uint8_t
        for (int i = 0; i < _channels * _frameSize; i++)
        {
            outUint8[i] = out[i];
        }


        pcmData->resize(_channels * 2 * _frameSize);
        // times 2, because uint8_t is just 1 Byte and uint16_t is two, so the actual framesize in bytes is 2 * OPUS_FRAMESIZE
        pcmData->insert(pcmData->begin(), outUint8, outUint8 + (_channels * 2 * _frameSize));

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
