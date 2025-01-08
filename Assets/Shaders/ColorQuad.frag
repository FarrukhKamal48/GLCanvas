#version 440 core

layout(location = 0) out vec4 color;
layout(location = 1) out vec4 color2;
in vec4 v_Color;
in vec2 v_TexCoord;

void main() {
    color = v_Color;
    color2 = vec4(0.9, 0.5, 0.0, 1.0);
};
