#include "pch.h"
#include "Window.h"
#include "core/core.h"
#include "glm/glm/glm.hpp"
#include "Events/Event.h"
#include "core/KeyCodes.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace ALStore {

	Window::Window() {}
	Window::~Window(){ glfwDestroyWindow(m_gWindow); }
	bool Window::init() {
		if (!glfwInit()) AL_CORE_CRITICAL("GLFW FAILED");
		//glfwSetErrorCallback(GLFWErrorCallback);
		m_gWindow = glfwCreateWindow(800, 600, "ALAvery", NULL, NULL);
		if (!m_gWindow) { AL_CORE_CRITICAL("GLFW WINDOW CREATION FAILED"); return false; }
		glfwMakeContextCurrent(m_gWindow);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AL_CORE_ASSERT(status, "Failed to initialize Glad!");
		AL_INFO("Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// tell GL to only draw onto a pixel if the shape is closer to the viewer
		//////////////////glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
		glfwSwapInterval(1); //SetVSync(true);
		glfwSetWindowUserPointer(m_gWindow, &m_Data);
		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_gWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_gWindow, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_gWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_gWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_gWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_gWindow, [](GLFWwindow* window, double xPos, double yPos)
			{//https://stackoverflow.com/questions/29356783/glfwsetcursorposcallback-to-function-in-another-class
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
		return true;
	}

	void Window::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_gWindow);
	}
	void Window::OnShutdown() { glfwTerminate(); }
}