#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>

using namespace Engine::Core;

void Application::Run()
{
	if (Init())
	{
		Loop();
		Terminate();
	}
}

bool Application::Init()
{
	// GLFW
	m_Window.Init();
	m_Window.SetVsync(true);

	// ImGui
	IMGUI_CHECKVERSION();
	ImGuiContext* context = ImGui::CreateContext();
	ImGui::SetCurrentContext(context);
	ImGui::GetIO().IniFilename = nullptr;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_Window.GetGlfwWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	return true;
}

void Application::Loop()
{
	while (!m_Window.ShouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.31f, 0.37f, 0.56f, 1.0f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		m_Window.Update();
	}
}

void Application::Terminate()
{
	// ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::Shutdown();
	ImGui::DestroyContext();

	// GLFW
	m_Window.Terminate();
}
