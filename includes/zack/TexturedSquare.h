#pragma once

#include <string>
#include <zack/Shader.h>
#include <zack/Camera.h>

class TexturedSquare {

public:

    /*
     * @param imagePath: Path to image data to be loaded
    */
    TexturedSquare(
        const std::string &imagePath,
        Shader *shader,
        Camera &camera,
        glm::vec3 initialPosition
    );

    void draw();

    void SetPosition(glm::vec3 position);

private:
    uint32_t mTextureId;
    uint32_t mVAO;

    glm::vec3 mPosition;

    Shader *mShader;
    Camera &mCamera;
};