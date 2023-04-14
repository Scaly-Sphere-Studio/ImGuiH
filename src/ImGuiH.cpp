#include "ImGuiH.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

SSS_IMGUIH_BEGIN;

class Handle {
private:
    Handle();
public:
    ~Handle();
    using Ptr = std::unique_ptr<Handle>;
    static Ptr const& get();

private:
    GLFWwindow* _context{ nullptr };
    bool _has_frame{ false };

public:
    void setContext(GLFWwindow* context, const char* glsl_version);
    void newFrame();
    void render();
    ImGui::FileBrowser filebrowser;
};

Handle::Handle() try
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
CATCH_AND_RETHROW_METHOD_EXC;

Handle::~Handle()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

Handle::Ptr const& Handle::get()
{
    static Ptr const singleton(new Handle());
    return singleton;
}

void Handle::setContext(GLFWwindow* context, const char* glsl_version)
{
    if (context == nullptr) {
        SSS::throw_exc("Please forward a non-null OpenGL context.");
    }
    if (context == _context) return;
    
    GLFWwindow* previous = glfwGetCurrentContext();
    glfwMakeContextCurrent(context);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SSS::throw_exc("Failed to initialize GLAD");
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplGlfw_InitForOpenGL(context, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    _context = context;
    glfwMakeContextCurrent(previous);
}

void Handle::newFrame()
{
    if (_context == nullptr) {
        LOG_WRN("SSS/ImGuiH: Please set OpenGL context with setContext() before calling newFrame().");
        return;
    }
    if (_has_frame) {
        LOG_WRN("SSS/ImGuiH: A frame is already open.");
        return;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    _has_frame = true;
}

void Handle::render()
{
    Ptr const& handle = get();

    if (!handle->_has_frame) {
        LOG_WRN("SSS/ImGuiH: Tried to render when no frame was open.");
        return;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    handle->_has_frame = false;
}

void setContext(GLFWwindow* context, const char* glsl_version) try
{
    Handle::get()->setContext(context, glsl_version);
}
CATCH_AND_LOG_FUNC_EXC;

bool newFrame()
{
    try {
        Handle::get()->newFrame();
        return true;
    }
    catch (std::exception const& e) {
        LOG_FUNC_ERR(e.what());
        return false;
    }
}

void render() try
{
    Handle::get()->render();
}
CATCH_AND_LOG_FUNC_EXC;

ImGui::FileBrowser& getFilebrowser()
{
    return Handle::get()->filebrowser;
}

SSS_IMGUIH_END;