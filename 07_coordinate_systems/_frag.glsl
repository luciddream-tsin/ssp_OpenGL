#version 330 core
out vec4 FragColor;

in vec4 ourColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
in vec2 texCoord;

uniform float s;
uniform sampler2D texture1;
uniform sampler2D texture2;


void main()
{

    FragColor = texture(texture1, texCoord) * 0.5 * (1 - s) + texture(texture2, texCoord) * s;
    FragColor = FragColor * 0.5+ ourColor * 0.5;

}