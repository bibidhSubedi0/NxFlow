-- Set workspace configuration
workspace "MLLibrary"
    configurations { "Debug", "Release" }
    language "C++"
    cppdialect "C++20"
    architecture "x64"
    startproject "App"  -- Default project to start


-- Include directories (both CoreLibrary, App, and Test)
includedirs {
    "CoreLibrary/include",
    "App/include",
    "Test/include",
    "Test/externals/googletest/googletest/include"
}

-- Static library project for CoreLibrary
project "CoreLibrary"
    kind "SharedLib"  -- Use SharedLib for DLL
    language "C++"
    location "CoreLibrary"
    files {
        "CoreLibrary/src/**.cpp",
        "CoreLibrary/include/**.h",
        "CoreLibrary/include/**.hpp"
    }
    -- Library specific settings
    includedirs {
        "CoreLibrary/include"
    }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"



-- Console application project for App
project "App"
    kind "ConsoleApp"
    language "C++"
    location "App"

    files {
        "App/src/**.cpp",
        "App/include/**.h",
        "App/include/**.hpp"
    }

    includedirs {
        "App/include",
        "CoreLibrary/include"
    }

    libdirs {
        "%{wks.location}/CoreLibrary/bin/%{cfg.buildcfg}"  -- Ensure correct CoreLibrary lib directory
    }

    links { "CoreLibrary" }

    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}")

    postbuildcommands {
        "{COPY} %{wks.location}/CoreLibrary/bin/%{cfg.buildcfg}/CoreLibrary.dll %{wks.location}/bin/%{cfg.buildcfg}"
    }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"


-- Testing project using Google Test for CoreLibrary
project "Test"
    kind "ConsoleApp"
    language "C++"
    location "Test"
    files {
        "Test/src/**.cpp"
    }
    -- Linking CoreLibrary and Google Test to Test
    links { "CoreLibrary", "gtest", "gtest_main" }
    includedirs {
        "CoreLibrary/include",
        "Test/include",
        "C:/Users/third/OneDrive/Documents/Projects/ML/packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.7/build/native/include"  -- Path to Google Test include
    }
    libdirs {
        "C:/Users/third/OneDrive/Documents/Projects/ML/packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.7/lib/native/v140/windesktop/msvcstl/static/rt-dyn/x64"  -- Path to Google Test library
    }
    links { "gtest", "gtest_main" }
    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"