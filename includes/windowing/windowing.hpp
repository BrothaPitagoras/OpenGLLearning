#pragma once

namespace windowing {


	void initializeGFLWWithHints();

	GLFWwindow* createWindowWithCallback(int window_width, int window_height);


}

