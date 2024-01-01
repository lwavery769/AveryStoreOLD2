#include "Sandbox.h"
#include "core/Log.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "Sandbox.h"
#include "core/KeyCodes.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
bool m_Running = true;
#define BIND_EVENT_FN(x) std::bind(&Sandbox::x, this, std::placeholders::_1)
struct s_LeftMouseBtn {
    bool isPressed = false;
    int x, y;
}; s_LeftMouseBtn m_LeftMouseBtn;

Sandbox::Sandbox() : m_Camera(1.0f, 1.0f, 1.0f, 1.0f) 
{}
Sandbox::~Sandbox() {}
void Sandbox::init() {
    m_Window = std::make_unique<ALStore::Window>();
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    m_Window->init();
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

}
void Sandbox::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
    dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScrolledEvent));
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressedEvent));
    //dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(OnKeyTypedEvent));
    //dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnKeyReleasedEvent));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResizeEvent));
    AL_CORE_TRACE("{0}", e);
}

void Sandbox::run() {
    m_Window->setRunning(true);
    while (m_Window->isRunning()) {
        glClearColor(0.8f, 0.3f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication))
        {
            AL_TRACE(e);
        }
        if (e.IsInCategory(EventCategoryInput))
        {
            AL_TRACE(e);
        }
        m_Window->OnUpdate();

    }
    m_Window->OnShutdown();
}
bool Sandbox::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
    //HZ_PROFILE_FUNCTION("MousePicking");
    if (e.GetMouseButton() == 0) {
        AL_INFO("MOUSE PRESSED{0}", e.GetMouseButton());
    }
    return false;
}
bool Sandbox::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) { return false; }
bool Sandbox::OnMouseMovedEvent(MouseMovedEvent& e) {
    m_mousePos.x = e.GetX(); m_mousePos.y = e.GetY();//HZ_CORE_INFO("{0}, {1}", m_mousePos.x, m_mousePos.y);
    return false;
}
bool Sandbox::OnMouseScrolledEvent(MouseScrolledEvent& e) {
    float y = e.GetYOffset(); AL_CORE_TRACE("Engine: zoom ={0}", m_ZoomLevel);
    m_ZoomLevel = m_ZoomLevel + e.GetYOffset();
    m_ZoomLevel -= e.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_ZoomLevel = std::min(m_ZoomLevel, 14.25f);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return true;
}
bool Sandbox::OnKeyPressedEvent(KeyPressedEvent& e) {
    AL_CORE_TRACE("Engine: key pressed");
    KeyPressedEvent& eventK = (KeyPressedEvent&)e;
    int ts = 1;
    glm::vec3 pos = m_Camera.GetPosition();
    switch (eventK.GetKeyCode()) {
    case HZ_KEY_TAB: AL_TRACE("Tab key is pressed (event)!"); break;
    case HZ_KEY_A: pos.x -= m_CameraTranslationSpeed * ts; break;
    case HZ_KEY_D: pos.x += m_CameraTranslationSpeed * ts; break;
    case HZ_KEY_W: pos.y += m_CameraTranslationSpeed * ts; break;
    case HZ_KEY_S: pos.y -= m_CameraTranslationSpeed * ts; break;
    default:
        break;
    }
    m_Camera.SetPosition(pos);
    //HZ_CORE_TRACE("Engine: New m_CameraPosition ={0}",  glm::to_string(pos) );
    //m_CameraTranslationSpeed = m_ZoomLevel;	//HZ_TRACE("{0}", (char)e.GetKeyCode());
    return false;
}

bool Sandbox::OnWindowResizeEvent(WindowResizeEvent& e) {
    if (e.IsInCategory(EventCategoryApplication))
    {
        AL_TRACE(e);
    }
    if (e.IsInCategory(EventCategoryInput))
    {
        AL_TRACE(e);
    }
    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
        m_Minimized = true;
        return false;
    }

    m_Minimized = false;
    //m_Framebuffer->Resize(e.GetWidth(), e.GetHeight());
   // draw.OnWindowResize(e.GetWidth(), e.GetHeight()); //glViewport

    return false;

}
bool Sandbox::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}