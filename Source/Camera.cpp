//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include "Camera.h"

#include "glm/ext.hpp"

void FCamera::Update()
{

}

glm::mat4 FCamera::GetProjectionMatrix()
{
    int WindowWidth, WindowHeight;
    glfwGetWindowSize(mWindow, &WindowWidth, &WindowHeight);
    return glm::perspective(glm::radians(60.0f), (float) WindowWidth / WindowHeight, 0.01f, 1000.0f);
}

glm::mat4 FCamera::GetViewMatrix()
{
    return glm::lookAt(mPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
