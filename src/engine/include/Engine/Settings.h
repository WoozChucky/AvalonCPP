#pragma once

#include <Common/Types.h>
#include <Common/Utilities/Optional.h>

#define DEFAULT_GAME_SETTINGS_PATH "settings.json"

namespace Avalon::Engine {

    namespace Internal {
        constexpr U32 AUDIO_DEVICE_NAME_MAX_LENGTH = 126;
        constexpr U32 DEFAULT_VIDEO_WIDTH = 1920;
        constexpr U32 DEFAULT_VIDEO_HEIGHT = 1080;
        constexpr bool DEFAULT_VIDEO_FULLSCREEN = false;
        constexpr bool DEFAULT_VIDEO_VSYNC = false;
        constexpr U32 DEFAULT_VIDEO_TARGET_FRAMES_PER_SECOND = 60;
        constexpr U32 DEFAULT_AUDIO_INPUT_VOLUME = 100;
        constexpr U32 DEFAULT_AUDIO_OUTPUT_VOLUME = 100;
    }

    using namespace Internal;

    struct VideoResolution {
        U32 Width;
        U32 Height;
    };

    struct VideoSettings {
        VideoResolution Resolution;
        bool Fullscreen;
        bool VSync;
        int TargetFramesPerSecond;
    };

    struct AudioSettings {
        std::string InputDevice;
        U32 InputVolume;
        std::string OutputDevice;
        U32 OutputVolume;
    };

    struct GameSettings {
        VideoSettings Video;
        AudioSettings Audio;
    };

    static GameSettings DefaultGameSettings = {
            { // VideoSettings
                    { DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT },
                           DEFAULT_VIDEO_FULLSCREEN,
                    DEFAULT_VIDEO_VSYNC,
                           DEFAULT_VIDEO_TARGET_FRAMES_PER_SECOND
            },
            { // AudioSettings
                    { "" }, DEFAULT_AUDIO_INPUT_VOLUME,
                    { "" }, DEFAULT_AUDIO_OUTPUT_VOLUME
            }
    };

    GameSettings LoadGameSettings(const std::string& path);
    bool SaveGameSettings(GameSettings& settings, const String& path);

}

