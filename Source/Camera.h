//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_CAMERA_H
#define PSD_CAMERA_H

#include "PSD.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class FCamera
{
public:
    explicit FCamera(GLFWwindow* Window, glm::vec3 Position) : mWindow(Window), mPosition(Position) {}

    void Update(const PSD::FInputSource*, double DeltaTime);

    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();

    float* GetPosition() { return glm::value_ptr(mPosition); }

private:
    glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 mDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);

    double mYaw = -90.0, mPitch = 0.0;

    GLFWwindow* mWindow;

    double mPreviousX;
    double mPreviousY;
    bool bIsDragging = false;
};


#endif //PSD_CAMERA_H
