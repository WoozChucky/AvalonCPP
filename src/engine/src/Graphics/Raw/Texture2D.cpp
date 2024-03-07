#include <Engine/Graphics/Raw/Texture2D.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Engine/Graphics/stb_image.h>
#include <glad/glad.h>

namespace Avalon
{
    namespace Utils {

        static GLenum AvalonImageFormatToGLDataFormat(ImageFormat format)
        {
            switch (format)
            {
                case ImageFormat::RGB8:  return GL_RGB;
                case ImageFormat::RGBA8: return GL_RGBA;
            }

            return 0;
        }

        static GLenum AvalonImageFormatToGLInternalFormat(ImageFormat format)
        {
            switch (format)
            {
                case ImageFormat::RGB8:  return GL_RGB8;
                case ImageFormat::RGBA8: return GL_RGBA8;
            }

            return 0;
        }

    }

    Texture2D::Texture2D(const TextureSpecification& specification)
            : m_Specification(specification), m_Width(m_Specification.Width), m_Height(m_Specification.Height)
    {
        m_InternalFormat = Utils::AvalonImageFormatToGLInternalFormat(m_Specification.Format);
        m_DataFormat = Utils::AvalonImageFormatToGLDataFormat(m_Specification.Format);

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID); // Bind the newly generated texture object

        // Allocate storage for the texture using glTexImage2D
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    Texture2D::Texture2D(const std::string& path)
            : m_Path(path)
    {

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = nullptr;
        {
            data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }

        if (data)
        {
            m_IsLoaded = true;

            m_Width = width;
            m_Height = height;

            GLenum internalFormat = 0, dataFormat = 0;
            if (channels == 4)
            {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            }
            else if (channels == 3)
            {
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }

            m_InternalFormat = internalFormat;
            m_DataFormat = dataFormat;

            glGenTextures(1, &m_RendererID);
            glBindTexture(GL_TEXTURE_2D, m_RendererID);

            // Allocate storage for the texture using glTexImage2D
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            stbi_image_free(data);
        }
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture2D::SetData(void* data, U32 size)
    {
        U32 bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        glBindTexture(GL_TEXTURE_2D, m_RendererID); // Bind the texture before calling glTexSubImage2D
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void Texture2D::Bind(U32 slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot); // Activate the texture unit
        glBindTexture(GL_TEXTURE_2D, m_RendererID); // Bind the texture to the currently active texture unit
    }

    void Texture2D::Unbind(U32 slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot); // Activate the texture unit
        glBindTexture(GL_TEXTURE_2D, 0); // Bind texture ID 0 to unbind the texture from the currently active texture unit
    }
}