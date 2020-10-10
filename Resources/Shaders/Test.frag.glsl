#version 450 core

out vec4 OutVertexColor;

uniform vec3 VertexColor;

void main() {
    OutVertexColor = vec4(VertexColor, 1.0);
}