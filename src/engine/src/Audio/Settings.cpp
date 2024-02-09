#include <Engine/Settings.h>
#include <Common/Utilities/JsonUtils.h>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
using namespace Avalon::Engine;

namespace Avalon::Engine {

    void from_json(const json& j, Avalon::Engine::VideoResolution& res)
    {
        j.at("Width").get_to(res.Width);
        j.at("Height").get_to(res.Height);
    }
    void to_json(json& j, const Avalon::Engine::VideoResolution& res)
    {
        j = json{{"Width", res.Width}, {"Height", res.Height}};
    }

    void from_json(const json& j, Avalon::Engine::VideoSettings& res)
    {
        j.at("Resolution").get_to(res.Resolution);
        j.at("Mode").get_to(res.Mode);
        j.at("VSync").get_to(res.VSync);
        j.at("TargetFramesPerSecond").get_to(res.TargetFramesPerSecond);
    }
    void to_json(json& j, const Avalon::Engine::VideoSettings& res)
    {
        j = json{{"Resolution", res.Resolution}, {"Mode", res.Mode}, {"VSync", res.VSync}, {"TargetFramesPerSecond", res.TargetFramesPerSecond}};
    }

    void from_json(const json& j, Avalon::Engine::AudioSettings& res)
    {
        j.at("InputDevice").get_to(res.InputDevice);
        j.at("InputVolume").get_to(res.InputVolume);
        j.at("OutputDevice").get_to(res.OutputDevice);
        j.at("OutputVolume").get_to(res.OutputVolume);
    }
    void to_json(json& j, const Avalon::Engine::AudioSettings& res)
    {
        j = json{{"InputDevice", res.InputDevice}, {"InputVolume", res.InputVolume}, {"OutputDevice", res.OutputDevice}, {"OutputVolume", res.OutputVolume}};
    }

    void from_json(const json& j, Avalon::Engine::GameSettings& res)
    {
        j.at("Video").get_to(res.Video);
        j.at("Audio").get_to(res.Audio);
    }
    void to_json(json& j, const Avalon::Engine::GameSettings& res)
    {
        j = json{{"Video", res.Video}, {"Audio", res.Audio}};
    }



    Optional<GameSettings> LoadGameSettingsFile(const String& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            return {};
        }

        auto content = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        auto settings = Utilities::Json::Deserialize<GameSettings>(content);

        content.clear();
        file.close();

        return settings;
    }

    GameSettings Avalon::Engine::LoadGameSettings(const std::string& path)
    {
        return LoadGameSettingsFile(path).value_or(DefaultGameSettings);
    }

    bool Avalon::Engine::SaveGameSettings(GameSettings& settings, const String& path)
    {
        std::ofstream file(path);
        if (!file.is_open())
        {
            return false;
        }

        auto serialized = Utilities::Json::Serialize(settings);

        file.write(serialized.c_str(), (S32)serialized.size());
        file.close();

        return true;
    }

}


