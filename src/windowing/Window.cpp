#include <includes.h>
#include <windowing/Window.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(const unsigned int window_width, const unsigned int window_height) {
    width = window_width;
    height = window_height;
    lastX = width / 2.0f;
    lastY = height / 2.0f;
    firstMouse = true;
    Window::initializeGFLWWithHints();
    Window::createWindowWithCallbacks(width, height);

    //This sets a user pointer so that you can access the pointer from anywhere that is using this glfw window (great for callbacks which the signature cant be changed)
    glfwSetWindowUserPointer(glfw_window, this);
}

void Window::initializeGFLWWithHints() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* Window::createWindowWithCallbacks(int window_width, int window_height) {
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    this->glfw_window = window;

    return window;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Window::setMouseCallback(GLFWcursorposfun callback)
{
    glfwSetCursorPosCallback(glfw_window, callback);
}

void Window::setScrollCallback(GLFWscrollfun callback)
{
    glfwSetScrollCallback(glfw_window, callback);
}

bool Window::pressedKey(int key)
{
    return glfwGetKey(glfw_window, key) == GLFW_PRESS;
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(glfw_window);
}

void Window::close()
{
    glfwSetWindowShouldClose(glfw_window, true);
}

void Window::captureAndHideCursor()
{
    // tell GLFW to capture our mouse
    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}