#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <zack/Shader.h>
#include <zack/TexturedSquare.h>
#include <zack/Player.h>
#include <zack/Direction.h>

#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

Camera camera;
Player *player;

float lastFrameTime = glfwGetTime();
float deltaTime = 0.0f;

int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("resources/shaders/shader.vs", "resources/shaders/shader.fs");

    std::vector<TexturedSquare*> squares;
    std::vector<glm::vec3> cubePositions;

    for(int i = 0; i < 10; i++) {
        cubePositions.push_back(
            glm::vec3( i,  -1.0f,  -5.0f)
        );
    }

    int i = 0;

    for(auto position : cubePositions) {

        std::string image = "resources/textures/bricks2.jpg";

        squares.push_back(
            new TexturedSquare(
                image,
                &shader,
                camera,
                position
            )
        );

        i++;
    }

    player = new Player(camera, &shader);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(auto square : squares) {
            square->draw();
        }

        glm::vec3 cameraPosition = camera.GetPosition();

        player->OnUpdate(deltaTime);
        player->Draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_A)) {
        player->ProcessKeyboard(0, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        player->ProcessKeyboard(1, deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE)) {
        player->OnJump();
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}