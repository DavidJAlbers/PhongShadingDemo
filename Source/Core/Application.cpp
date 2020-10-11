//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include <GL/gl3w.h>

#include "Application.h"

#include <iostream>
#include <ctime>

static PSD::FApplication* TheApplication = nullptr;

PSD::FApplication* PSD::GetApplication()
{
    if (TheApplication == nullptr)
    {
        std::cout << "The Application instance has not been created or set so far. Call PSD::SetApplication first! Aborting\n";
        std::exit(-1);
    }
    return TheApplication;
}

PSD::FApplication* PSD::SetApplication(PSD::FApplication* Application)
{
    if (TheApplication != nullptr)
    {
        std::cout << "Another Application instance already exists, aborting\n";
        std::exit(-1);
    }
    return TheApplication = Application;
}

static void GLFWErrorCallback(int ErrorCode, const char* Description)
{
    std::cout << "GLFW error " << ErrorCode << " occurred, aborting: " << Description << "\n";
    std::exit(-1);
}

static void GLErrorCallback(GLenum Source, GLenum Type, GLuint ID, GLenum Severity, GLsizei, const GLchar* Message, const void*)
{
    std::cout << "GL: " << Message << std::hex << " (GL message of type 0x" << Type << " with source 0x" << Source << ", ID " << std::dec << ID <<
              std::hex << " and severity 0x" << Severity << ")\n" << std::dec;
}

PSD::FApplication::FApplication(const std::string& Name)
    : mApplicationName(Name)
{
    std::cout << "This is PhongShadingDemo by David J Albers, initializing application\n\n";

    std::time_t RawTime = std::time(nullptr);
    std::cout << "Current time is " << asctime(localtime(&RawTime));
}

PSD::FApplication::~FApplication()
{
    glfwDestroyWindow(mWindowHandle);
    glfwTerminate();
}

void PSD::FApplication::Start()
{
    glfwSetErrorCallback(&GLFWErrorCallback);
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW, aborting\n";
        std::exit(-1);
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    mWindowHandle = glfwCreateWindow(1280, 720, mApplicationName.c_str(), nullptr, nullptr);
    if (!mWindowHandle)
    {
        std::exit(-1);
    }

    glfwMakeContextCurrent(mWindowHandle);
    if (gl3wInit())
    {
        std::cout << "Failed to initialize OpenGL, aborting\n";
        std::exit(-1);
    }

    glDebugMessageCallback(&GLErrorCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

    std::cout << "Rendering context created, running on OpenGL " << glGetString(GL_VERSION) << "\n";

    OnStart();

    while (!glfwWindowShouldClose(mWindowHandle))
    {
        glfwPollEvents();

        OnUpdate();

        int Width, Height;
        glfwGetFramebufferSize(mWindowHandle, &Width, &Height);
        glViewport(0, 0, Width, Height);
        glClearBufferfv(GL_COLOR, 0, mClearColor);

        if (bIsWireframeEnabled)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        OnRender();

        glfwSwapBuffers(mWindowHandle);
    }
}
