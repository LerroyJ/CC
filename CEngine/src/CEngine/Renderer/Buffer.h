#pragma once
namespace CEngine {
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case CEngine::ShaderDataType::None:
			return 0;
		case CEngine::ShaderDataType::Float:
			return 4;
		case CEngine::ShaderDataType::Float2:
			return 4 * 2;
		case CEngine::ShaderDataType::Float3:
			return 4 * 3;
		case CEngine::ShaderDataType::Float4:
			return 4 * 4;
		case CEngine::ShaderDataType::Mat3:
			return 4 * 9;
		case CEngine::ShaderDataType::Mat4:
			return 4 * 16;
		case CEngine::ShaderDataType::Int:
			return 4;
		case CEngine::ShaderDataType::Int2:
			return 4 * 2;
		case CEngine::ShaderDataType::Int3:
			return 4 * 3;
		case CEngine::ShaderDataType::Int4:
			return 4 * 4;
		case CEngine::ShaderDataType::Bool:
			return 1;
		}
		CC_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}
	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;
		uint32_t GetComponentCount() const{
			switch (Type)
			{
			case CEngine::ShaderDataType::None:
				return 0;
			case CEngine::ShaderDataType::Float:
				return 1;
			case CEngine::ShaderDataType::Float2:
				return 2;
			case CEngine::ShaderDataType::Float3:
				return 3;
			case CEngine::ShaderDataType::Float4:
				return 4;
			case CEngine::ShaderDataType::Mat3:
				return 3;
			case CEngine::ShaderDataType::Mat4:
				return 4;
			case CEngine::ShaderDataType::Int:
				return 1;
			case CEngine::ShaderDataType::Int2:
				return 2;
			case CEngine::ShaderDataType::Int3:
				return 3;
			case CEngine::ShaderDataType::Int4:
				return 4;
			case CEngine::ShaderDataType::Bool:
				return 1;
			}
			CC_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}

		BufferElement(const std::string& name, ShaderDataType type, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{

		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) 
		{
			CalculateOffsetAndStride();
		}
		const uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	private:
		void CalculateOffsetAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void SetData(const void* data, uint32_t size) const = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
		static Ref<VertexBuffer> Create(uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetCount() const = 0;
		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}