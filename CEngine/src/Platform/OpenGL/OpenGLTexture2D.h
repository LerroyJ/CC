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
		inline virtual uint32_t GetWidth() const override { return m_Width; }
		inline virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot) const override;
	private:
		uint32_t loadTexture(bool gammaCorrection = false);
		std::string m_Path;
		int m_Width, m_Height;
		uint32_t m_RendererID;
	};
}

