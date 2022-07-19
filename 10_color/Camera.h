//
// Created by tsin on 22-7-18.
//

#ifndef SSPOPENGL_CAMERA_H
#define SSPOPENGL_CAMERA_H


#include "glm/vec3.hpp"
#include "glm/glm.hpp"

class Camera {
public:
    Camera(glm::vec3 cameraPos);

    void ProcessMouseMove(double pitch, double yaw);
    void ProcessWASDMove(glm::vec3 moved);
    glm::mat4 GetView();

    glm::vec3 cameraPos_;
    glm::vec3 cameraLookVec_;
    glm::vec3 cameraUp_;

    glm::mat4 view_;

};



#endif //SSPOPENGL_CAMERA_H
