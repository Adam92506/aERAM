workspace "Eram"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Eram"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "Eram/vendor/glfw/include"
IncludeDir["glad"] = "Eram/vendor/glad/include"
IncludeDir["glm"] = "Eram/vendor/glm"
IncludeDir["stb_image"] = "Eram/vendor/stb_image"
IncludeDir["ImGui"] = "Eram/vendor/ImGui/"
IncludeDir["yamlCpp"] = "Eram/vendor/yamlCpp/include"

include "Eram/vendor/glfw"
include "Eram/vendor/glad"
include "Eram/vendor/ImGui"
include "Eram/vendor/yamlCpp"

project "Eram"
	location "Eram"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "erpch.h"
	pchsource "Eram/src/erpch.cpp"

	debugdir "%{wks.location}"

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
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.stb_image}/src",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.yamlCpp}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib",
		"ImGui",
		"yamlCpp"
	}

	filter "system:windows"
		systemversion "latest"
		defines 
		{
			"ER_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS",
			"YAML_CPP_STATIC_DEFINE"
		}

	filter "configurations:Debug"
		defines
		{
			"ER_DEBUG",
			"ER_ENABLE_ASSERTS",
			"ER_LOG_LEVEL_TRACE"
		}
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"ER_RELEASE",
			"ER_LOG_LEVEL_WARN"
		}
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines
		{
			"ER_DIST",
			"ER_LOG_LEVEL_INFO"
		}
		runtime "Release"
		optimize "on"