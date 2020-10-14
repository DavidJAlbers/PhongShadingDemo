//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_APPLICATION_H
#define PSD_APPLICATION_H

#include "GLFW/glfw3.h"

#include "Input.h"

#include <string>

namespace PSD
{
    class FApplication : public FInputSource
    {
    public:
        explicit FApplication(const std::string& Name);
        ~FApplication();

        void Start();

        inline float* GetClearColor() { return mClearColor; }
        inline bool* IsWireframeEnabled() { return &bIsWireframeEnabled; }

        inline bool IsKeyDown(EKey Key) const override { return glfwGetKey(mWindowHandle, Key) == GLFW_PRESS; }
        inline bool IsRightMouseButtonDown() const override { return glfwGetMouseButton(mWindowHandle, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS; }
        inline void GetMousePosition(double* X, double* Y) const override { glfwGetCursorPos(mWindowHandle, X, Y); }

        inline GLFWwindow* ExposeNativeWindow() { return mWindowHandle; }

    protected:
        virtual void OnStart() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;

    private:
        float mClearColor[3] { 1.0f, 1.0f, 1.0f };
        bool bIsWireframeEnabled = false;

        GLFWwindow* mWindowHandle;
        std::string mApplicationName;
    };

    FApplication* GetApplication();
    FApplication* SetApplication(FApplication*);
}

#endif //PSD_APPLICATION_H
