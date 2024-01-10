#pragma once
#include "entt/entt.hpp"
//#include "scene/Entity.h"
#include "core/Log.h"
#include "core/UUID.h"
#include "render/Render2D.h"
#include "render/Texture2D.h"
#include "rapidXML/rapidxml.hpp"
#include <map>
#include <tchar.h>
#include "Render/TextureLibrary.h"
#include "ImGui/ImGuiLayer.h"
using namespace rapidxml;
using namespace std;
#include "core/Timestep.h"
namespace ALStore{
class Entity;
static std::map<std::string, int> localMap;

class Scene
{
public:
	Scene();
	~Scene();

	Entity CreateEntity(const std::string& name);
	Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
	void DestroyEntity(Entity entity);
	// TEMP
	entt::registry& Reg() { return m_Registry; }
	void LoadXML(std::string filePath);
	void OnViewportResize(uint32_t width, uint32_t height);
	void drawMap(); void drawRoads();
	void OnUpdate(Timestep ts);	
	glm::vec2 m_size;
	glm::vec3 m_position;
	glm::vec4 tintColor = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec2 coords = { 0.0f, 0.0f };
private:
	template<typename T>
	void OnComponentAdded(Entity entity, T& component);

private:
	entt::registry m_Registry;
	xml_document<> doc; xml_node<>* root_node;
	TextureLibrary s_TextureLibrary;
	std::shared_ptr<Texture2D> m_SpriteSheet;
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	Render2D draw;
	int divisor, dividend, quotient, remainder;
	glm::vec2 getCoords(int dividend, int divisor);
	size_t m_MapWidth, m_MapHeight;
	ImGuiLayer* s_imguiLayer;
	friend class Entity;
	friend class XMLClass;
};
}