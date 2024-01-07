#pragma once

//#include "Core/Layer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Window/Window.h"

namespace ALStore {

	class ImGuiLayer 
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

	/*  void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e); private:
		*/
		void OnAttach();
		void OnDetach();
		void OnImGuiRender();
		void OnEvent(Event& e);
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
		int ww, wh;
		Window* m_Window;
		GLFWwindow* s_Window;
	};

}