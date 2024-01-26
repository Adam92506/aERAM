#pragma once

#include "erpch.h"

#include "Core.h"

#include "Eram/Events/Event.h"

namespace Eram
{

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "aEram",
			unsigned int width = 1280,
			unsigned int height = 720)
			:Title(title), Width(width), Height(height) {}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Unique<Window> Create(const WindowProps& props = WindowProps());
	};

}