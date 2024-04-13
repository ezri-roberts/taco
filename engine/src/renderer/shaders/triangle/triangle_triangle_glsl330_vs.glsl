#version 330

layout(location = 0) in vec4 position;
out vec4 color;
layout(location = 1) in vec4 color0;

void main()
{
    gl_Position = position;
    color = color0;
}

