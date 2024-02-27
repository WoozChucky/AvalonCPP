#pragma once

#include <Common/Types.h>
#include <Common/Utilities/Optional.h>
#include <SDL_video.h>

#define DEFAULT_GAME_SETTINGS_PATH "settings.json"

namespace Avalon::Engine {

    namespace Internal {
        constexpr U32 DEFAULT_VIDEO_WIDTH = 1920;
        constexpr U32 DEFAULT_VIDEO_HEIGHT = 1080;
        constexpr bool DEFAULT_VIDEO_MODE = false;
        constexpr bool DEFAULT_VIDEO_VSYNC = false;
        constexpr U32 DEFAULT_VIDEO_TARGET_FRAMES_PER_SECOND = 60;
        constexpr U32 DEFAULT_AUDIO_INPUT_VOLUME = 100;
        constexpr U32 DEFAULT_AUDIO_OUTPUT_VOLUME = 100;
    }

    using namespace Internal;

    enum ResolutionOption {
        RESOLUTION_1280x720 = 0,
        RESOLUTION_1920x1080 = 1,
        RESOLUTION_2560x1440 = 2
    };

    enum FPSOption {
        FPS_30 = 30,
        FPS_60 = 60,
        FPS_120 = 120,
        FPS_144 = 144,
        FPS_240 = 240,
        FPS_360 = 360
    };

    enum VideoMode : U32 {
        Windowed = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL,
        Borderless = SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL,
        Fullscreen = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL,
        FullscreenBorderless = SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL
    };

    struct VideoResolution {
        U32 Width;
        U32 Height;

        ResolutionOption GetResolutionOption() const {
            if (Width == 1280 && Height == 720) {
                return RESOLUTION_1280x720;
            } else if (Width == 1920 && Height == 1080) {
                return RESOLUTION_1920x1080;
            } else if (Width == 2560 && Height == 1440) {
                return RESOLUTION_2560x1440;
            }
            return RESOLUTION_1920x1080;
        }
    };

    struct VideoSettings {
        VideoResolution Resolution;
        VideoMode Mode;
        bool VSync;
        int TargetFramesPerSecond;

        ResolutionOption GetResolutionOption() const {
            return Resolution.GetResolutionOption();
        }

        FPSOption GetFPSOption() const {
            switch (TargetFramesPerSecond) {
                case 30: return FPS_30;
                default:
                case 60: return FPS_60;
                case 120: return FPS_120;
                case 144: return FPS_144;
                case 240: return FPS_240;
                case 360: return FPS_360;
            }
        }
    };

    struct AudioSettings {
        std::string InputDevice;
        int InputVolume;
        std::string OutputDevice;
        int OutputVolume;
    };

    struct GameSettings {
        VideoSettings Video;
        AudioSettings Audio;
    };

    static GameSettings DefaultGameSettings = {
            { // VideoSettings
                    { DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT },
                    VideoMode::Windowed,
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

