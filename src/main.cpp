
#include <includes.h>
#include <windowing/windowing.hpp>
#include <shadering/shadering.hpp>
#include <shadering/VAO.hpp>
#include <shadering/Shader.hpp>
#include <render/renderObjects/renderObject.hpp>
#include <shadering/Texture.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

std::vector<float> vertices {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

std::vector<unsigned int> indices {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
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

    renderObject triangle1 = renderObject(&vaoOne, vertices, indices, true, true);



    // LOADING TEXTURE
    Texture texture1 = Texture("C:/Games/OpenGLTutorial/OpenGLTutorial/textures/container.jpg");
    Texture texture2 = Texture("C:/Games/OpenGLTutorial/OpenGLTutorial/textures/awesomeface.png");

    shader.use();
    shader.setUniformInt("texture1", texture1.texture);
    shader.setUniformInt("texture2", texture2.texture);
    // STOP LOADING TEXTURE


    glm::mat4 transMat = glm::mat4(1.0f);
    
    transMat = glm::rotate(transMat, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    transMat = glm::scale(transMat, glm::vec3(0.5, 0.5, 0.5));


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

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //Gets the variable uniform declared on the shader
        Texture::bind(GL_TEXTURE1, texture1.texture);
        Texture::bind(GL_TEXTURE2, texture2.texture);
        shader.use();

        vaoOne.bind();
        // to change the uniform u must use the shader program before, because it changes the uniform on the active shader program
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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

