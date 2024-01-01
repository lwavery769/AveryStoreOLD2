#pragma once
#include "engine.h"

class Sandbox {
public:
	Sandbox();
	~Sandbox();
	void init();
	void run();

private:
	void OnEvent(Event& e);
		
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool OnMouseMovedEvent(MouseMovedEvent& e);
	bool OnMouseScrolledEvent(MouseScrolledEvent& e);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	//bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	//bool OnKeyTypedEvent(KeyTypedEvent& e);
	bool OnWindowResizeEvent(WindowResizeEvent& e);
	bool OnWindowClose(WindowCloseEvent& e);
	std::unique_ptr<ALStore::Window> m_Window;
	bool m_Minimized = false;
	unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	glm::vec2 m_mousePos = { .75f, .75f };
	ALStore::OrthographicCamera m_Camera;
	float m_AspectRatio = 1.0f;
	float m_ZoomLevel = 1.25f;
	float m_CameraTranslationSpeed = .2250f, m_CameraRotationSpeed = 180.0f;
};