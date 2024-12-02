
#include <includes.h>
#include <windowing/windowing.hpp>
#include <shadering/shadering.hpp>
#include <shadering/VAO.hpp>
#include <shadering/Shader.hpp>
#include <render/renderObjects/renderObject.hpp>


void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

std::vector<float> vertices {
    // first triangle
    -0.5f,  -0.5f, 0.0f,// 1.0f, 0.0f, 0.0f,  // bottom left
    0.5f, -0.5f, 0.0f, //0.0f, 1.0f, 0.0f, // bottom right
   0.0f,  0.5f, 0.0f  //0.0f, 0.0f, 1.0f // top
};

int main()
{
    
    windowing::initializeGFLWWithHints();

    GLFWwindow* window = windowing::createWindowWithCallback(SCR_WIDTH, SCR_HEIGHT);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader = Shader("C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/vertex.glsl", "C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/frag.glsl");
    VAO vaoOne = VAO();

    renderObject triangle1 = renderObject(&vaoOne, vertices);
    // Render Loop
    // ----------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        // Input
        // -----------------
        processInput(window);

        // Render
        // -----------------

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //Gets the variable uniform declared on the shader
        shader.use();
        // to change the uniform u must use the shader program before, because it changes the uniform on the active shader program
        vaoOne.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
     //------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

