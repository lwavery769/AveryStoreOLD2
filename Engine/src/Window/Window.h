#pragma once
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "Events/Event.h"

namespace ALStore {
	class Window
	{
	public:
		Window();
		~Window();
		bool init();
		void OnUpdate();
		void OnShutdown();
		using EventCallbackFn = std::function<void(Event&)>;
		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

	private:
		bool m_Minimized = false;
		int width, height;

		GLFWwindow* m_gWindow;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}