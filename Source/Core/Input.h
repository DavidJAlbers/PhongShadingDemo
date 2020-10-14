//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_INPUT_H
#define PSD_INPUT_H

#include "GLFW/glfw3.h"

namespace PSD
{
    enum EKey
    {
        W = GLFW_KEY_W,
        A = GLFW_KEY_A,
        S = GLFW_KEY_S,
        D = GLFW_KEY_D,
        LSHIFT = GLFW_KEY_LEFT_SHIFT,
        SPACE = GLFW_KEY_SPACE
    };

    class FInputSource {
    public:
        virtual bool IsKeyDown(EKey) const = 0;
        virtual bool IsRightMouseButtonDown() const = 0;
        virtual void GetMousePosition(double*, double*) const = 0;
    };
}

#endif //PSD_INPUT_H
