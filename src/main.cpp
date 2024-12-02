
#include <includes.h>
#include <windowing/windowing.hpp>
#include <shadering/shadering.hpp>
#include <shadering/VAO.hpp>
#include <render/renderObjects/renderObject.hpp>


void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

std::vector<float> vertices {
    // first triangle
    -0.5f,  -0.5f, 0.0f,  // bottom left
    0.5f, -0.5f, 0.0f,  // bottom right
   0.0f,  0.5f, 0.0f,  // top
};

//std::vector<float> vertices2{
//    // second triangle
//     0.5f, -0.5f, 0.0f,  // bottom right
//    -0.5f, -0.5f, 0.0f,  // bottom left
//    -0.5f,  0.5f, 0.0f   // top left
//};

//std::vector<int> indices{
//    0, 1, 3,
//    1, 2, 3
//};

//const char* vertexShaderSource =    "#version 460 core\n"
//                                    "layout(location = 0) in vec3 aPos;\n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//                                    "}\0";
//
//const char* fragmentShaderSource =  "#version 460 core\n"
//                                    "out vec4 FragColor;\n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                    "}\0";

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

    unsigned int shaderProgram = shadering::linkShaderProgram("C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/vertex.glsl", "C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/frag.glsl");
    //unsigned int shaderProgram2 = shadering::linkShaderProgram("C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/vertex.glsl", "C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/frag2.glsl");
    VAO vaoOne = VAO();
    //VAO vaoTwo= VAO();

    renderObject triangle1 = renderObject(&vaoOne, vertices);
    //renderObject triangle2 = renderObject(&vaoTwo, vertices2);
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

        float timeValue = glfwGetTime();
        float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;

        //Gets the variable uniform declared on the shader
        int vertexColorUniform = glGetUniformLocation(shaderProgram, "ourColor");



        glUseProgram(shaderProgram);
        // to change the uniform u must use the shader program before, because it changes the uniform on the active shader program
        glUniform4f(vertexColorUniform, 0.0f, greenValue, 0.0f, 1.0f);
        vaoOne.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glUseProgram(shaderProgram2);
        //vaoTwo.bind();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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

