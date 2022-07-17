//
// Created by tsin on 22-7-17.
//

#ifndef SSPOPENGL_SHADER_H
#define SSPOPENGL_SHADER_H

#include "string"

class Shader {
public:
    Shader(std::string vsFile, std::string fsFile);

    void Use();

    void SetBool(std::string &name, bool value);
    void SetInt(std::string &name, int value);
    void SetFloat(std::string &name, float value);

private:
    unsigned int programID_;
    unsigned int vertShaderID_;
    unsigned int fragShaderID_;


};


#endif //SSPOPENGL_SHADER_H
