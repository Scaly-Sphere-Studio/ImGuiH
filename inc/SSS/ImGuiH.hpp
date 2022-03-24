#pragma once

#include <SSS/Commons.hpp>
#include <imgui.h>
#include "ImGuiH/imfilebrowser.h"

#define __SSS_IMGUIH_BEGIN __SSS_BEGIN namespace ImGuiH {
#define __SSS_IMGUIH_END __SSS_END }

struct GLFWwindow;

__SSS_IMGUIH_BEGIN

void init();
void setContext(GLFWwindow* context, const char* glsl_version = "#version 330");
void newFrame();
void render();
void shutdown();

extern ImGui::FileBrowser FileBrowser;

__SSS_IMGUIH_END