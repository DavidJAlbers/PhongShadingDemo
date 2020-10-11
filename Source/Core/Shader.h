//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_SHADER_H
#define PSD_SHADER_H

#include "GL/gl3w.h"
#include "glm/glm.hpp"

#include <string>
#include <map>

namespace PSD
{

    class FShader
    {
    public:
        explicit FShader(const std::string& Name);
        ~FShader();

        void Bind() const;

        void SetVector3f(const std::string&, const float&, const float&, const float&);
        void SetVector3f(const std::string&, float*);

        void SetMatrix4f(const std::string&, const glm::mat4&);

    private:
        GLuint mProgramID;
        std::map<std::string, int> mUniformLocations;

        int GetUniformLocation(const std::string&) const;
    };
}

#endif //PSD_SHADER_H
