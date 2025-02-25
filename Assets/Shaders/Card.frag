#version 440 core

layout(location = 0) out vec4 color;
layout(location = 1) out int ID;
in vec4 v_Color;
in vec2 v_TexCoord;
in flat int v_ID;

void main() {
    color = v_Color;
    ID = v_ID;
};
