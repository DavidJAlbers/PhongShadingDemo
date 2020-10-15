#version 450 core

layout (location = 0) in vec3 InVertexPosition;
layout (location = 1) in vec3 InVertexNormal;

out vec3 FragmentPosition;
out vec3 VertexNormal;

uniform mat4 ModelMatrix;
uniform mat4 ProjectionViewMatrix;

void main() {
    vec4 VertexPosition = ModelMatrix * vec4(InVertexPosition, 1.0);
    gl_Position = ProjectionViewMatrix * VertexPosition;
    FragmentPosition = VertexPosition.xyz;
    VertexNormal = InVertexNormal;
}