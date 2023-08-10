#pragma once
#include "CEngine/Renderer/Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
namespace CEngine {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& name, const char* vertexPath, const char* fragmentPath, const char* geometryPath);
		OpenGLShader(const char* path);
		virtual ~OpenGLShader();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		inline virtual const std::string& GetName() const override { return m_Name; }

		inline virtual uint32_t GetID() const override { return m_RendererID; }

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setVec2(const std::string& name, const glm::vec2& value) const;
		void setVec2(const std::string& name, float x, float y) const;
		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec3(const std::string& name, float x, float y, float z) const;
		void setVec4(const std::string& name, const glm::vec4& value) const;
		void setVec4(const std::string& name, float x, float y, float z, float w);
		void setMat2(const std::string& name, const glm::mat2& mat) const;
		void setMat3(const std::string& name, const glm::mat3& mat) const;
		void setMat4(const std::string& name, const glm::mat4& mat) const;
	private:
		void checkCompileErrors(uint32_t shader, std::string type) const;
		void Compile();
		std::string ReadFile(const std::string& path);
	private:
		unsigned int m_RendererID;
		std::string m_Name;
	};
}