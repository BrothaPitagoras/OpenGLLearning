
#include <includes.h>
#include <windowing/Window.hpp>
#include <windowing/gui.hpp>
#include <shadering/shadering.hpp>
#include <shadering/VAO.hpp>
#include <shadering/Shader.hpp>
#include <render/renderObjects/renderObject.hpp>
#include <render/Camera.hpp>
#include <shadering/Texture.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <data/data.hpp>
#include <stb_image.h>
#include <model/Model.hpp>


void custom_keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(Window* window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

//timing fps
float deltaTime = 0.0f;
float lastFrame = 0.0f;


//std::vector<unsigned int> indices {
//        0, 1, 3, // first triangle
//        1, 2, 3  // second triangle
//};


int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT);

    window.setMouseCallback(mouse_callback);
    window.setScrollCallback(scroll_callback);
    window.setKeyboardCallback(custom_keyboard_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    Shader lightingShader = Shader("C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/objectVertex.glsl", "C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/objectFrag.glsl");
    //Shader lightCubeShader = Shader("C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/lightVertex.glsl", "C:/Games/OpenGLTutorial/OpenGLTutorial/shaders/lightFrag.glsl");

    Model backpackModel("C:/Games/OpenGLTutorial/OpenGLTutorial/textures/backpack/backpack.obj");

    // Render Loop
    // ----------------------------------------------
    while (!window.shouldClose())
    {
        //pre frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        processInput(&window);
        
        // Render
        // -----------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //activate shader
        lightingShader.use();
        
        ////set material uniforms
        //lightingShader.setUniformFloat("material.shininess", 32.0f);

        // set dirLight
        lightingShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        lightingShader.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        lightingShader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
        lightingShader.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

        //set spotlight
        lightingShader.setVec3("spotLight.position", camera.Position);
        lightingShader.setVec3("spotLight.direction", camera.Front);
        lightingShader.setUniformFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setUniformFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        lightingShader.setVec3("spotLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        lightingShader.setVec3("spotLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        lightingShader.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setUniformFloat("spotLight.constant", 1.0f);
        lightingShader.setUniformFloat("spotLight.linear", 0.09f);
        lightingShader.setUniformFloat("spotLight.quadratic", 0.032f);

        //set pointLights
        //for (unsigned int i = 0; i < pointLightPositions.size(); i++)
        //{
        //    lightingShader.setVec3(std::format("pointLights[{}].position", i), pointLightPositions.at(i));
        //    lightingShader.setVec3(std::format("pointLights[{}].ambient", i), glm::vec3(0.2f, 0.2f, 0.2f));
        //    lightingShader.setVec3(std::format("pointLights[{}].diffuse", i), glm::vec3(0.5f, 0.5f, 0.5f));
        //    lightingShader.setVec3(std::format("pointLights[{}].specular", i), glm::vec3(1.0f, 1.0f, 1.0f));
        //    lightingShader.setUniformFloat(std::format("pointLights[{}].constant", i), 1.0f);
        //    lightingShader.setUniformFloat(std::format("pointLights[{}].linear", i), 0.09f);
        //    lightingShader.setUniformFloat(std::format("pointLights[{}].quadratic", i), 0.032f);
        //}
        

        lightingShader.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) window.width / (float) window.height, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera view transformation
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);
        backpackModel.Draw(lightingShader);
        //render the boxes

        //Imgui related window stuff;
        window.imgui_window->NewFrame();
        window.imgui_window->Update();
        window.imgui_window->Render();

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
void processInput(Window* myWindowType)
{
    ImGuiIO& io = ImGui::GetIO();

    if (io.WantCaptureKeyboard)
    {
        return;
    }

    if (myWindowType->pressedKey(GLFW_KEY_ESCAPE))
        myWindowType->close();
    
    if (ImGui_Data::control_light)
    {
        if (myWindowType->pressedKey(GLFW_KEY_DOWN))
            ImGui_Data::lightPosition_.z += ImGui_Data::model_mov_speed_factor * deltaTime;
        if (myWindowType->pressedKey(GLFW_KEY_UP))
            ImGui_Data::lightPosition_.z -= ImGui_Data::model_mov_speed_factor * deltaTime;
        if (myWindowType->pressedKey(GLFW_KEY_RIGHT))
            ImGui_Data::lightPosition_.x += ImGui_Data::model_mov_speed_factor * deltaTime;
        if (myWindowType->pressedKey(GLFW_KEY_LEFT))
            ImGui_Data::lightPosition_.x -= ImGui_Data::model_mov_speed_factor * deltaTime;
        if (myWindowType->pressedKey(GLFW_KEY_RIGHT_CONTROL))
            ImGui_Data::lightPosition_.y -= ImGui_Data::model_mov_speed_factor * deltaTime;
        if (myWindowType->pressedKey(GLFW_KEY_RIGHT_SHIFT))
            ImGui_Data::lightPosition_.y += ImGui_Data::model_mov_speed_factor * deltaTime;
    }

    if (myWindowType->pressedKey(GLFW_KEY_SPACE))
        camera.ProcessKeyboard(UP, deltaTime);
    if (myWindowType->pressedKey(GLFW_KEY_LEFT_CONTROL))
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (myWindowType->pressedKey(GLFW_KEY_W))
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (myWindowType->pressedKey(GLFW_KEY_S))
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (myWindowType->pressedKey(GLFW_KEY_D))
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (myWindowType->pressedKey(GLFW_KEY_A))
        camera.ProcessKeyboard(LEFT, deltaTime);
}

void custom_keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS) {
        Window* myWindowType = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        myWindowType->captureMouseInput = !myWindowType->captureMouseInput;
        myWindowType->imgui_window->show_main_window = !myWindowType->imgui_window->show_main_window;
        if (myWindowType->captureMouseInput)
        {
            myWindowType->captureAndHideCursor();
        }
        else {
            myWindowType->stopHidingCursor();
        }
    }

    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    
    ImGuiIO& io = ImGui::GetIO();

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

    if (!io.WantCaptureMouse && myWindowType->captureMouseInput)
    {
        camera.ProcessMouseMovement(xoffset, yoffset);
    }

    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    ImGuiIO& io = ImGui::GetIO();

    if (!io.WantCaptureMouse)
    {
        camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }

    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

}



