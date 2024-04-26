/**
 * @file lyphc.h
 * @author flexhaufen
 * @brief Precompiled header
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
// ** External Files **
#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING       // Disable C4996 warning inn xutility

#pragma warning(push, 0)  // Disable all warnings
#include <algorithm>
#include <array>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define NOMINMAX        // Else std::min / max do not work
#include <Windows.h>


// GLFW
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// Vulkan
#include <vulkan/vulkan.hpp>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

// ImGui
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imconfig.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

// EnTT
#include "entt.hpp"

// Stb image
#include <stb_image.h>

// * yaml-cpp *
#include <yaml-cpp/yaml.h>

#pragma warning(pop)  // Restore previous warning settings

// ** Local Files **
#include "Lychee/Core/Log.h"
#include "Lychee/Core/Debug/Instrumentor.h"
#include "Lychee/Helper/Types.h"


// *** DEFINES ***
// ** Debug **

#ifndef NLY_DEBUG
    #define LY_DEBUG
#else
    #undef LY_DEBUG
#endif


#ifdef LY_DEBUG
    #define LY_RENDER_IMGUI 		
    #define LY_IMGUI_SHOW_DEMO      // Demo window    
    #define LY_IMPLOT_SHOW_DEMO     // Demo window
    //#define LY_LOG_EVENTS
    #define LY_DEBUGBREAK() __debugbreak()
	#define LY_ENABLE_ASSERTS
#else
	#define LY_RENDER_IMGUI 		//! dont change this
    #define LY_DEBUGBREAK()
#endif

// ** Macros **
#define LY_EXPAND_MACRO(x) x
#define LY_STRINGIFY_MACRO(x) #x


// ** Config **
// * General *
#define LY_SHOW_WINDOWTITLE_FPS     // FPS counter on window title

#define LY_PROJECT_NAME             "Lychee"
#define LY_VERSION_STR              "v2.1.0a"

#define LY_IMGUI_INSTALL_CALLBACKS  true

// * Rescources *
#define LY_DEFAULT_PATH             "./"
#define LY_ICON_PNG                 "./resource/images/Lychee.png"
#define LY_FONT_SIZE                15.0f
#define LY_FONT_REGULAR             "./resource/fonts/Rilu-Regular.ttf"

// * Colors *
// TODO (flex): convert
#define LY_COLOR_RED                ImVec4(249 / 255.f, 65 / 255.f, 68 / 255.f, 255)     // #F94144
#define LY_COLOR_ORANGE             ImVec4(243 / 255.f, 114 / 255.f, 44 / 255.f, 255)    // #F3722C
#define LY_COLOR_LIGHT_ORANGE       ImVec4(248 / 255.f, 150 / 255.f, 30 / 255.f, 255)    // #F8961E
#define LY_COLOR_YELLOW             ImVec4(249 / 255.f, 199 / 255.f, 79 / 255.f, 255)    // #F9C74F   
#define LY_COLOR_LIME               ImVec4(144 / 255.f, 190 / 255.f, 109 / 255.f, 255)   // #90BE6D
#define LY_COLOR_LIGHT_BLUE         ImVec4(67 / 255.f, 170 / 255.f, 139 / 255.f, 255)    // #43AA8B
#define LY_COLOR_BLUE               ImVec4(87 / 255.f, 117 / 255.f, 144 / 255.f, 255)    // #577590
#define LY_COLOR_WHITE              ImVec4(0 / 255.f,0 / 255.f,0 / 255.f,255)
#define LY_COLOR_BLACK              ImVec4(255 / 255.f,255 / 255.f,255 / 255.f,255)
#define LY_COLOR_GRAY               ImVec4(49 / 255.f, 57 / 255.f, 60 / 255.f, 255)      // #31393C

#define LY_WINDOW_SIZE_X            1920
#define LY_WINDOW_SIZE_Y            1080

#define LY_WINDOW_NAME_DEBUG        "Lychee - DEBUG"
#define LY_WINDOW_NAME              "Lychee"
#define LY_VSYNC_DEFAULT            true
