
#include <zack/TexturedSquare.h>

#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

TexturedSquare::TexturedSquare(
    const std::string &imagePath,
    Shader *shader
) {

    mShader = shader;

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    // starts at byte 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    // starts at byte 3
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture
    // -------------------------

    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}

void TexturedSquare::draw() {

    // bind Texture
    glBindTexture(GL_TEXTURE_2D, mTextureId);

    // render container
    mShader->use();
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}