//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

#include "glm/ext.hpp"

static std::string LoadSource(const std::string& Name, const std::string& Type)
{
    std::ostringstream Path;
    Path << "Resources/Shaders/" << Name << "." << Type << ".glsl";
    std::ifstream File(Path.str());

    std::ostringstream Source;
    std::string Line;
    while (std::getline(File, Line))
    {
        Source << Line << "\n";
    }
    return Source.str();
}

static void CheckCompilationStatus(const GLuint& Shader, const std::string& Name, const std::string& Type)
{
    GLint CompilationStatus;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &CompilationStatus);
    if (CompilationStatus == GL_FALSE)
    {
        GLint LogLength;
        glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &LogLength);
        GLchar Log[LogLength];
        glGetShaderInfoLog(Shader, sizeof(Log), nullptr, Log);
        std::cout << "The " << Name << " " << Type << " shader failed to compile, aborting: " << Log << "\n";
        std::exit(-1);
    }
}

static void CheckLinkingStatus(const GLuint& Program, const std::string& Name)
{
    GLint LinkingStatus;
    glGetProgramiv(Program, GL_LINK_STATUS, &LinkingStatus);
    if (LinkingStatus == GL_FALSE)
    {
        GLint LogLength;
        glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &LogLength);
        GLchar Log[LogLength];
        glGetProgramInfoLog(Program, sizeof(Log), nullptr, Log);
        std::cout << "The " << Name << " shader failed to link, aborting: " << Log << "\n";
        std::exit(-1);
    }
}

PSD::FShader::FShader(const std::string& Name)
{
    auto VertexSource = LoadSource(Name, "vert");
    auto FragmentSource = LoadSource(Name, "frag");

    if (VertexSource.empty() || FragmentSource.empty())
    {
        std::cout << "The shader " << Name << " could not be found or read, aborting\n";
        std::exit(-1);
    }

    mProgramID = glCreateProgram();
    auto VertexShader = glCreateShader(GL_VERTEX_SHADER);
    auto FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* glVertexSource = VertexSource.c_str();
    const GLchar* glFragmentSource = FragmentSource.c_str();
    glShaderSource(VertexShader, 1, &glVertexSource, nullptr);
    glShaderSource(FragmentShader, 1, &glFragmentSource, nullptr);
    glCompileShader(VertexShader);
    glCompileShader(FragmentShader);
    CheckCompilationStatus(VertexShader, Name, "vertex");
    CheckCompilationStatus(FragmentShader, Name, "fragment");
    glAttachShader(mProgramID, VertexShader);
    glAttachShader(mProgramID, FragmentShader);
    glLinkProgram(mProgramID);
    CheckLinkingStatus(mProgramID, Name);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}

void PSD::FShader::Bind() const
{
    glUseProgram(mProgramID);
}

PSD::FShader::~FShader()
{
    glDeleteProgram(mProgramID);
}

void PSD::FShader::SetVector3f(const std::string& Name, const float& X, const float& Y, const float& Z)
{
    glProgramUniform3f(mProgramID, GetUniformLocation(Name), X, Y, Z);
}

void PSD::FShader::SetVector3f(const std::string& Name, float* Value)
{
    glProgramUniform3fv(mProgramID, GetUniformLocation(Name), 1, Value);
}

void PSD::FShader::SetMatrix4f(const std::string& Name, const glm::mat4& Value)
{
    auto RawValue = glm::value_ptr(Value);
    Bind();
    glProgramUniformMatrix4fv(mProgramID, GetUniformLocation(Name), 1, GL_FALSE, RawValue);
}

int PSD::FShader::GetUniformLocation(const std::string& Name) const
{
// TODO This seems to be causing GL_INVALID_OPERATION sometimes. Look into it
//    if (mUniformLocations.find(Name) != mUniformLocations.end())
//    {
//        mUniformLocations[Name] = glGetUniformLocation(mProgramID, Name.c_str());
//    }
//    return mUniformLocations[Name];
    return glGetUniformLocation(mProgramID, Name.c_str());
}
