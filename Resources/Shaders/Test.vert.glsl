#version 450 core

layout (location = 0) in vec3 InVertexPosition;

uniform mat4 ModelMatrix;
uniform mat4 ProjectionViewMatrix;

void main() {
    gl_Position = ProjectionViewMatrix * ModelMatrix * vec4(InVertexPosition, 1.0);
}