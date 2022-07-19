//
// Created by tsin on 22-7-18.
//

#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera(glm::vec3 cameraPos):
cameraPos_(cameraPos), cameraLookVec_(0.0, 0.0f, -1.0), cameraUp_(0.0, 1.0, 0.0) {

}

void Camera::ProcessMouseMove(double pitch, double yaw) {
//下面添加相机类, 其实就是移动物体然后进行一个基变换, glm::lookAt， 就是干这个的,
//接受三个参数, (相机位置CP, 相机看的目标位置TP, UP向量), 不要忘记normalize.
//注意, 你填的参数是相机的, 但这个lookAt的结果矩阵是用于模型, 说明已经转置过啦!!!!!!!!
//  过程讲解, 他用CP-TP 得到相机坐标系的z轴(任然是右手系, z轴正方向和观察方向相反),
//  然后使用这个z得到x和y, 略,
//  这里要说的是, TP是个点, TP = CP + LookVec, 所以只需要只需要计算看向方向向量LookVec即可
//NOTE:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//你用以下方式计算旋转正交基, 就已经默认, 是看向z的负方向的, 若果默认看向别的地方, 计算公式不一样
//而且千万不要忘记 给z轴添加负号!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    cameraLookVec_.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraLookVec_.y = sin(glm::radians(pitch));
    cameraLookVec_.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));

    //这样理解: 这只是得到相机看向的方向向量LookVec, 是为了得到 CP+LookVec 为LookAt 提供第二个参数

    cameraLookVec_ = glm::normalize(cameraLookVec_);

    view_ = glm::lookAt(cameraPos_, cameraPos_+cameraLookVec_, cameraUp_);
}

void Camera::ProcessWASDMove(glm::vec3 moved){
    cameraPos_ += moved;
    view_ = glm::lookAt(cameraPos_, cameraPos_+cameraLookVec_, cameraUp_);
}


glm::mat4 Camera::GetView() {
    return view_;
}