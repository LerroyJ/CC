#include "ccpch.h"
#include "Application.h"
#include "Input.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "imgui.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace CEngine {
	void renderSphere();
	void renderQuad();

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// example quad
		{
			m_Shader.reset(Shader::Create("D:/Users/DELL/source/repos/CEngine/CEngine/shader/test.vs", "D:/Users/DELL/source/repos/CEngine/CEngine/shader/test.frag"));
			glm::mat4 projection = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 model = glm::mat4(1.0f);
			int view_w, view_h;
			auto window = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
			glfwGetWindowSize(window, &view_w, &view_h);
			projection = glm::perspective(glm::radians(45.0f), (float)view_w / (float)view_h, 0.1f, 100.0f);
			glm::vec3 Position = glm::vec3(0, 0, 3);
			glm::vec3 Front = glm::vec3(0, 0, -1);
			glm::vec3 Up = glm::vec3(0, 1, 0);
			view = glm::lookAt(Position, Position + Front, Up);
			
			m_Shader->Bind();
			m_Shader->setMat4("projection", projection);
			m_Shader->setMat4("view", view);
			m_Shader->setMat4("model", model);

			float quadVertices[] = {
				// positions        // texture Coords             //Color
				-0.5f,  0.5,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.2f, 0.1f, 0.7f,
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.7f, 0.1f, 0.0f,
				 0.5,   0.5,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.6f, 0.0f,
				 0.5,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.3f, 0.0f, 0.5f
			};
			uint32_t quadIndices[] = {
					0,1,3,
					0,3,2
			};
			std::shared_ptr<VertexBuffer> m_VertexBuffer;
			m_VertexBuffer.reset(VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
			std::shared_ptr<IndexBuffer> m_IndexBuffer;
			m_IndexBuffer.reset(IndexBuffer::Create(quadIndices, sizeof(quadIndices)/sizeof(uint32_t)));
			BufferLayout layout = {
				{"Position", ShaderDataType::Float3},
				{"Normal", ShaderDataType::Float3},
				{"TexCoord", ShaderDataType::Float2},
				{"Color", ShaderDataType::Float3}
			};
			m_VertexBuffer->SetLayout(layout);

			m_VertexArray.reset(VertexArray::Create());
			m_VertexArray->AddVertexBuffer(m_VertexBuffer);
			m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		}
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		//dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		//dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoe));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::run() {

		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		};
	}

	bool Application::OnWindowClosed(WindowCloseEvent& event) {
		CC_CORE_TRACE("{0}", event);
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event) {
		CC_CORE_TRACE("{0}", event);
		return true;
	}

	bool Application::OnMouseMoe(MouseMovedEvent& event) {
		CC_CORE_TRACE("{0}", event);
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	// renders a 1x1 quad in NDC with manually calculated tangent vectors
// ------------------------------------------------------------------
	unsigned int quadVAO = 0;
	void renderQuad()
	{
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				// positions        // texture Coords
				-0.5f,  0.5,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				 0.5,   0.5,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.5,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			};
			uint32_t quadIndices[] = {
				0,1,3,
				0,3,2
			};
			// vertexbuffer create
			VertexBuffer* quadVBO = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
			IndexBuffer* quadEBO = IndexBuffer::Create(quadIndices, 6);
			// setup plane VAO
			glGenVertexArrays(1, &quadVAO);
			glBindVertexArray(quadVAO);
			quadVBO->Bind();
			quadEBO->Bind();
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		}
		glBindVertexArray(quadVAO);
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	unsigned int sphereVAO = 0;
	unsigned int indexCount;
	void renderSphere()
	{
		if (sphereVAO == 0)
		{
			glGenVertexArrays(1, &sphereVAO);

			unsigned int vbo, ebo;
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			std::vector<glm::vec3> positions;
			std::vector<glm::vec2> uv;
			std::vector<glm::vec3> normals;
			std::vector<unsigned int> indices;

			const unsigned int X_SEGMENTS = 64;
			const unsigned int Y_SEGMENTS = 64;
			const float PI = 3.14159265359f;
			for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
			{
				for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
				{
					float xSegment = (float)x / (float)X_SEGMENTS;
					float ySegment = (float)y / (float)Y_SEGMENTS;
					float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
					float yPos = std::cos(ySegment * PI);
					float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

					positions.push_back(glm::vec3(xPos, yPos, zPos));
					uv.push_back(glm::vec2(xSegment, ySegment));
					normals.push_back(glm::vec3(xPos, yPos, zPos));
				}
			}

			bool oddRow = false;
			for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
			{
				if (!oddRow) // even rows: y == 0, y == 2; and so on
				{
					for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
					{
						indices.push_back(y * (X_SEGMENTS + 1) + x);
						indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					}
				}
				else
				{
					for (int x = X_SEGMENTS; x >= 0; --x)
					{
						indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
						indices.push_back(y * (X_SEGMENTS + 1) + x);
					}
				}
				oddRow = !oddRow;
			}
			indexCount = static_cast<unsigned int>(indices.size());

			std::vector<float> data;
			for (unsigned int i = 0; i < positions.size(); ++i)
			{
				data.push_back(positions[i].x);
				data.push_back(positions[i].y);
				data.push_back(positions[i].z);
				if (normals.size() > 0)
				{
					data.push_back(normals[i].x);
					data.push_back(normals[i].y);
					data.push_back(normals[i].z);
				}
				if (uv.size() > 0)
				{
					data.push_back(uv[i].x);
					data.push_back(uv[i].y);
				}
			}
			glBindVertexArray(sphereVAO);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
			unsigned int stride = (3 + 2 + 3) * sizeof(float);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
		}

		glBindVertexArray(sphereVAO);
		glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
	}
}
