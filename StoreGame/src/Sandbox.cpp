#include <engine.h>
#include "core/Log.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "Window/Window.h"
struct s_LeftMouseBtn {
    bool isPressed = false;
    int x, y;
}; s_LeftMouseBtn m_LeftMouseBtn;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        m_LeftMouseBtn.isPressed = true;
}

int main(int argc, char** argv)
{
	ALStore::Log::Init();
	AL_CORE_INFO("Loger init");
    std::unique_ptr<ALStore::Window> m_Window;
    m_Window = std::make_unique<ALStore::Window>();
    m_Window->init();
/*
    GLFWwindow* m_gWindow;

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
    glfwSwapInterval(1);
    glfwSetMouseButtonCallback(m_gWindow, mouse_button_callback);
    glfwSetCursorPosCallback(m_gWindow, [](GLFWwindow* window, double xPos, double yPos)
        {m_LeftMouseBtn.x = xPos; m_LeftMouseBtn.y = yPos;
        });
 */
    unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    unsigned int indices[3] = { 0, 1, 2 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    bool running = true;
    while (running) {
        glClearColor(0.8f, 0.3f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        m_Window->OnUpdate();

    }

	return 0;
} 