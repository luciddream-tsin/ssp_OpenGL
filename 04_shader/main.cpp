//
// Created by tsin on 22-7-17.
//
#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int Init(GLFWwindow* & window){
    //------------------------------------------------------------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //------------------------------------------------------------------------------------------------------------------
    window = glfwCreateWindow(800, 600, "SSPGL", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "create window failed" << std::endl;
        return -1;
    }
    //glfwCreateWindow函数需要窗口的宽和高作为它的前两个参数。第三个参数表示这个窗口的名称（标题），这里我们使用"LearnOpenGL"，
    // 最后两个参数我们暂时忽略。这个函数将会返回一个GLFWwindow对象，我们会在其它的GLFW操作中使用到。
    // 创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前线程的主上下文了。
    glfwMakeContextCurrent(window);

    //------------------------------------------------------------------------------------------------------------------

    //在之前的教程中已经提到过，GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        //我们给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //------------------------------------------------------------------------------------------------------------------

    //在我们开始渲染之前还有一件重要的事情要做，我们必须告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)，
    // 这样OpenGL才只能知道怎样根据窗口大小显示数据和坐标。我们可以通过调用glViewport函数来设置窗口的维度(Dimension)：
    glViewport(0, 0, 800, 600);

    //note: OpenGL幕后使用glViewport中定义的位置和宽高进行2D坐标的转换，将OpenGL中的位置坐标转换为你的屏幕坐标。
    // 例如，OpenGL中的坐标(-0.5, 0.5)有可能（最终）被映射为屏幕中的坐标(200,450)。注意，处理过的OpenGL坐标范围只为-1到1，
    // 因此我们事实上将(-1到1)范围内的坐标映射到(0, 800)和(0, 600)。
    //------------------------------------------------------------------------------------------------------------------



    //然而，当用户改变窗口的大小的时候，视口也应该被调整。我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。这个回调函数的原型如下：
    //void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

int main(){

    GLFWwindow *window = nullptr;
    Init(window);

    // 由于我们希望渲染一个三角形，我们一共要指定三个顶点，每个顶点都有一个3D位置。
    // 我们会将它们以标准化设备坐标的形式（OpenGL的可见区域）定义为一个float数组
    float vertices[] = {  0.5f,  0.5f,    0.0f,      0.4f,  0.3f,  0.5f, // 右上角
                          0.5f, -0.5f,    0.0f,      0.3f, 0.9f, 1.0f, // 右下角
                        -0.5f, -0.5f,  0.0f,     0.3f, 0.9f, 1.0f, // 左下角
                        -0.5f,  0.5f,  0.0f,     1.0f, 0.3f, 0.5f// 左上角
                        };
    unsigned int indices[] = {
            // 注意索引从0开始! // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
            // 这样可以由下标代表顶点组合成矩形
             0, 1, 3,// 第一个三角形
             1, 2, 3// 第二个三角形
    };


    //------------------------------------------------------------------------------------------------------
    // 放到bind IBO 前面
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //------------------------------------------------------------------------------------------------------


    // 添加index buffer
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); // 我故意把这个放到前面， 提示你这个是状态机机器, 各个buffer填充的顺序是独立的
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);


    Shader shader("../04_shader/_vert.glsl", "../04_shader/_frag.glsl");


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    shader.Use();
    while(!glfwWindowShouldClose(window))
    {

        processInput(window);

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //------------------------set uniform---------------
        // float timeValue = glfwGetTime();
        // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0, 1.0f);

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();


    }
    //------------------------------------------------------------------------------------------------------------------





    glfwTerminate();
    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
