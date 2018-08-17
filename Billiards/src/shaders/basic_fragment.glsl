//  basic_fragment.glsl
//  Created on: Aug 17, 2018
//    Author: Samuel Tan
#version 330 core

in vec4 vo_color;
out vec4 color;

void main()
{
    color = vo_color;
}