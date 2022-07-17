//
// Created by tsin on 22-7-17.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"
#include "glad/glad.h"

Shader::Shader(std::string vsFile, std::string fsFile) {

    std::ifstream vsSource;
    std::ifstream fsSource;
    vsSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fsSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string vsCode;
    std::string fsCode;
    std::stringstream vsStream, fsStream;

    try {
        vsSource.open(vsFile);
        fsSource.open(fsFile);


        vsStream << vsSource.rdbuf();
        fsStream << fsSource.rdbuf();

        vsSource.close();
        fsSource.close();

        vsCode = vsStream.str();
        fsCode = fsStream.str();
    }catch (std::ifstream::failure e){
        std::cout << "Read Failed : " << e.what() << std::endl;
    }

    const char *vertShaderSource = vsCode.c_str();
    const char *fragShaderSource = fsCode.c_str();

    vertShaderID_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShaderID_, 1, &vertShaderSource, NULL);
    glCompileShader(vertShaderID_);
    int success;
    char infoLog[512];
    glGetShaderiv(vertShaderID_, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertShaderID_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragShaderID_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderID_, 1, &fragShaderSource, NULL);
    glCompileShader(fragShaderID_);
    glGetShaderiv(fragShaderID_, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragShaderID_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    programID_ = glCreateProgram();
    glAttachShader(programID_, vertShaderID_);
    glAttachShader(programID_, fragShaderID_);
    glLinkProgram(programID_);
    glGetProgramiv(programID_, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(programID_, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertShaderID_);
    glDeleteShader(fragShaderID_);

}

void Shader::Use() {
    glUseProgram(programID_);
}

void Shader::SetInt(std::string &name, int value) {
    glUniform1i(glGetUniformLocation(programID_, name.c_str()), value);
}

void Shader::SetFloat(std::string &name, float value) {
    glUniform1f(glGetUniformLocation(programID_, name.c_str()), value);
}

void Shader::SetBool(std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(programID_, name.c_str()), value);
}
