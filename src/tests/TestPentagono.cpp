#include "TestPentagono.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shaders.h"

#include "Texture.h"

#include "imgui/imgui.h"

namespace test {
	TestPentagono::TestPentagono()
		:m_PentagonoColor{ 0.2f, 0.3f, 0.5f, 1.0f },
		m_Vb(getPositions(), sizeof(float)*10),
		m_Ib(getIndices(), 9),
		m_Shader("res/shader/Basic.shader"),
		m_Translation(0.0f, 0.0f, 0.0f)
	{

		//setup vertex buffer
		m_Layout.Push<float>(2);

		//setup vertex array
		m_Va.AddBuffer(m_Vb, m_Layout);

		//setup MVP
		m_Proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f); 
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		m_Model = glm::translate(glm::mat4(1.0f), m_Translation);
	}

	float* TestPentagono::getPositions() {
		float positions[10] = {
			 0.0f,   135.0f, //0
			 192.0f,   54.0f, //1
			 120.0f, -81.0f, //2
			-120.0f, -81.0f, //3
			-192.0f,   54.0f  //4
		};
		return positions;
	}

	unsigned int* TestPentagono::getIndices() {
		unsigned int indices[9] = {
			0, 1, 2,
			2, 3, 0,
			0, 3, 4
		};
		return indices;
	}
	

	TestPentagono::~TestPentagono()
	{
	}

	void TestPentagono::OnUpdate(float deltaTime)
	{
	}

	void TestPentagono::OnRender()
	{
		m_Model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 mvp = m_Proj * m_View * m_Model;

		m_Shader.Bind();
		m_Shader.setUniformMat4f("u_MVP", mvp);
		m_Shader.setUniform4f("u_Color", m_PentagonoColor[0], m_PentagonoColor[1], m_PentagonoColor[2], m_PentagonoColor[3]);

		m_Renderer.Clear();
		m_Renderer.Draw(m_Va, m_Ib, m_Shader);
	}

	void TestPentagono::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_PentagonoColor);
		ImGui::DragFloat3("Translation", &m_Translation.x);
		//ImGui::
	}
}