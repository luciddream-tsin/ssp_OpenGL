#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

out vec4 ourColor; // 为片段着色器指定一个颜色输出
out vec2 texCoord;


void main()
{
    gl_Position = vec4(aPos, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
    ourColor = vec4(aColor, 1.0);
    texCoord = aUV;

}