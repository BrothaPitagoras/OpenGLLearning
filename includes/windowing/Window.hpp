#pragma once

#include <GLFW/glfw3.h>

class Window {
public:

	GLFWwindow* glfw_window;

	unsigned int width;
	unsigned int height;

	float lastX;
	float lastY;
	bool firstMouse;

	Window(const unsigned int width, const unsigned int height);

	void initializeGFLWWithHints();

	GLFWwindow* createWindowWithCallbacks(int window_width, int window_height);

	void setMouseCallback(GLFWcursorposfun callback);

	void setScrollCallback(GLFWscrollfun callback);

	bool pressedKey(int key);

	bool shouldClose();

	void close();

	void captureAndHideCursor();

private:


};

