#pragma once

#include <zack/TexturedSquare.h>
#include <zack/Camera.h>
#include <zack/Shader.h>
#include <zack/Direction.h>

class Player {

public:
    Player(Camera &camera, Shader *shader);

    void Draw();

    void OnUpdate(float deltaTime);
    void OnJump();

    void ProcessKeyboard(int direction, float deltaTime);

private:

    TexturedSquare mTexturedSquare;
    bool mIsJumping = false;
    Camera &mCamera;

    glm::vec3 mPosition;

    float mSpeed = 5.0f;

    float jumpSpeed = 5.0f;
    float elapsedJumpTime = 0.0f;
    float totalJumpAnimationTime = 1.5f;
};