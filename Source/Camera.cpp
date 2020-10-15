//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include <iostream>
#include "Camera.h"

static constexpr float MOVEMENT_SPEED = 0.1f;
static constexpr float ROTATION_SPEED = 10.0f;

glm::mat4 FCamera::GetProjectionMatrix()
{
    int WindowWidth, WindowHeight;
    glfwGetWindowSize(mWindow, &WindowWidth, &WindowHeight);
    return glm::perspective(glm::radians(60.0f), (float) WindowWidth / WindowHeight, 0.01f, 1000.0f);
}

glm::mat4 FCamera::GetViewMatrix()
{
    return glm::lookAt(mPosition, mPosition + mDirection, mUp);
}

void FCamera::Update(const PSD::FInputSource* InputSource, double DeltaTime)
{
    if (InputSource->IsKeyDown(PSD::W))
    {
        mPosition += mDirection * MOVEMENT_SPEED * (float) DeltaTime;
    }
    if (InputSource->IsKeyDown(PSD::S))
    {
        mPosition -= mDirection * MOVEMENT_SPEED * (float) DeltaTime;
    }

    if (InputSource->IsKeyDown(PSD::A))
    {
        mPosition -= glm::normalize(glm::cross(mDirection, mUp)) * MOVEMENT_SPEED * (float) DeltaTime;
    }
    if (InputSource->IsKeyDown(PSD::D))
    {
        mPosition += glm::normalize(glm::cross(mDirection, mUp)) * MOVEMENT_SPEED * (float) DeltaTime;
    }

    if (InputSource->IsKeyDown(PSD::LSHIFT))
    {
        mPosition.y -= MOVEMENT_SPEED * (float) DeltaTime;
    }
    if (InputSource->IsKeyDown(PSD::SPACE))
    {
        mPosition.y += MOVEMENT_SPEED * (float) DeltaTime;
    }

    if (InputSource->IsKeyDown(PSD::X) || InputSource->IsRightMouseButtonDown())
    {
        if (!bIsDragging) // Drag gerade erst begonnen
        {
            InputSource->GetMousePosition(&mPreviousX, &mPreviousY);
            bIsDragging = true;
            return;
        }

        double X, Y;
        InputSource->GetMousePosition(&X, &Y);
        double DeltaX = X - mPreviousX, DeltaY = mPreviousY - Y;
        mPreviousX = X, mPreviousY = Y;

        mYaw += DeltaX * ROTATION_SPEED * (float) DeltaTime, mPitch += DeltaY * ROTATION_SPEED * (float) DeltaTime;
        mPitch = glm::clamp(mPitch, -89.0, 89.0);

        glm::vec3 Direction;
        Direction.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        Direction.y = sin(glm::radians(mPitch));
        Direction.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        mDirection = glm::normalize(Direction);
    }
    else
    {
        bIsDragging = false;
    }

}
