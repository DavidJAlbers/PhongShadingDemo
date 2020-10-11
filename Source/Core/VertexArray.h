//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_VERTEXARRAY_H
#define PSD_VERTEXARRAY_H

#include "GL/gl3w.h"

#include <memory>
#include <vector>
#include <string>

namespace PSD
{
    class FVertexArray
    {
    public:
        static constexpr int VERTEX_SIZE = 3;

        FVertexArray();
        ~FVertexArray();

        void Bind() const;

        void SetIndexBuffer(const unsigned int*, unsigned int);
        void AddVertexBuffer(const float*, unsigned int);

        void SimpleDraw() const;

    private:
        GLuint mVAO;
        unsigned int mCurrentAttribIndex = 0;
        std::vector<GLuint> mBuffers;

        unsigned int mIndicesCount = 0;
        unsigned int mVerticesCount = 0;

    };

    std::unique_ptr<FVertexArray> LoadMesh(const std::string&);

}

#endif //PSD_VERTEXARRAY_H
