
#include <zack/Player.h>
#include <iostream>

Player::Player(Camera &camera, Shader *shader):
    mTexturedSquare(
        "resources/textures/matrix.jpg",
        shader,
        camera,
        { 0.0f, 0.0f, -5.0f }
    ),
    mCamera(camera),
    mPosition({ 0.0f, 0.0f, -5.0f }) {

}

void Player::Draw() {
    mTexturedSquare.draw();
}

void Player::ProcessKeyboard(int direction, float deltaTime) {
    if(direction == 0) {
        mPosition.x -= mSpeed * deltaTime;
        mTexturedSquare.SetPosition(mPosition);
        mCamera.SetPosition(mPosition.x, mPosition.y);
    }

    if(direction == 1) {
        mPosition.x += mSpeed * deltaTime;
        mTexturedSquare.SetPosition(mPosition);
        mCamera.SetPosition(mPosition.x, mPosition.y);
    }
}

void Player::OnUpdate(float deltaTime) {

    if(mIsJumping) {

        float animationPoint = cos((glm::pi<float>()) * (elapsedJumpTime / totalJumpAnimationTime));

        float currentJumpSpeed = jumpSpeed * animationPoint;

        elapsedJumpTime += deltaTime;

        mPosition.y += currentJumpSpeed * deltaTime;
        mTexturedSquare.SetPosition(mPosition);
        mCamera.SetPosition(mPosition.x, mPosition.y);

        if(elapsedJumpTime > totalJumpAnimationTime) {
            mIsJumping = false;
            elapsedJumpTime = 0.0f;
        }
    }

}

void Player::OnJump() {
    if(mIsJumping == false) {
        mIsJumping = true;
    }
}