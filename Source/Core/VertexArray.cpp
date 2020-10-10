//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include "VertexArray.h"

#include <sstream>
#include <fstream>

PSD::FVertexArray::FVertexArray()
{
    glCreateVertexArrays(1, &mVAO);
}

PSD::FVertexArray::~FVertexArray()
{
    glDeleteBuffers(mBuffers.size(), mBuffers.data());
    glDeleteVertexArrays(1, &mVAO);
}

void PSD::FVertexArray::Bind() const
{
    glBindVertexArray(mVAO);
}

void PSD::FVertexArray::SetIndexBuffer(const unsigned int* Indices, unsigned int IndicesCount)
{
    GLuint IBO;
    glCreateBuffers(1, &IBO);
    mBuffers.push_back(IBO);

    glNamedBufferStorage(IBO, IndicesCount * sizeof(unsigned int), Indices, 0x00000000);
    glVertexArrayElementBuffer(mVAO, IBO);
    mIndicesCount = IndicesCount;
}

void PSD::FVertexArray::AddVertexBuffer(const float* Vertices, unsigned int VerticesCount)
{
    GLuint VBO;
    glCreateBuffers(1, &VBO);
    mBuffers.push_back(VBO);

    glNamedBufferStorage(VBO, sizeof(Vertices) * VerticesCount, Vertices, 0x00000000);

    glVertexArrayVertexBuffer(mVAO, mCurrentAttribIndex, VBO, 0, sizeof(float) * VERTEX_SIZE);
    glEnableVertexArrayAttrib(mVAO, mCurrentAttribIndex);
    glVertexArrayAttribBinding(mVAO, mCurrentAttribIndex, mCurrentAttribIndex);
    glVertexArrayAttribFormat(mVAO, mCurrentAttribIndex, VERTEX_SIZE, GL_FLOAT, GL_FALSE, 0);

    ++mCurrentAttribIndex;
    mVerticesCount = VerticesCount;
}

void PSD::FVertexArray::SimpleDraw() const
{
    Bind();
    if (mIndicesCount != 0)
    {
        glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, mVerticesCount);
    }
}

std::unique_ptr<PSD::FVertexArray> PSD::LoadMesh(const std::string& Name)
{
    std::ostringstream Path;
    Path << "Resources/Meshes/" << Name << ".obj";
    std::ifstream File(Path.str());

    std::vector<float> VertexPositions;
    std::vector<float> VertexNormals;
    std::vector<unsigned int> Indices;

    std::string Line;
    std::string LineType;
    struct FFloatVec {
        float X, Y, Z;
    };
    struct FIntVec {
        unsigned int First, Second, Third;
    };
    union ULineData {
        FFloatVec VertexData;
        FIntVec IndexData;
    } LineData;
    while (std::getline(File, Line))
    {
        std::istringstream Input(Line);

        Input >> LineType;
        if (LineType == "#")
        {
            continue;
        }
        else if (LineType == "v")
        {
            Input >> LineData.VertexData.X;
            Input >> LineData.VertexData.Y;
            Input >> LineData.VertexData.Z;
            VertexPositions.push_back(LineData.VertexData.X);
            VertexPositions.push_back(LineData.VertexData.Y);
            VertexPositions.push_back(LineData.VertexData.Z);
        }
        else if (LineType == "vn")
        {
            Input >> LineData.VertexData.X;
            Input >> LineData.VertexData.Y;
            Input >> LineData.VertexData.Z;
            VertexNormals.push_back(LineData.VertexData.X);
            VertexNormals.push_back(LineData.VertexData.Y);
            VertexNormals.push_back(LineData.VertexData.Z);
        }
        else if (LineType == "f") // z. B. f 1//1 14//1 13//1
        {
            int ToDiscard;
            Input >> LineData.IndexData.First;
            Input.ignore(2);
            Input >> ToDiscard;
            Input >> LineData.IndexData.Second;
            Input.ignore(2);
            Input >> ToDiscard;
            Input >> LineData.IndexData.Third;
            Input.ignore(2);
            Input >> ToDiscard;
            Indices.push_back(LineData.IndexData.First - 1); // Das OBJ-Format beginnt bei 1, wir aber bei 0
            Indices.push_back(LineData.IndexData.Second - 1);
            Indices.push_back(LineData.IndexData.Third - 1);
        }
        else // Etwas anderes, was nicht unterstützt wird
        {
            continue;
        }
    }

    std::unique_ptr<FVertexArray> VertexArray = std::make_unique<FVertexArray>();
    VertexArray->SetIndexBuffer(Indices.data(), Indices.size());
    VertexArray->AddVertexBuffer(VertexPositions.data(), VertexPositions.size());
    VertexArray->AddVertexBuffer(VertexNormals.data(), VertexNormals.size());
    return VertexArray;
}
