#version 330

in vec2 UV;

out vec4 color;

uniform sampler2D texture_sampler;

void main() {
    color = texture(texture_sampler, UV);
}

