#pragma once

#include <string>
#include <zack/Shader.h>

class TexturedSquare {

public:

    /*
     * @param imagePath: Path to image data to be loaded
    */
    TexturedSquare(
        const std::string &imagePath,
        Shader *shader
    );

    void draw();

private:
    uint32_t mTextureId;
    uint32_t mVAO;

    Shader *mShader;
};