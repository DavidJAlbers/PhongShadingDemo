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
    return glm::translate(glm::mat4(1.0f), mPosition) * glm::scale(glm::mat4(1.0f), glm::vec3(mScale));
}
