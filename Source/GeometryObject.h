//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_GEOMETRYOBJECT_H
#define PSD_GEOMETRYOBJECT_H

#include "glm/glm.hpp"

#include "PSD.h"

#include <memory>

class FGeometryObject
{
public:
    explicit FGeometryObject(std::unique_ptr<PSD::FVertexArray> Mesh = PSD::GetDefaultCube(), glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), float Scale = 1.0f, glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f))
    : mMesh(std::move(Mesh)), mPosition(Position), mScale(Scale), mColor(Color) { }

    void Draw();

    glm::mat4 GetModelMatrix();

    inline glm::vec3 GetColor() { return mColor; }

private:
    glm::vec3 mPosition;
    glm::vec3 mColor;
    float mScale;

    std::unique_ptr<PSD::FVertexArray> mMesh;
};


#endif //PSD_GEOMETRYOBJECT_H
