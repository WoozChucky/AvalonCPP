#pragma once

#include <Common/Types.h>

namespace Avalon
{

    enum class ImageFormat
    {
        None = 0,
        R8,
        RGB8,
        RGBA8,
        RGBA32F
    };

    struct TextureSpecification
    {
        uint32_t Width = 1;
        uint32_t Height = 1;
        ImageFormat Format = ImageFormat::RGBA8;
        bool GenerateMips = true;
    };

    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual const TextureSpecification& GetSpecification() const = 0;

        virtual U32 GetWidth() const = 0;
        virtual U32 GetHeight() const = 0;
        virtual U32 GetRendererID() const = 0;

        virtual const std::string& GetPath() const = 0;

        virtual void SetData(void* data, U32 size) = 0;

        virtual void Bind(U32 slot = 0) const = 0;
        virtual void Unbind(U32 slot = 0) const = 0;

        virtual bool IsLoaded() const = 0;

        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& path) { return CreateRef<Texture2D>(path); }
        static Ref<Texture2D> Create(const TextureSpecification& specification) { return CreateRef<Texture2D>(specification); }

    public:
        Texture2D(const std::string& path);
        Texture2D(const TextureSpecification& specification);

        virtual ~Texture2D();

        virtual const TextureSpecification& GetSpecification() const override { return m_Specification; }

        virtual U32 GetWidth() const override { return m_Width; }
        virtual U32 GetHeight() const override { return m_Height; }
        virtual U32 GetRendererID() const override { return m_RendererID; }

        virtual const std::string& GetPath() const override { return m_Path; }

        virtual void SetData(void* data, U32 size) override;

        virtual void Bind(U32 slot = 0) const override;
        virtual void Unbind(U32 slot = 0) const override;

        virtual bool IsLoaded() const override { return m_IsLoaded; }

        virtual bool operator==(const Texture& other) const override
        {
            return m_RendererID == ((Texture2D&)other).m_RendererID;
        }
    private:
        TextureSpecification m_Specification;

        std::string m_Path;
        bool m_IsLoaded = false;
        U32 m_Width, m_Height;
        U32 m_RendererID;
        U32 m_InternalFormat, m_DataFormat;
    };
}