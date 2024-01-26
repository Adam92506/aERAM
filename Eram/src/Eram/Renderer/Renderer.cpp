#include "erpch.h"
#include "Renderer.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Eram
{

	Unique<Renderer::SceneData> Renderer::s_SceneData = CreateUnique<Renderer::SceneData>();
	Ref<Shader> Renderer::s_QuadShader;

	void Renderer::Init()
	{
		ER_PROFILE_FUNCTION();

		RenderCommand::Init();
		
		ReloadShaders();
	}

	void Renderer::Shutdown()
	{

	}

	void Renderer::ReloadShaders()
	{
		ER_PROFILE_FUNCTION();

	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
		
	}

}
