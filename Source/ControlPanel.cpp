//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include "ControlPanel.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <iostream>

FControlPanel::FControlPanel(GLFWwindow* Window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    std::cout << "GUI system initialized, running on Dear ImGui v" << ImGui::GetVersion() << "\n";
}

FControlPanel::~FControlPanel()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void FControlPanel::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Control Panel");
    ImGui::DragFloat3("Camera position", mCameraPosition, 0.1f);
    ImGui::Separator();
    ImGui::DragFloat3("Light direction", mLightDirection);
    ImGui::ColorEdit3("Background Color", mClearColor);
    ImGui::Separator();
    ImGui::Checkbox("Enable Wireframe Rendering", bIsWireframeEnabled);
    ImGui::Spacing();
    ImGui::TextDisabled("Copyright (c) 2019-2020 David J Albers.");
    ImGui::End();
}

void FControlPanel::Render() const
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
