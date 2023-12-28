workspace "StoreGame"
	architecture "x64"
	startproject "StoreGame"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Engine/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%(prj.name)/vendor/spdlog/**.h",
		--"%{prj.name}/vendor/glm/glm/**.hpp",
		--"%{prj.name}/vendor/glm/glm/**.inl"
	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
		
	}

	links 
	{ 
		--"GLFW",
		--"Glad",
		--"ImGui",
		--"opengl32.lib"
	}

	filter "system:windows"
		--cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		--postbuildcommands{("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "on"

project "StoreGame"
	location "StoreGame"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"Engine/vendor/spdlog/include",
		"Engine/src",
		"Engine/vendor"
		--"%{IncludeDir.glm}"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		--staticruntime "on"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "on"