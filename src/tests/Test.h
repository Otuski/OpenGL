#pragma once

#include <vector>
#include <string>
#include <functional>

namespace test {

	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& m_CurrentTestPointer);

		void OnImGuiRender() override;
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}