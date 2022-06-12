#define GL_CLAMP_TO_EDGE 0x812F
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>

#include "Dirent/dirent.h"
#include "ImGuiFileDialog.h"

#include <opencv2/opencv.hpp>

#include "include/Image.h"
#include "include/SOMNetwork.h"
#include "include/SOMNetworkEncoder.h"
#include "include/SOMNetworkDecoder.h"
#include "include/Misc.h"
#include "include/Neuron.h"
//#include "Spinner.h"

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

    char selectedFile[] = "Selected file: ";
    std::string filePathName;
    const char *str = " ";
    SOM::Image image;

    bool trainingCheckbox = true;
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

        ImGui::Checkbox("Train network", &trainingCheckbox);

        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk()) {
                filePathName =
                    ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath =
                    ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
                image.readImageFromFileName(filePathName);
                int my_image_width = 0;
                int my_image_height = 0;
                GLuint my_image_texture = 0;
                //bool ret = LoadTextureFromFile(filePathName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
                memset(&str, 0, sizeof str);
                str = strcat(selectedFile, filePathName.c_str());
            }   
            // close
            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::Text(str);

        if (ImGui::Button("Run SOM & compress the image")) 
        {
            //ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
            image.transformImageToPixelArray();

            SOM::SOMNetwork network =
                SOM::SOMNetwork(image.getBGRImageHandle().cols *
                                    image.getBGRImageHandle().rows / (8 * 8),
                                8 * 8,
                                // 100,
                                0.01, 10, image.getPixelArray());

            std::vector<SOM::Subframe> trainingSet;
            std::vector<SOM::Subframe> resultTrSetTemp;
            std::vector<std::vector<SOM::Subframe>> framesList =
                convertPixelArrayToSubframes(
                    image.getPixelArray(), image.getYCbCrImageHandle().cols,
                    image.getYCbCrImageHandle().rows, 8, 8);
            bool training = trainingCheckbox;

            if (training) {

                for (int i = 0; i < framesList.size(); i++) {
                    for (int j = 0; j < framesList[i].size(); j++) {
                        trainingSet.push_back(framesList[i][j]);
                    }
                }

                /* std::vector<SOM::Subframe> randomSubframes =
                    generateRandomSubframes();

                for (auto frame : randomSubframes) {
                    trainingSet.push_back(frame);
                } */
                

                for (int i = 0; i < 1; i++) {
                    for (auto &frame : trainingSet) {
                        network.processFrame(frame);
                    }
                }

                network.purgeDeadNeurons();

                std::ofstream lumaNeuronsFile("lumaNeuronsValues.csv");
                std::ofstream redChromaNeuronsFile(
                    "redChromaNeuronsValues.csv");
                std::ofstream blueChromaNeuronsFile(
                    "blueChromaNeuronsValues.csv");

                for (auto neuron : network.getLumaNeurons()) {
                    lumaNeuronsFile << neuron.serialize();
                }

                for (auto neuron : network.getRedChromaNeurons()) {
                    redChromaNeuronsFile << neuron.serialize();
                }

                for (auto neuron : network.getBlueChromaNeurons()) {
                    blueChromaNeuronsFile << neuron.serialize();
                }

                lumaNeuronsFile.close();
                redChromaNeuronsFile.close();
                blueChromaNeuronsFile.close();
            } else {
                std::ifstream lumaNeuronsFile("lumaNeuronsValues.csv");
                std::ifstream redChromaNeuronsFile(
                    "redChromaNeuronsValues.csv");
                std::ifstream blueChromaNeuronsFile(
                    "blueChromaNeuronsValues.csv");

                std::vector<SOM::Neuron> lumaNeuronsList;
                std::vector<SOM::Neuron> redChromaNeuronsList;
                std::vector<SOM::Neuron> blueChromaNeuronsList;

                std::string buffer;
            std:
                string delimiter = ";";

                while (getline(lumaNeuronsFile, buffer)) {
                    size_t pos = 0;
                    std::vector<double> weights;
                    unsigned long winnerCounter = 0;
                    std::string token;
                    int counter = 0;
                    while ((pos = buffer.find(delimiter)) !=
                           std::string::npos) {
                        token = buffer.substr(0, pos);
                        buffer.erase(0, pos + delimiter.length());
                        if (counter == 0) {
                            winnerCounter = atol(token.c_str());
                        } else {
                            double temp = atof(token.c_str());
                            weights.push_back(temp);
                        }
                        counter++;
                    }
                    SOM::Neuron neuron(weights);
                    neuron.setWinnerCount(winnerCounter);
                    lumaNeuronsList.push_back(neuron);
                }

                while (getline(redChromaNeuronsFile, buffer)) {
                    size_t pos = 0;
                    std::vector<double> weights;
                    unsigned long winnerCounter = 0;
                    std::string token;
                    int counter = 0;
                    while ((pos = buffer.find(delimiter)) !=
                           std::string::npos) {
                        token = buffer.substr(0, pos);
                        buffer.erase(0, pos + delimiter.length());
                        if (counter == 0) {
                            winnerCounter = atol(token.c_str());
                        } else {
                            double temp = atof(token.c_str());
                            weights.push_back(temp);
                        }
                        counter++;
                    }
                    SOM::Neuron neuron(weights);
                    neuron.setWinnerCount(winnerCounter);
                    redChromaNeuronsList.push_back(neuron);
                }
                while (getline(blueChromaNeuronsFile, buffer)) {
                    size_t pos = 0;
                    std::vector<double> weights;
                    unsigned long winnerCounter = 0;
                    std::string token;
                    int counter = 0;
                    while ((pos = buffer.find(delimiter)) !=
                           std::string::npos) {
                        token = buffer.substr(0, pos);
                        buffer.erase(0, pos + delimiter.length());
                        if (counter == 0) {
                            winnerCounter = atol(token.c_str());
                        } else {
                            double temp = atof(token.c_str());
                            weights.push_back(temp);
                        }
                        counter++;
                    }
                    SOM::Neuron neuron(weights);
                    neuron.setWinnerCount(winnerCounter);
                    blueChromaNeuronsList.push_back(neuron);
                }
                lumaNeuronsFile.close();
                redChromaNeuronsFile.close();
                blueChromaNeuronsFile.close();
                network.setLumaNeurons(lumaNeuronsList);
                network.setRedChromaNeurons(redChromaNeuronsList);
                network.setBlueChromaNeurons(blueChromaNeuronsList);
            }


            SOM::SOMNetworkEncoder encoder(network);

            std::vector<std::vector<SOM::SubframeCompressed>> encodedFrames =
                encoder.encode(framesList);
            std::vector<SOM::SubframeCompressed> encodedFramesArrayFlattened;
            for (int i = 0; i < encodedFrames.size(); i++) {
                for (int j = 0; j < encodedFrames[i].size(); j++) {
                    encodedFramesArrayFlattened.push_back(encodedFrames[i][j]);
                }
            }
            SOM::SOMNetworkDecoder decoder(
                network, encodedFrames, image.getYCbCrImageHandle().cols,
                image.getYCbCrImageHandle().rows, 8, 8);
            std::vector<SOM::Pixel> resultImagePixelArray = decoder.decode();
            SOM::Image newImage;
            newImage.setPixelArray(resultImagePixelArray);
            newImage.transformPixelArrayToImage();
            // newImage.transformYCbCr2BGR();
            newImage.saveToFile("testimage.jpg");image.transformImageToPixelArray();
            ImGui::ProgressBar(1, ImVec2(0.f, 0.f));
            ImGui::Text("File was successfuly compressed and saved as testimage.jpg");
        }

        //ImGui::SliderFloat("Compression rate", &compRate, 1.f, 50.f);
        //ImGui::SliderFloat("PSNR", &psnr, 1.f, 50.f);
        
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