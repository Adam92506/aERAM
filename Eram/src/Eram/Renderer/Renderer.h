#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

namespace Eram
{

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		
		static void ReloadShaders();

		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene(const Camera& camera);
		static void EndScene();

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Unique<SceneData> s_SceneData;
		static Ref<Shader> s_QuadShader;
	};

}