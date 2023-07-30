workspace "CEngine"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution diretory)
IncludeDir = {}
IncludeDir["GLFW"] = "CEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "CEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "CEngine/vendor/imgui"
IncludeDir["glm"] = "CEngine/vendor/glm"

include "CEngine/vendor/GLFW"
include "Cengine/vendor/Glad"
include "Cengine/vendor/imgui"

project "CEngine"
	location "CEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ccpch.h"
	pchsource "CEngine/src/ccpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++latest"
		systemversion "latest"

		defines
		{
			"CC_PLATFORM_WINDOWS",
			"CC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "CC_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CC_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CC_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"CEngine/vendor/spdlog/include",
		"CEngine/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"CEngine"
	}

	filter "system:windows"
		cppdialect "C++latest"
		systemversion "latest"

		defines
		{
			"CC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CC_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CC_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "CC_DIST"
		runtime "Release"
		symbols "On"