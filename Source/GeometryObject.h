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
    explicit FGeometryObject(std::unique_ptr<PSD::FVertexArray> Mesh, glm::vec3 Position, float Scale)
    : mMesh(std::move(Mesh)), mPosition(Position), mScale(Scale) { }

    void Draw();

    glm::mat4 GetModelMatrix();

private:
    glm::vec3 mPosition;
    float mScale;

    std::unique_ptr<PSD::FVertexArray> mMesh;
};


#endif //PSD_GEOMETRYOBJECT_H
