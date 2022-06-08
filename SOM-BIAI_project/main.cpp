#define GL_CLAMP_TO_EDGE 0x812F
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include "Dirent/dirent.h"
#include "ImGuiFileDialog.h"

#include <opencv2/opencv.hpp>

#include "include/Image.h"
#include "include/SOMNetwork.h"
#include "include/SOMNetworkEncoder.h"
#include "include/SOMNetworkDecoder.h"
#include "include/Misc.h"

using namespace std;

bool LoadTextureFromFile(const char *filename, GLuint *out_texture, int *out_width, int *out_height);

int main(void) 
{
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
        ImGui::Begin("Self-organizing maps", &isActive, ImGuiWindowFlags_MenuBar);
        
        // open Dialog Simple
        if (ImGui::Button("Import image..."))
            ImGuiFileDialog::Instance()->OpenDialog(
                "ChooseFileDlgKey", "Choose File", ".jpg,.jpeg", ".");

        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePathName =
                    ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath =
                    ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
                int my_image_width = 0;
                int my_image_height = 0;
                GLuint my_image_texture = 0;
                bool ret = LoadTextureFromFile(filePathName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
                SOM::Image image(filePathName);
                image.transformBGR2YCbCr();
                image.transformImageToPixelArray();
                SOM::SOMNetwork network =
                    SOM::SOMNetwork(128,
                                    //image.getBGRImageHandle().cols *
                                    //    image.getBGRImageHandle().rows,
                                    100,
                                    100, 12);
                std::vector<SOM::Subframe> trainingSet =
                    generateRandomSubframes();
                for (int i = 0; i < 100; i++) {
                    for (auto frame : trainingSet) {
                        network.processFrame(frame);
                    }
                }
                network.purgeDeadNeurons();
                SOM::SOMNetworkEncoder encoder(network);
                std::vector<std::vector<SOM::Subframe>> framesList =
                    convertPixelArrayToSubframes(image.getPixelArray(),
                                                 image.getYCbCrImageHandle().cols, image.getYCbCrImageHandle().rows, 4, 4);
                std::vector<std::vector<SOM::SubframeCompressed>>
                    encodedFrames = encoder.encode(framesList);
                std::vector<SOM::SubframeCompressed> encodedFramesArrayFlattened;
                for (int i = 0; i < encodedFrames.size(); i++) {
                    for (int j = 0; j < encodedFrames[i].size(); j++) {
                        encodedFramesArrayFlattened.push_back(
                            encodedFrames[i][j]);
                    }
                }
                SOM::SOMNetworkDecoder decoder(
                    network, encodedFramesArrayFlattened, encodedFrames.size(),
                    encodedFrames[0].size());
                std::vector<SOM::Pixel> resultImagePixelArray =
                    decoder.decode();
                SOM::Image newImage;
                newImage.setPixelArray(resultImagePixelArray);
                newImage.transformPixelArrayToImage();
                newImage.transformYCbCr2BGR();
                newImage.saveToFile("testimage.jpg");
                if (ret)
                    ImGui::Image((void *)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
            }   
            // close
            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::SliderFloat("Compression rate", &compRate, 1.f, 50.f);
        ImGui::SliderFloat("PSNR", &psnr, 1.f, 50.f);
        ImGui::Button("Run SOM & compress the image");
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

// Simple helper function to load an image into a OpenGL texture with common
// settings
bool LoadTextureFromFile(const char *filename, GLuint *out_texture, int *out_width, int *out_height) 
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char *image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL) return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);  // This is required on WebGL for non
                                        // power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    GL_CLAMP_TO_EDGE);  // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}