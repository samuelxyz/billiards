//  basic_vertex.glsl
//  Created on: Aug 17, 2018
//    Author: Samuel Tan
//
#version 330 core

in vec4 position;
in vec4 color;
out vec4 vo_color;

uniform mat4 u_projMatrix;

void main()
{
    gl_Position = u_projMatrix * position;
    vo_color = color;
}