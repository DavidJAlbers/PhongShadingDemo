//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_GEOMETRYOBJECT_H
#define PSD_GEOMETRYOBJECT_H

#include "glm/glm.hpp"

#include "Core/VertexArray.h"

#include <memory>

class FGeometryObject
{
public:
    explicit FGeometryObject(std::unique_ptr<PSD::FVertexArray> Mesh, glm::vec3 Position) : mMesh(std::move(Mesh)),
                                                                                            mPosition(Position) {}

    void Draw();

    inline glm::vec3 GetPosition() { return mPosition; }

private:
    glm::vec3 mPosition;

    std::unique_ptr<PSD::FVertexArray> mMesh;
};


#endif //PSD_GEOMETRYOBJECT_H
