#include "Test.h"
#include "imgui/imgui.h"
namespace test
{
	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{

	}
	TestMenu::~TestMenu()
	{
	}
	void TestMenu::onImGuiRender()
	{
		for(auto& test : m_Test)
		{
			if(ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}
}