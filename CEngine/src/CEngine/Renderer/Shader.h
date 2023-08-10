#pragma once
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