#pragma once
#include "GameState.h"
#include "PlayerController.h"
#include "BallController.h"

class MyGameComponentFactory : public DefaultComponentFactory
{
public:
	MyGameComponentFactory();
	virtual~MyGameComponentFactory();

	virtual Component* createNewComponent(const std::string& type, Entity* owner, const PropertySet& properties);
	virtual Entity* createNewEntity(ComponentFactory* m_componentFactory, const std::string& type, Entity* parent, const PropertySet& properties);
private:
	Ref<GameObject> m_gameObject;
	Ref<Map> m_map;
};