#pragma once

#include "Eram/Events/Event.h"

namespace Eram {

	class Scope
	{
	public:
		Scope();
		~Scope();

		void Init();
		void Free();

		void Run();

		void OnEvent(Event& e);
	private:

	};

}