#include "SSS/ImGuiH.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

__SSS_IMGUIH_BEGIN;

ImGui::FileBrowser filebrowser;

void init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;

    // Init filebrowser
    filebrowser = ImGui::FileBrowser();
    // Remove last '\' from PWD because for some reason
    // the file browser detects it as an empty directory
    std::string pwd = SSS::PWD;
    pwd.resize(pwd.size() - 1);
    filebrowser.SetPwd(pwd);
    filebrowser.SetTitle("Select a file");
}

void setContext(GLFWwindow* context, const char* glsl_version)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplGlfw_InitForOpenGL(context, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

__SSS_IMGUIH_END;