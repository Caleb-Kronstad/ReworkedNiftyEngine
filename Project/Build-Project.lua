project "Project"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "on"

    files { 
        "Source/**.h", 
        "Source/**.hpp", 
        "Source/**.cpp",
        
        "Assets/**.vert",
        "Assets/**.frag",
        "Assets/**.geom",

        "Assets/**.obj",
        "Assets/**.mtl",
        "Assets/**.blend",
        "Assets/**.blend1",
        "Assets/**.png",
        "Assets/**.jpg",
        "Assets/**.ttf"
    }

    includedirs {
        "Source",
        "Assets",

        -- Include Core
        "../Engine/Source"
    }

    links {
        "Engine"
    }

    targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("../bin-int/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        
        defines { 
            "NF_PLATFORM_WINDOWS",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "on"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "off"