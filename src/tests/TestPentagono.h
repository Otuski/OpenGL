#pragma once

#include "Test.h"

namespace test {
	class TestPentagono : public Test
	{
	public:
		TestPentagono();
		~TestPentagono();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_PentagonoColor[4];
	};
}
