//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_RENDERER_H
#define PSD_RENDERER_H

#include <memory>

#include "PSD.h"

#include "Camera.h"
#include "GeometryObject.h"

class FRenderer
{
public:
    void BeginScene(std::shared_ptr<PSD::FShader>, std::shared_ptr<FCamera>);
    void DrawSingle(std::shared_ptr<FGeometryObject>);
    void EndScene();
private:
    bool bIsInScene = false;
    std::shared_ptr<PSD::FShader> mShader;
    std::shared_ptr<FCamera> mCamera;
};


#endif //PSD_RENDERER_H
