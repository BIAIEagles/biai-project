#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

#include <iostream>

#include "Dirent/dirent.h"
#include "ImGuiFileBrowser.h"

#include <opencv2/opencv.hpp>

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 700, "Self-organizing maps", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        static float compRate = 20.f;
        static float psnr = 25.f;
        static bool isActive = true;
        imgui_addons::ImGuiFileBrowser file_dialog;
        ImGui::Begin("Self-organizing maps", &isActive, ImGuiWindowFlags_MenuBar);
        bool open = false, save = false;
        if (ImGui::BeginMenu("Menu")) 
        {
            if (ImGui::MenuItem("Select image", NULL)) open = true;

            ImGui::EndMenu();
        }

        // Remember the name to ImGui::OpenPopup() and showFileDialog() must
        // be same...
        if (open) ImGui::OpenPopup("Select image");

        /* Optional third parameter. Support opening only compressed rar/zip
         * files. Opening any other file will show error, return false and
         * won't close the dialog.
         */
        if (file_dialog.showFileDialog(
                "Select image", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN,
                ImVec2(700, 310), ".jpg,.jpeg")) {
            std::cout
                << file_dialog.selected_fn
                << std::endl;  // The name of the selected file or directory
                               // in case of Select Directory dialog mode
            std::cout << file_dialog.selected_path
                      << std::endl;  // The absolute path to the selected file
        }
        ImGui::SliderFloat("Compression rate", &compRate, 1.f, 50.f);
        ImGui::SliderFloat("PSNR", &psnr, 1.f, 50.f);
        ImGui::End();
        ImGui::EndFrame();
        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}