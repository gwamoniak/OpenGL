#include "TestTexture2D.h"
#include "Renderer.h"
#include "BufferLayout.h"
#include "imgui\imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_opengl3.h"
#include "imgui\imgui_impl_glfw.h"


namespace test {
	TestTexture2D::TestTexture2D()
		: m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0),
		m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
			-50.0f,  -50.0f, 0.0f, 0.0f,
			 50.0f,  -50.0f, 1.0f, 0.0f,
			 50.0f,   50.0f, 1.0f, 1.0f,
			-50.0f,   50.0f, 0.0f, 1.0f,
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		BufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

    	m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		m_Texture = std::make_unique<Texture>("res/texture/spiral.png");
		m_Shader->SetUniform1i("u_Texture", 0);

		//m_VAO->Unbind();
		//m_VBO->Unbind();
		//m_IBO->Unbind();
		//m_Shader->Unbind();

	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void test::TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void test::TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_Texture->Bind();

		{
			glm::mat4 modelA = glm::translate(glm::mat4(1.0f), m_TranslationA);
			m_Shader->Bind();
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
			glm::mat4 mvpA = m_proj * m_view * modelA;
			m_Shader->SetUniformMat4f("u_MVP", mvpA);
		}

		{
			glm::mat4 modelB = glm::translate(glm::mat4(1.0f), m_TranslationB);
			m_Shader->Bind();
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
			glm::mat4 mvpB = m_proj * m_view * modelB;
			m_Shader->SetUniformMat4f("u_MVP", mvpB);
		}


	}

	void test::TestTexture2D::OnImGuiRender()
	{
		{
			ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
			ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

	}
}