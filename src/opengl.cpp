#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <SSS/Commons.hpp>

using WindowPtr = SSS::C_Ptr<GLFWwindow, void(*)(GLFWwindow*), glfwDestroyWindow>;

inline WindowPtr load_opengl() try
{
    using namespace SSS;
    constexpr int w = 1280, h = 720;

    // Create Window
    glfwInit();
    WindowPtr window(glfwCreateWindow(w, h, "SSS/ImGuiH - Demo Window", nullptr, nullptr));
    // Throw if an error occured
    if (!window) {
        const char* msg;
        glfwGetError(&msg);
        SSS::throw_exc(msg);
    }

    // Set context
    glfwMakeContextCurrent(window.get());

    // Init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SSS::throw_exc("Failed to initialize GLAD");
    }

    // Finish setting up window
    glViewport(0, 0, w, h);
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwMakeContextCurrent(nullptr);

    return window;
}
CATCH_AND_RETHROW_FUNC_EXC;