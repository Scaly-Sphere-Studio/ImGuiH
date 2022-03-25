#pragma once

#include <SSS/Commons.hpp>
#include <imgui.h>
#include "ImGuiH/imfilebrowser.h"

/*! \file
 *  @brief The header of the
 *  [SSS/ImGuiH](https://github.com/Scaly-Sphere-Studio/ImGuiH) library.
 */

#define __SSS_IMGUIH_BEGIN __SSS_BEGIN namespace ImGuiH {
#define __SSS_IMGUIH_END __SSS_END }

/*! \namespace ImGuiH
 *  @brief This namespaces holds all of
 *  [SSS/ImGuiH](https://github.com/Scaly-Sphere-Studio/ImGuiH) library.
 * 
 *  It is nested inside the \c SSS namespace. Members of this namespace
 *  shall be accessed via the \c SSS::ImGuiH formula
 */

struct GLFWwindow; // pre-declaration

__SSS_IMGUIH_BEGIN;

/*! @brief Creates an \a ImGui context and inits the #filebrowser variable.
 *  
 *  \a ImGui's .ini file option is disabled.\n
 *  The #filebrowser's pwd is set to the executable's folder.
 * 
 *  @usage
 *  Should be called after \a OpenGL initialisation, and followed
 *  by #setContext.
 */
void init();

/*! @brief Links \a ImGui to a specific \a OpenGL context.
 *
 *  @param[in] context The \a OpenGL context to be linked to.
 *  @param[in] glsl_version  The \a GLSL shader version.
 * 
 *  @usage
 *  Should be called after #init, and anytime further if the user
 *  decides to change the \a OpenGL target.
 */
void setContext(GLFWwindow* context, const char* glsl_version = "#version 330");

/*! @brief Starts a new \a ImGui frame.
 *
 *  \a ImGui will draw future operations in a clean buffer that's
 *  available until the next #render call.
 * 
 *  @usage
 *  Should be called before any \a ImGui draw operation.
 */
void newFrame();

/*! @brief Ends the \a ImGui frame and renders it to the linked \a OpenGL
 *  context.
 *
 *  @usage
 *  Should be called after \a ImGui draw operations have been completed.
 */
void render();

/*! @brief Destroys the \a ImGui context and cleans up everything.
 *
 *  @usage
 *  Should be called before any program exit, or when \a ImGui is no longer needed.
 */
void shutdown();

/*! @brief A pre-set instance of \a ImGui's file browser
 *  [extension](https://github.com/AirGuanZ/imgui-filebrowser).
 * 
 *  This instance is created in the #init function.
 */
extern ImGui::FileBrowser filebrowser;

__SSS_IMGUIH_END;