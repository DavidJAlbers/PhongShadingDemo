#version 450 core

in vec3 VertexPosition;

void main() {
    gl_Position = vec4(VertexPosition, 1.0);
}