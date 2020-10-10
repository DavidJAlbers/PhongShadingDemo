//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include "ControlPanel.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <iostream>

PSD::FControlPanel::FControlPanel(GLFWwindow* Window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    std::cout << "GUI system initialized, running on Dear ImGui v" << ImGui::GetVersion() << "\n";
}

PSD::FControlPanel::~FControlPanel()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void PSD::FControlPanel::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Control Panel");
    ImGui::ColorEdit3("Background Color", mClearColor);
    ImGui::ColorEdit3("Object Color", mObjectColor);
    ImGui::Separator();
    ImGui::Checkbox("Enable Wireframe Rendering", bIsWireframeEnabled);
    ImGui::End();
}

void PSD::FControlPanel::Render() const
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
