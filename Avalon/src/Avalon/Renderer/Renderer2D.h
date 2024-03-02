#pragma once

#include "Avalon/Core/Base.h"

#include "Avalon/Renderer/Texture.h"
#include "Avalon/Renderer/SubTexture2D.h"

#include "Avalon/Renderer/OrthographicCamera.h"

#include <glm/glm.hpp>

namespace Avalon
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, 
			const glm::vec2& size, 
			const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, 
			const glm::vec2& size, 
			const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, 
			const glm::vec2& size, 
			const Ref<Texture2D>& texture, 
			F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, 
			const glm::vec2& size, 
			const Ref<Texture2D>& texture, 
			F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position,
			const glm::vec2& size,
			const Ref<SubTexture2D>& subtexture,
			F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position,
			const glm::vec2& size,
			const Ref<SubTexture2D>& subtexture,
			F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Rotated Quad
		static void DrawRotatedQuad(const glm::vec2& position, 
			const glm::vec2& size, 
			F32 rotation,
			const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, 
			const glm::vec2& size, 
			F32 rotation,
			const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, 
			const glm::vec2& size, 
			F32 rotation,
			const Ref<Texture2D>& texture, 
			F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, 
			const glm::vec2& size, 
			F32 rotation,
			const Ref<Texture2D>& texture, 
			F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec2& position,
			const glm::vec2& size,
			F32 rotation,
			const Ref<SubTexture2D>& subtexture,
			F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position,
			const glm::vec2& size,
			F32 rotation,
			const Ref<SubTexture2D>& subtexture,
			F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		struct Statistics
		{
			U32 DrawCalls = 0;
			U32 QuadCount = 0;

			U32 GetTotalVertexCount() { return QuadCount * 4; }
			U32 GetTotalIndexCount() { return QuadCount * 6; }
		};

		static void ResetStats();
		static Statistics GetStats();

	private:
		static void FlushAndReset();
	};
}