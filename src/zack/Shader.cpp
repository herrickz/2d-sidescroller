
#include <zack/Shader.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(
    const std::string &vertexShaderSourcePath,
    const std::string &fragmentShaderSourcePath
) {

    std::ifstream vertexShaderFileStream(vertexShaderSourcePath.c_str());
    std::ifstream fragmentShaderFileStream(fragmentShaderSourcePath.c_str());

    if(!vertexShaderFileStream) {
        std::cout << "Could not find: " << vertexShaderSourcePath << std::endl;
        return;
    }

    if(!fragmentShaderFileStream) {
        std::cout << "Could not find: " << fragmentShaderSourcePath << std::endl;
        return;
    }

    std::stringstream ss;

    ss << vertexShaderFileStream.rdbuf();
    vertexShaderFileStream.close();

    const std::string vertexShaderSourceString = ss.str();
    const char *vertexShaderSource = vertexShaderSourceString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::cout << vertexShaderSourceString << std::endl;
    }

    ss.str("");
    ss << fragmentShaderFileStream.rdbuf();

    const std::string fragmentShaderSourceString = ss.str();
    const char *fragmentShaderSource = fragmentShaderSourceString.c_str();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::cout << fragmentShaderSourceString << std::endl;
    }

    mShaderProgramId = glCreateProgram();
    glAttachShader(mShaderProgramId, vertexShader);
    glAttachShader(mShaderProgramId, fragmentShader);
    glLinkProgram(mShaderProgramId);

    glGetProgramiv(mShaderProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mShaderProgramId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(mShaderProgramId);
}

void Shader::use() {
    glUseProgram(mShaderProgramId);
}

uint32_t Shader::getShaderProgramId() {
    return mShaderProgramId;
}
