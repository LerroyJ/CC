#include "ccpch.h"
#include "OpenGLTexture2D.h"

#include <glad/glad.h>
#include "stb_image.h"
namespace CEngine {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path), m_RendererID(loadTexture())
	{
	}
    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_RendererID);
    }
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	uint32_t OpenGLTexture2D::loadTexture(bool gammaCorrection)
	{
        unsigned int textureID;
        glGenTextures(1, &textureID);

        stbi_set_flip_vertically_on_load(1);
        int nrComponents;
        unsigned char* data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &nrComponents, 0);
        if (data)
        {
            GLenum internalFormat;
            GLenum dataFormat;
            if (nrComponents == 1)
            {
                internalFormat = dataFormat = GL_RED;
            }
            else if (nrComponents == 3)
            {
                internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
                dataFormat = GL_RGB;
            }
            else if (nrComponents == 4)
            {
                internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
                dataFormat = GL_RGBA;
            }

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_image_free(data);
        }
        else
        {
            CC_CORE_ERROR("Texture failed to load at path: {0}", m_Path);
            stbi_image_free(data);
        }
        
        return textureID;
	}
}