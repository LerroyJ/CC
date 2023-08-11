#pragma once
#include "glm/glm.hpp"
namespace CEngine {
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetID() const = 0;

        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
        static Ref<Shader> Create(const char* path);

        virtual void setBool(const std::string& name, bool value) const = 0;
        virtual void setInt(const std::string& name, int value) const = 0;
        virtual void setFloat(const std::string& name, float value) const = 0;
        virtual void setVec2(const std::string& name, const glm::vec2& value) const = 0;
        virtual void setVec2(const std::string& name, float x, float y) const = 0;
        virtual void setVec3(const std::string& name, const glm::vec3& value) const = 0;
        virtual void setVec3(const std::string& name, float x, float y, float z) const = 0;
        virtual void setVec4(const std::string& name, const glm::vec4& value) const = 0;
        virtual void setVec4(const std::string& name, float x, float y, float z, float w) const = 0;
        virtual void setMat2(const std::string& name, const glm::mat2& mat) const = 0;
        virtual void setMat3(const std::string& name, const glm::mat3& mat) const = 0;
        virtual void setMat4(const std::string& name, const glm::mat4& mat) const = 0;
    };

    class ShaderLibrary {
    public:
        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        Ref<Shader> Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);

        Ref<Shader> Get(const std::string& name);
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}