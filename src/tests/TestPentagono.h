#pragma once

#include "Test.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shaders.h"

#include "Texture.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

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
		VertexBuffer m_Vb;
		VertexBufferLayout m_Layout;
		IndexBuffer m_Ib;
		VertexArray m_Va;
		Shader m_Shader;
		Renderer m_Renderer;
		glm::vec3 m_Translation;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_Model;


		float* getPositions();
		unsigned int* getIndices();
	};
}
