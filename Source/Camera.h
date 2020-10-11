//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_CAMERA_H
#define PSD_CAMERA_H


#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class FCamera
{
public:
    explicit FCamera(GLFWwindow* Window, glm::vec3 Position) : mWindow(Window), mPosition(Position) {}

    void Update();

    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();

    float* GetPosition() { return glm::value_ptr(mPosition); }

private:
    glm::vec3 mPosition;
    GLFWwindow* mWindow;
};


#endif //PSD_CAMERA_H
