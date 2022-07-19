//
// Created by tsin on 22-7-17.
//
#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"

Camera camera(glm::vec3(0.0, 0.0, 3.0));
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_move_callback(GLFWwindow *window, double x, double y);
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessWASDMove(camera.cameraLookVec_*0.1f);

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessWASDMove(-camera.cameraLookVec_*0.1f);

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessWASDMove(glm::normalize(glm::cross(camera.cameraUp_, camera.cameraLookVec_))*0.1f);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessWASDMove(- glm::normalize(glm::cross(camera.cameraUp_, camera.cameraLookVec_))*0.1f);


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
    glfwSetCursorPosCallback(window, mouse_move_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

}

int main(){

    GLFWwindow *window = nullptr;
    Init(window);


    glEnable(GL_DEPTH_TEST);

    // 由于我们希望渲染一个三角形，我们一共要指定三个顶点，每个顶点都有一个3D位置。
    // 我们会将它们以标准化设备坐标的形式（OpenGL的可见区域）定义为一个float数组
    float vertices[] = {
            //the four vertex in front face.
            0.5f,  0.5f,  0.5f,    0.6f, 0.2f, 0.0f,    1.0f, 0.0f,// 右上角 0
            0.5f, -0.5f,  0.5f,    0.0f, 0.4f, 0.6f,    1.0f, 1.0f,// 右下角 1
            -0.5f, -0.5f,  0.5f,    0.2f, 0.0f, 1.0f,    0.0f, 1.0f,// 左下角 2
            -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,// 左上角 3

            //the four vertex in back  face.
            0.5f,  0.5f, -0.5f,    0.6f, 0.2f, 0.0f,    1.0f, 0.0f,// 右上角 4
            0.5f, -0.5f, -0.5f,    0.0f, 0.4f, 0.6f,    1.0f, 1.0f,// 右下角 5
            -0.5f, -0.5f, -0.5f,    0.2f, 0.0f, 1.0f,    0.0f, 1.0f,// 左下角 6
            -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f // 左上角 7
    };

    unsigned int indices[] = {
            0, 1, 3,// 第一个三角形
            1, 2, 3, // 第二个三角形
            7, 4, 0,
            7, 0, 3,
            1, 0, 4,
            1, 4, 5,
            6, 7, 3,
            6, 3, 2,
            2, 1, 6,
            1, 5, 6,
            4, 7, 6,
            5, 4, 6,
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


    Shader shader("../08_camera/_vert.glsl", "../08_camera/_frag.glsl");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    //texture
    int w1, h1, c1;
    unsigned char *data1 = stbi_load("../08_camera/texture1.png", &w1, &h1, &c1, 0);
    assert(data1);

    int w2, h2, c2;
    unsigned char *data2 = stbi_load("../08_camera/texture2.png", &w2, &h2, &c2, 0);
    assert(data2);

    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glGenTextures(2, &texture2);

    glActiveTexture(GL_TEXTURE0);// 默认激活
    glBindTexture(GL_TEXTURE_2D, texture1);
/*
    //函数很长，参数也不少，所以我们一个一个地讲解：
    // • 第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
    // • 第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
    // • 第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
    // • 第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
    // • 下个参数应该总是被设为0（历史遗留的问题）。
    // • 第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char (byte)数组，我们将会传入对应值。
    // • 最后一个参数是真正的图像数据
*/

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w1, h1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);


    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w2, h2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data1);
    stbi_image_free(data2);

    shader.Use();

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //------------------------set uniform---------------
        float timeValue = glfwGetTime();
        float s = (sin(timeValue) / 2.0f) + 0.5f;

        std::string sinName = "s";
        shader.SetFloat(sinName, s);

        std::string textureUnit1Name = "texture1";
        shader.SetInt(textureUnit1Name, 0);

        std::string textureUnit2Name = "texture2";
        shader.SetInt(textureUnit2Name, 1);

        // GLM库从0.9.9版本起，默认会将矩阵类型初始化为一个零矩阵（所有元素均为0），而不是单位矩阵（对角元素为1，其它元素为0）。如果你使用的是0.9.9或0.9.9以上的版本，
        // 你需要将所有的矩阵初始化改为glm::mat4 mat = glm::mat4(1.0f)。如果你想与本教程的代码保持一致，请使用低于0.9.9版本的GLM，或者改用上述代码初始化所有的矩阵



        for(int i = -2; i < 3; ++i) {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = camera.GetView();
            //glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 proj = glm::mat4(1.0);


            model = glm::translate(model,  glm::vec3(s*i*1.5 , .0, -8.0));
            model = glm::rotate(model, s*30.f, glm::vec3(0.f, 1.0f, 0.f));

            proj = glm::perspective(glm::radians(45.0f), 800.f/600.f, 0.0001f, 1000.0f);

            std::string modelName = "model";
            shader.SetMat4(modelName, glm::value_ptr(model));
            std::string viewName = "view";
            shader.SetMat4(viewName, glm::value_ptr(view));
            std::string projName = "projection";
            shader.SetMat4(projName, glm::value_ptr(proj));


            glBindVertexArray(VAO);
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

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

static double lastX = 400;
static double lastY = 300;
static double pitch = 0;
static double yaw = 0;

void mouse_move_callback(GLFWwindow *window, double x, double y){
    double xOffset = x - lastX;
    double yOffset = lastY - y;
    xOffset *= 0.05;
    yOffset *= 0.05;

    pitch += yOffset;
    yaw += xOffset;

    if (pitch > +89.f) pitch = +89.f;
    if (pitch < -89.f) pitch = -89.f;

    camera.ProcessMouseMove(pitch, yaw);
    lastX = x;
    lastY = y;
}
