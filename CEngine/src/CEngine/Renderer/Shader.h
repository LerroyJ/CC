#pragma once
namespace CEngine {
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetID() const = 0;

        static Ref<Shader> Create(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    };
}