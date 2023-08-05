#pragma once
#include "glm/glm.hpp"

namespace CEngine {
    class Shader
    {
    public:
        virtual ~Shader();
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual uint32_t GetID() const = 0;
        // setting
        virtual void setBool(const std::string& name, bool value) const = 0;
        virtual void setInt(const std::string& name, int value) const = 0;
        virtual void setFloat(const std::string& name, float value) const = 0;
        virtual void setVec2(const std::string& name, const glm::vec2& value) const = 0;
        virtual void setVec2(const std::string& name, float x, float y) const = 0;
        virtual void setVec3(const std::string& name, const glm::vec3& value) const = 0;
        virtual void setVec3(const std::string& name, float x, float y, float z) const = 0;
        virtual void setVec4(const std::string& name, const glm::vec4& value) const = 0;
        virtual void setVec4(const std::string& name, float x, float y, float z, float w) = 0;
        virtual void setMat2(const std::string& name, const glm::mat2& mat) const = 0;
        virtual void setMat3(const std::string& name, const glm::mat3& mat) const = 0;
        virtual void setMat4(const std::string& name, const glm::mat4& mat) const = 0;     
        static Shader* Create(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    private:
        virtual void checkCompileErrors(uint32_t shader, std::string type) const = 0;
    };
}