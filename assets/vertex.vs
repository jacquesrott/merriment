#version 330

layout(location = 0) in vec3 vertex_position_modelspace;
layout(location = 1) in vec2 vertex_uv;

out vec2 UV;

uniform mat4 MVP;

void main() {
    gl_Position =  MVP * vec4(vertex_position_modelspace, 1);
    UV = vertex_uv;
}

