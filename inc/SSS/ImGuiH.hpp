#pragma once

#include <SSS/Commons.hpp>
#include <imgui.h>
#include "ImGuiH/imfilebrowser.h"

/** @file
 *  Header of the
 *  [SSS/ImGuiH](https://github.com/Scaly-Sphere-Studio/ImGuiH) library.
 */

/** @namespace SSS::ImGuiH
 *  A simple handle to \b ImGui integration & extension(s).
 */

/** Declares the SSS::ImGuiH namespace.
 *  Further code will be nested in the SSS::ImGuiH namespace.\n
 *  Should be used in pair with with #SSS_IMGUIH_END.
 */
#define SSS_IMGUIH_BEGIN SSS_BEGIN; namespace ImGuiH {
/** Closes the SSS::ImGuiH namespace declaration.
 *  Further code will no longer be nested in the SSS::ImGuiH namespace.\n
 *  Should be used in pair with with #SSS_IMGUIH_BEGIN.
 */
#define SSS_IMGUIH_END SSS_END; }

struct GLFWwindow; // pre-declaration

SSS_IMGUIH_BEGIN;

/** Creates an \b ImGui context and inits the #filebrowser variable.
 *  \a ImGui's .ini file option is disabled.\n
 *  The #filebrowser's pwd is set to SSS::PWD.
 *  @usage
 *  Should be called after \b OpenGL initialisation, and followed
 *  by setContext().\n
 *  Must be used in pair with shutdown().
 */
void init();

/** Links \b ImGui to a specific \b OpenGL context for future draw calls.
 *  @param[in] context The \a OpenGL context to be linked to.
 *  @param[in] glsl_version  The \a GLSL shader version to be used.
 *  @usage
 *  Should be called after init(), and anytime the user wants
 *  to change the \b OpenGL target.
 */
void setContext(GLFWwindow* context, const char* glsl_version = "#version 330");

/** Starts a new \b ImGui frame.
 *  Future \b ImGui operations will be drawn in a clean buffer that's
 *  available until the next render() call.
 *  @usage
 *  Should be called before any \b ImGui draw operation, and after
 *  a context has been set with setContext().\n
 *  Must be used in pair with render().
 */
void newFrame();

/** Ends the \b ImGui frame and renders it to the linked \b OpenGL context.
 *  @usage
 *  Should be called after \b ImGui draw operations have been completed.\n
 *  Must be used in pair with newFrame().
 */
void render();

/** Destroys the \b ImGui context and cleans up everything.
 *  @usage
 *  Should be called before any program exit, or when \b ImGui
 *  is no longer needed.\n
 *  Must be used in pair with init().
 */
void shutdown();

/** A pre-set instance of \b ImGui's file browser
 *  [extension](https://github.com/AirGuanZ/imgui-filebrowser).
 *  This instance is created in the init() function.
 */
extern ImGui::FileBrowser filebrowser;

SSS_IMGUIH_END;