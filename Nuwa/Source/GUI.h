#pragma once
#include "imgui/imgui.h"
#include "imgui/ImGuizmo.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <string>

namespace Nuwa
{
	void InitImGui(GLFWwindow* window, std::string glslVersionStr = "#version 410");

	void BeginImGui();	
	void RenderImGui(GLFWwindow* window, ImVec4 clearColor);
	void EndImGui();

}