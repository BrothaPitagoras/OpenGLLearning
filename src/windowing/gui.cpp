#include <windowing/gui.hpp>

ImGui_Impl::ImGui_Impl(GLFWwindow* window, const char* glsl_version) 
{
    ImGui_Impl::Init(window, glsl_version);
}

ImGui_Impl::~ImGui_Impl() {
    ImGui_Impl::Shutdown();
}

void ImGui_Impl::Init(GLFWwindow* window, const char* glsl_version)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// setup platform/renderer bindings
    ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui::StyleColorsDark();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
}

void ImGui_Impl::NewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGui_Impl::Update() 
{
    ImGuiIO& io = ImGui::GetIO();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    if (show_main_window) {

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::SliderFloat("scale_factor for model: ", &Model::scale_factor, 0.4f, 3.0f);
        ImGui::SliderFloat("mov_speed for model: ", &Model::model_mov_speed_factor, 0.5f, 5.0f);
        ImGui::Checkbox("Control Light", &Model::control_light);
        
        ImGui::Text("Light Pos x:%.2f y:%.2f z:%.2f ", Model::lightPosition_.x , Model::lightPosition_.y, Model::lightPosition_.z);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }
}

void ImGui_Impl::Render() {
    //Render ImGui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGui_Impl::Shutdown() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}