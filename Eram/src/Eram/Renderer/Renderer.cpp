#include "erpch.h"
#include "Renderer.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Eram
{

	struct QuadVertex
	{
		glm::vec3 Postition;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct LineVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	struct RendererData
	{
		// Quads

		const uint32_t MaxQuads = 10000;
		const uint32_t MaxQuadVerticies = MaxQuads * 4;
		const uint32_t MaxQuadIndecies = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> QuadShader;

		uint32_t QuadIndexCount;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		// Lines

		const uint32_t MaxLines = 10000;
		const uint32_t MaxLineVerticies = MaxLines * 2;
		const float LineWidth = 2.0f;

		Ref<VertexArray> LineVertexArray;
		Ref<VertexBuffer> LineVertexBuffer;
		Ref<Shader> LineShader;

		uint32_t LineVertexCount;
		LineVertex* LineVertexBufferBase = nullptr;
		LineVertex* LineVertexBufferPtr = nullptr;
	};

	static RendererData s_Data;

	void Renderer::Init()
	{
		ER_PROFILE_FUNCTION();

		RenderCommand::Init();

		// Quads

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxQuadVerticies * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"}
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxQuadVerticies];

		uint32_t* quadIndecies = new uint32_t[s_Data.MaxQuadIndecies];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxQuadIndecies; i += 6)
		{
			quadIndecies[i + 0] = offset + 0;
			quadIndecies[i + 1] = offset + 1;
			quadIndecies[i + 2] = offset + 2;
			
			quadIndecies[i + 3] = offset + 2;
			quadIndecies[i + 4] = offset + 3;
			quadIndecies[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndecies, s_Data.MaxQuadIndecies);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndecies;

		// Lines

		s_Data.LineVertexArray = VertexArray::Create();

		s_Data.LineVertexBuffer = VertexBuffer::Create(s_Data.MaxLineVerticies * sizeof(LineVertex));
		s_Data.LineVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		});
		s_Data.LineVertexArray->AddVertexBuffer(s_Data.LineVertexBuffer);
		s_Data.LineVertexBufferBase = new LineVertex[s_Data.MaxLineVerticies];

		// Load Shaders

		s_Data.QuadShader = Shader::Create("Eram/assets/shaders/Quad.glsl");
		s_Data.LineShader = Shader::Create("Eram/assets/shaders/Line.glsl");

		ER_INFO("Initialized 2D Renderer");
	}

	void Renderer::Shutdown()
	{
		ER_PROFILE_FUNCTION();

		delete[] s_Data.QuadVertexBufferBase;
		delete[] s_Data.LineVertexBufferBase;
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		ER_PROFILE_FUNCTION();

		s_Data.QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data.LineShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		StartBatch();
	}

	void Renderer::EndScene()
	{
		ER_PROFILE_FUNCTION();

		Flush();
	}

	void Renderer::Flush()
	{
		ER_PROFILE_FUNCTION();

		if (s_Data.QuadIndexCount)
		{
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
			s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

			s_Data.QuadShader->Bind();
			RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		}

		if (s_Data.LineVertexCount)
		{
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.LineVertexBufferPtr - (uint8_t*)s_Data.LineVertexBufferBase);
			s_Data.LineVertexBuffer->SetData(s_Data.LineVertexBufferBase, dataSize);

			s_Data.LineShader->Bind();
			RenderCommand::SetLineWidth(s_Data.LineWidth);
			RenderCommand::DrawLines(s_Data.LineVertexArray, s_Data.LineVertexCount);
		}
	}

	void Renderer::StartBatch()
	{
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.LineVertexCount = 0;
		s_Data.LineVertexBufferPtr = s_Data.LineVertexBufferBase;
	}

	void Renderer::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		ER_PROFILE_FUNCTION();

		if (s_Data.QuadIndexCount >= s_Data.MaxQuadIndecies)
		{
			NextBatch();
		}

		s_Data.QuadVertexBufferPtr->Postition = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Postition = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Postition = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Postition = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;
	}

	void Renderer::DrawLine(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color)
	{
		if (s_Data.LineVertexCount >= s_Data.MaxLineVerticies)
		{
			NextBatch();
		}

		s_Data.LineVertexBufferPtr->Position = { p0.x, p0.y, 0.0f };
		s_Data.LineVertexBufferPtr->Color = color;
		s_Data.LineVertexBufferPtr++;

		s_Data.LineVertexBufferPtr->Position = { p1.x, p1.y, 0.0f };
		s_Data.LineVertexBufferPtr->Color = color;
		s_Data.LineVertexBufferPtr++;

		s_Data.LineVertexCount += 2;
	}

}
