
#include <includes.h>
#include <windowing/Window.hpp>
#include <shadering/shadering.hpp>
#include <shadering/VAO.hpp>
#include <shadering/Shader.hpp>
#include <render/renderObjects/renderObject.hpp>
#include <render/Camera.hpp>
#include <shadering/Texture.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void processInput(Window* window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//std::vector<glm::vec3> cubePositions = {
//    glm::vec3(0.0f,  0.0f,  0.0f),
//    glm::vec3(2.0f,  5.0f, -15.0f),
//    glm::vec3(-1.5f, -2.2f, -2.5f),
//    glm::vec3(-3.8f, -2.0f, -12.3f),
//    glm::vec3(2.4f, -0.4f, -3.5f),
//    glm::vec3(-1.7f,  3.0f, -7.5f),
//    glm::vec3(1.3f, -2.0f, -2.5f),
//    glm::vec3(1.5f,  2.0f, -2.5f),
//    glm::vec3(1.5f,  0.2f, -1.5f),
//    glm::vec3(-1.3f,  1.0f, -1.5f)
//};

std::vector<float> vertices {

    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

//timing fps
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//std::vector<unsigned int> indices {
//        0, 1, 3, // first triangle
//        1, 2, 3  // second triangle
//};

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT);

    window.setMouseCallback(mouse_callback);
    window.setScrollCallback(scroll_callback);

    window.captureAndHideCursor();

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader lightingShader = Shader("C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/objectVertex.glsl", "C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/objectFrag.glsl");
    Shader lightCubeShader = Shader("C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/lightVertex.glsl", "C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/lightFrag.glsl");
    VAO vaoOne = VAO();

    renderObject object = renderObject(&vaoOne, &vertices, nullptr, true, false, false);

    VAO lightVao = VAO();
    renderObject lightObject = renderObject(&lightVao, &vertices, nullptr, true, false, false);

    // LOADING TEXTURE
    //Texture texture1 = Texture("C:/Games/OpenGLTutorial/OpenGLTutorial/textures/container.jpg");
    //Texture texture2 = Texture("C:/Games/OpenGLTutorial/OpenGLTutorial/textures/awesomeface.png");

    //shader.setUniformInt("texture1", texture1.texture);
    //shader.setUniformInt("texture2", texture2.texture);
    // STOP LOADING TEXTURE
    
    glEnable(GL_DEPTH_TEST);

    // Render Loop
    // ----------------------------------------------
    while (!window.shouldClose())
    {
        //pre frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        // -----------------
        processInput(&window);

        // Render
        // -----------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //Bind the textures
        //Texture::bind(GL_TEXTURE1, texture1.texture);
        //Texture::bind(GL_TEXTURE2, texture2.texture);
        float yoffset = cos(glm::radians(90.0f) * glfwGetTime());
        float xoffset = sin(glm::radians(90.0f) * glfwGetTime());

        glm::vec3 variableLightPos = glm::vec3(xoffset, yoffset, lightPos.z);
        //activate shader
        lightingShader.use();
        vaoOne.bind();
        lightingShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        lightingShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("lightPos", variableLightPos);
        lightingShader.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) window.width / (float) window.height, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera view transformation
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("view", view);

        //render the boxes
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);


        model = glm::mat4(1.0f);
        model = glm::translate(model, variableLightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightCubeShader.setMat4("model", model);
            
        lightVao.bind();
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());


        // to change the uniform u must use the shader program before, because it changes the uniform on the active shader program
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window.glfw_window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
     //------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(Window* window)
{
    if (window->pressedKey(GLFW_KEY_ESCAPE))
        window->close();

    if (window->pressedKey(GLFW_KEY_SPACE))
        camera.ProcessKeyboard(UP, deltaTime);
    if (window->pressedKey(GLFW_KEY_LEFT_CONTROL))
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (window->pressedKey(GLFW_KEY_W))
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (window->pressedKey(GLFW_KEY_S))
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (window->pressedKey(GLFW_KEY_D))
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (window->pressedKey(GLFW_KEY_A))
        camera.ProcessKeyboard(LEFT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    Window* myWindowType = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

    if (myWindowType->firstMouse)
    {
        myWindowType->lastX = xpos;
        myWindowType->lastY = ypos;
        myWindowType->firstMouse = false;
    }

    float xoffset = xpos - myWindowType->lastX;
    float yoffset = myWindowType->lastY - ypos; // reversed since y-coordinates go from bottom to top

    myWindowType->lastX = xpos;
    myWindowType->lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}



