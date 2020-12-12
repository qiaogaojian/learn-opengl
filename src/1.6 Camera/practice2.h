#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <stdlib.h>
using namespace glm;

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// 默认摄像机值
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// 用于计算OpenGl相机需要的欧拉角 向量和矩阵.
class Camera
{
public:
    // 相机属性
    vec3 Position;
    vec3 WorldUp;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    // 欧拉角
    float Yaw;   // 左右
    float Pitch; // 俯仰
    // 相机配置
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = vec3(posX, posY, posZ);
        WorldUp = vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    mat4 GetViewMatrix()
    {
        mat4 m1 = CustomLookAt(Position, Position + Front, Up);
        mat4 m2 = lookAt(Position, Position + Front, Up);
        return m2;
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        switch (direction)
        {
        case FORWARD:
            Position += Front * velocity;
            break;
        case BACKWARD:
            Position -= Front * velocity;
            break;
        case LEFT:
            Position -= Right * velocity;
            break;
        case RIGHT:
            Position += Right * velocity;
            break;
        }
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;
        // 限制俯仰角 确保摄像机不会翻转
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
            {
                Pitch = 89.0f;
            }
            else if (Pitch < -89.0f)
            {
                Pitch = -89.0f;
            }
        }
        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= yoffset;
        if (Zoom < 1.0f)
        {
            Zoom = 1.0f;
        }
        else if (Zoom > 60.0f)
        {
            Zoom = 60.0f;
        }
    }

private:
    // 根据相机欧拉角计算相机前向量
    void updateCameraVectors()
    {
        vec3 front;
        front.x = cos(radians(Yaw)) * cos(radians(Pitch));
        front.y = sin(radians(Pitch));
        front.z = sin(radians(Yaw)) * cos(radians(Pitch));

        Front = normalize(front);
        Right = normalize(cross(Front, WorldUp)); // 叉乘使用右手坐标系 食指第一个参数 中指第二个参数 大拇指结果
        Up = normalize(cross(Right, Front));
    }

    // 自定义LookAt函数 eye 相机位置  center 目标位置  up 上向量
    // 返回观察矩阵
    mat4 CustomLookAt(vec3 eyePos, vec3 targetPos, vec3 up)
    {
        vec3 frontDir = eyePos - targetPos;                // 观察方向
        vec3 rightDir = normalize(cross(up, frontDir));    // 右方向
        vec3 upDir = normalize(cross(frontDir, rightDir)); // 上方向
        mat4 m = mat4();
        m[0] = vec4(frontDir, 0.0f);
        m[1] = vec4(rightDir, 0.0f);
        m[2] = vec4(upDir, 0.0f);
        m[3] = vec4(targetPos, 0.0f);
        return transpose(m);
    }
};

#endif