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
		// Í¨¹ý Shader ¼Ì³Ð
		virtual void setBool(const std::string& name, bool value) const override;
		virtual void setInt(const std::string& name, int value) const override;
		virtual void setFloat(const std::string& name, float value) const override;
		virtual void setVec2(const std::string& name, const glm::vec2& value) const override;
		virtual void setVec2(const std::string& name, float x, float y) const override;
		virtual void setVec3(const std::string& name, const glm::vec3& value) const override;
		virtual void setVec3(const std::string& name, float x, float y, float z) const override;
		virtual void setVec4(const std::string& name, const glm::vec4& value) const override;
		virtual void setVec4(const std::string& name, float x, float y, float z, float w) const override;
		virtual void setMat2(const std::string& name, const glm::mat2& mat) const override;
		virtual void setMat3(const std::string& name, const glm::mat3& mat) const override;
		virtual void setMat4(const std::string& name, const glm::mat4& mat) const override;
	private:
		void checkCompileErrors(uint32_t shader, std::string type) const;
		std::string ReadFile(const std::string& path);
	private:
		unsigned int m_RendererID;
		std::string m_Name;

		
	};
}