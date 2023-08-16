#include "ccpch.h"
#include "Renderer3D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
namespace CEngine {
	struct Renderer3DData {
		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
	};
	static Renderer3DData s_Data;

	void Renderer3D::Init() {
        s_Data.shader = Shader::Create("CubeShader", "assets/shaders/CubeShader.vs", "assets/shaders/CubeShader.frag");

		s_Data.vertexArray = VertexArray::Create();

        float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
        vertexBuffer->SetLayout({
            {"Position", ShaderDataType::Float3},
            {"TexCoords", ShaderDataType::Float2}
            });
        s_Data.vertexArray->AddVertexBuffer(vertexBuffer);
	}
	void Renderer3D::ShutDow() {
		
	}

	void Renderer3D::BeginScene(const PerspectiveCamera& camera) {
		s_Data.shader->Bind();
		s_Data.shader->setMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}
	void Renderer3D::EndScene() {
        
        Flush();
	}
	void Renderer3D::Flush() {
        RenderCommand::DrawArrays(36);
	}
    static float rotation = 0;
	void Renderer3D::DrawCube(float ts) {
        rotation += ts * 51.0f;
        glm::mat4 model = glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(1, 1, 1));
        s_Data.shader->setMat4("u_Model", model);
	}
}