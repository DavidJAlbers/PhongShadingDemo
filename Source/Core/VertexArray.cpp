//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include "VertexArray.h"

#include <sstream>
#include <fstream>
#include <iostream>

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
    std::vector<unsigned int> PositionIndices;
    std::vector<unsigned int> NormalIndices;

    std::string Line;
    std::string LineType;
    struct FFloatVec {
        float X, Y, Z;
    };
    struct FIntVec {
        unsigned int First, Second, Third;
    };
    struct FTwoIntVecs {
        FIntVec PositionIndices;
        FIntVec NormalIndices;
    };
    union ULineData {
        FFloatVec VertexData;
        FTwoIntVecs IndexData;
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
        else if (LineType == "f") // z. B. f 3//10 15//11 25//12
        {
            Input >> LineData.IndexData.PositionIndices.First;
            Input.ignore(2);
            Input >> LineData.IndexData.NormalIndices.First;
            Input >> LineData.IndexData.PositionIndices.Second;
            Input.ignore(2);
            Input >> LineData.IndexData.NormalIndices.Second;
            Input >> LineData.IndexData.PositionIndices.Third;
            Input.ignore(2);
            Input >> LineData.IndexData.NormalIndices.Third;
            PositionIndices.push_back(LineData.IndexData.PositionIndices.First - 1); // Das OBJ-Format beginnt bei 1, wir aber bei 0
            PositionIndices.push_back(LineData.IndexData.PositionIndices.Second - 1);
            PositionIndices.push_back(LineData.IndexData.PositionIndices.Third - 1);
            NormalIndices.push_back(LineData.IndexData.NormalIndices.First - 1);
            NormalIndices.push_back(LineData.IndexData.NormalIndices.Second - 1);
            NormalIndices.push_back(LineData.IndexData.NormalIndices.Third - 1);
        }
        else // Etwas anderes, was nicht unterstützt wird
        {
            continue;
        }
    }

    auto size = VertexNormals.size();
    float VertexNormalsReordered[size];
    auto VERTEX_SIZE = PSD::FVertexArray::VERTEX_SIZE;
    for (int i = 0; i < PositionIndices.size(); ++i)
    {
        VertexNormalsReordered[VERTEX_SIZE * PositionIndices[i]] = VertexNormals[VERTEX_SIZE * NormalIndices[i]];
        VertexNormalsReordered[VERTEX_SIZE * PositionIndices[i] + 1] = VertexNormals[VERTEX_SIZE * NormalIndices[i] + 1];
        VertexNormalsReordered[VERTEX_SIZE * PositionIndices[i] + 2] = VertexNormals[VERTEX_SIZE * NormalIndices[i] + 2];
    }

//    std::cout << "Vertex Positions:\n";
//    for (int i = 0; i < VertexPositions.size(); ++i)
//    {
//        std::cout << VertexPositions[i] << " " << VertexPositions[++i] << " " << VertexPositions[++i] << "\n";
//    }
//    std::cout << "Vertex Normals:\n";
//    for (int i = 0; i < VertexNormals.size(); ++i)
//    {
//        std::cout << VertexNormals[i] << " " << VertexNormals[++i] << " " << VertexNormals[++i] << "\n";
//    }
//    std::cout << "Position Indices:\n";
//    for (int i = 0; i < PositionIndices.size(); ++i)
//    {
//        std::cout << PositionIndices[i] << " " << PositionIndices[++i] << " " << PositionIndices[++i] << "\n";
//    }
//    std::cout << "Normal Indices:\n";
//    for (int i = 0; i < NormalIndices.size(); ++i)
//    {
//        std::cout << NormalIndices[i] << " " << NormalIndices[++i] << " " << NormalIndices[++i] << "\n";
//    }
//    std::cout << "Vertex Normals Reordered:\n";
//    for (int i = 0; i < VertexNormals.size(); ++i)
//    {
//        std::cout << VertexNormalsReordered[i] << " " << VertexNormalsReordered[++i] << " " << VertexNormalsReordered[++i] << "\n";
//    }

    std::unique_ptr<FVertexArray> VertexArray = std::make_unique<FVertexArray>();
    VertexArray->SetIndexBuffer(PositionIndices.data(), PositionIndices.size());
    VertexArray->AddVertexBuffer(VertexPositions.data(), VertexPositions.size());
    VertexArray->AddVertexBuffer(VertexNormalsReordered, VertexNormals.size());
    return VertexArray;
}

std::unique_ptr<PSD::FVertexArray> PSD::GetDefaultCube()
{
    return PSD::LoadMesh("Cube");
}
