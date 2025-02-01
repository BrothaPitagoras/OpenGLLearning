#pragma once

#include <includes.h>
#include <data/data.hpp>

class ImGui_Impl
{
public:
	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_main_window = false;

	ImGui_Impl(GLFWwindow* window, const char* glsl_version);
	~ImGui_Impl();

	void Init(GLFWwindow* window, const char* glsl_version);
	void NewFrame();
	virtual void Update();
	void Render();
	void Shutdown();


private:

};