#pragma once

#include "Eram/Events/Event.h"

#include "Eram/Renderer/CameraController.h"

#include "Eram/Scope/VideoMap.h"

namespace Eram {

	class Scope
	{
	public:
		Scope();
		~Scope();

		void Init();
		void Free();

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
	private:
		CameraController m_CameraController;

		VideoMap m_VideoMap;
		VideoMap m_VideoMap2;
		float m_Rotation = 0.0f;
	};

}