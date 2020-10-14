//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include "GeometryObject.h"

#include "glm/ext.hpp"

void FGeometryObject::Draw()
{
    mMesh->SimpleDraw();
}

glm::mat4 FGeometryObject::GetModelMatrix()
{
    glm::mat4 ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(mScale));
    return glm::translate(ModelMatrix, mPosition);
}
