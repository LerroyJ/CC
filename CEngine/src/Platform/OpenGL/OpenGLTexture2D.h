#pragma once
#include "CEngine/Renderer/Texture.h"
namespace CEngine{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		~OpenGLTexture2D();
		virtual void SetData(uint32_t size, void* data) override;
		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual void Bind(uint32_t slot) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}
	private:
		uint32_t loadTexture(bool gammaCorrection = false);
		std::string m_Path;
		int m_Width, m_Height;
		uint32_t m_RendererID;
	};
}

