#include "SSS/ImGuiH.hpp"
#include <SSS/GL.hpp>

int main(void) try
{
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
}
CATCH_AND_LOG_FUNC_EXC;