workspace "NiftyEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Project"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

IncludeDir = {}
IncludeDir["GLAD"] = os.realpath("Engine/Vendor/glad/include")
IncludeDir["GLFW"] = os.realpath("Engine/Vendor/glfw/include")
IncludeDir["IMGUI"] = os.realpath("Engine/Vendor/imgui")
IncludeDir["STB_IMAGE"] = os.realpath("Engine/Vendor/stb_image")
IncludeDir["ASSIMP"] = os.realpath("Engine/Vendor/assimp/include")
IncludeDir["GLM"] = os.realpath("Engine/Vendor/glm/glm")
IncludeDir["IMGUIZMO"] = os.realpath("Engine/Vendor/imguizmo")

group "Other"
   include "Engine/Vendor/glad/Build-GLAD.lua"
   include "Engine/Vendor/glfw/Build-GLFW.lua"
   include "Engine/Vendor/imgui/Build-IMGUI.lua"
   include "Engine/Vendor/assimp/Build-ASSIMP.lua"
   include "Engine/Vendor/glm/Build-GLM.lua"
   include "Engine/Vendor/imguizmo/Build-IMGUIZMO.lua"
group ""

include "Engine/Build-Engine.lua"

include "Project/Build-Project.lua"