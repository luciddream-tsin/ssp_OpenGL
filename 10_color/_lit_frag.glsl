#version 330 core
out vec4 FragColor;

in vec4 ourColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）

uniform float s;


void main()
{

FragColor = vec4(1.0);

}