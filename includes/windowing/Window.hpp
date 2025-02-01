#pragma once

#include <includes.h>
#include <GLFW/glfw3.h>
#include <windowing/gui.hpp>

class Window {
public:

	GLFWwindow* glfw_window;

	unsigned int width;
	unsigned int height;

	const char* glsl_version = "#version 460";

	float lastX;
	float lastY;
	bool firstMouse;

	bool captureMouseInput;

	std::unique_ptr<ImGui_Impl> imgui_window;

	Window(const unsigned int width, const unsigned int height);

	void initializeGFLWWithHints();

	GLFWwindow* createWindowWithCallbacks(int window_width, int window_height);

	void setMouseCallback(GLFWcursorposfun callback);

	void setScrollCallback(GLFWscrollfun callback);

	void setKeyboardCallback(GLFWkeyfun callback);

	bool pressedKey(int key);

	bool shouldClose();

	void close();

	void captureAndHideCursor();

	void stopHidingCursor();

private:


};

