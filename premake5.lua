workspace "Avalon"
    architecture "x64"
    startproject "App"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Avalon/vendor/glfw/include"
IncludeDir["GLAD"] = "Avalon/vendor/glad/include"
IncludeDir["ImGui"] = "Avalon/vendor/imgui"
IncludeDir["glm"] = "Avalon/vendor/glm"
IncludeDir["stb_image"] = "Avalon/vendor/stb_image"


group "Dependencies"
    include "Avalon/vendor/glfw"
    include "Avalon/vendor/glad"
    include "Avalon/vendor/imgui"
group ""

project "Avalon"
    location "Avalon"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "avpch.h"
    pchsource "Avalon/src/avpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "AV_PLATFORM_WINDOWS",
            "AV_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
        }

    filter "configurations:Debug"
        defines "AV_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AV_RELEASE"
        optimize "on"
        runtime "Release"
        symbols "on"

    filter "configurations:Distribution"
        defines "AV_DISTRIBUTION"
        runtime "Release"
        optimize "on"
        symbols "off"

project "App"
    location "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Avalon/vendor/spdlog/include",
        "Avalon/src",
        "Avalon/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Avalon"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "AV_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AV_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AV_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Distribution"
        defines "AV_DISTRIBUTION"
        runtime "Release"
        optimize "on"