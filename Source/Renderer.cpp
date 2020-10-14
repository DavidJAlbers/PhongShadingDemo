//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include <iostream>
#include <utility>

#include "Renderer.h"

#include "glm/glm.hpp"

void FRenderer::BeginScene(std::shared_ptr<PSD::FShader> Shader, std::shared_ptr<FCamera> Camera)
{
    if (bIsInScene)
    {
        std::cout << "Renderer is already drawing a scene, aborting\n";
        std::exit(-1);
    }
    bIsInScene = true;
    mShader = std::move(Shader);
    mCamera = std::move(Camera);
    glm::mat4 ProjectionViewMatrix = mCamera->GetProjectionMatrix() * mCamera->GetViewMatrix();
    mShader->SetMatrix4f("ProjectionViewMatrix", ProjectionViewMatrix);
    mShader->Bind();
}

void FRenderer::DrawSingle(std::shared_ptr<FGeometryObject> Object)
{
    mShader->SetMatrix4f("ModelMatrix", Object->GetModelMatrix());
    Object->Draw();
}

void FRenderer::EndScene()
{
    if (!bIsInScene)
    {
        std::cout << "Renderer is not drawing a scene and EndScene was called, aborting\n";
        std::exit(-1);
    }
    mShader = nullptr;
    mCamera = nullptr;
    bIsInScene = false;
}
