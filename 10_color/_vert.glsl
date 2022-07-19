#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
}