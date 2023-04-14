#define USE_SSS_GL

#include "ImGuiH.hpp"

#ifdef USE_SSS_GL
# include "SSS/GL.hpp"
#else
# include "opengl.cpp"
#endif

int main(void) try
{
#ifdef USE_SSS_GL

    // Create window
    SSS::GL::Window::CreateArgs args;
    args.w = 1280;
    args.h = 720;
    SSS::GL::Window::Shared window = SSS::GL::Window::create(args);

    // -------->>>  Setup ImGUI  context <<<--------
    SSS::ImGuiH::setContext(window->getGLFWwindow());

    // Main loop
    while (!window->shouldClose()) {

        // Poll events & set context
        SSS::GL::pollEverything();
        SSS::GL::Context const context(window);

        // -------->>>  Display ImGUI  <<<--------
        if (SSS::ImGuiH::newFrame()) {
            ImGui::ShowDemoWindow();
            SSS::ImGuiH::render();
        }

        // Print frame
        window->printFrame();
    };

#else

    // Create window
    WindowPtr window = load_opengl();
    SSS::ImGuiH::setContext(window.get());

    glfwMakeContextCurrent(window.get());

    while (!glfwWindowShouldClose(window.get())) {

        // Poll events
        glfwPollEvents();
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // -------->>>  Display ImGUI  <<<--------
        if (SSS::ImGuiH::newFrame()) {
            ImGui::ShowDemoWindow();
            SSS::ImGuiH::render();
        }

        glfwSwapBuffers(window.get());
    }

    glfwTerminate();

#endif
}
CATCH_AND_LOG_FUNC_EXC;