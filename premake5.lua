workspace "Avalon"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Avalon"
    location "Avalon"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "avpch.h"
    pchsource "Avalon/src/avpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    links
    {
        
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "AV_PLATFORM_WINDOWS",
            "AV_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/App")
        }

    filter "configurations:Debug"
        defines "AV_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AV_RELEASE"
        optimize "On"

    filter "configurations:Distribution"
        defines "AV_DISTRIBUTION"
        optimize "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

project "App"
    location "App"
    kind "ConsoleApp"
    language "C++"

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
        "Avalon/src"
    }

    links
    {
        "Avalon"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "AV_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AV_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AV_RELEASE"
        optimize "On"

    filter "configurations:Distribution"
        defines "AV_DISTRIBUTION"
        optimize "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"