#include "TestClearColor.h"

#include "../Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestClearColor::TestClearColor()
		:m_ClearColor{ 0.8f, 0.8f, 0.9f, 0.6f }
	{
	}
	TestClearColor::~TestClearColor()
	{
	}
	void TestClearColor::onUpdate(float deltaTime)
	{
	}
	void TestClearColor::onRender()
	{
		GLCALL(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColor::onImGuiRender()
	{
		ImGui::ColorEdit4("Clear color", m_ClearColor);
	}
}