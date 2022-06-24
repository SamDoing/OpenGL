#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>

namespace test {
	class Test
	{
	public:
		Test(){}
		virtual ~Test(){}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};

	class TestMenu : public Test
	{
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Test;
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		template<typename T>
		void RegisterTest(const std::string& name) 
		{
			std::cout << "Registring a test " << name << std::endl;
			m_Test.push_back(std::make_pair(name, []() {return new T(); }));
		}
		void onImGuiRender() override;
	};
}

