#pragma once

#include "OrthographicCamera.h"
#include "Shader.h"
#include "Texture2D.h"

namespace ALStore {
	class Render2D
	{
	public:
		Render2D();
		~Render2D();
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		void drawTexture(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor);
		void drawTile(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const glm::vec2& tileCoords, const glm::vec4& tintColor);

	private:
		static void DrawIndexed();
		static void Flush();
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}