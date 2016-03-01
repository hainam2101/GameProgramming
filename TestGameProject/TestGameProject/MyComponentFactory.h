#pragma once
#include "GameState.h"

class MyComponentFactory :
	public DefaultComponentFactory
{
public:
	MyComponentFactory() : DefaultComponentFactory(), m_playerTexture(), m_enemyTexture(), m_map(0)
	{
		/*m_world = new b2World(vec2(0, 9.81f));
		m_world->SetAllowSleeping(false);*/

		// jottai mycontactlistener scheissea???
	}
	virtual ~MyComponentFactory(){}

	virtual Component* createNewComponent(const std::string& type, Entity* owner, const yam2d::PropertySet& properties)
	{
		// TODO: Implementation... Use now default implementation instead.
		return DefaultComponentFactory::createNewComponent(type, owner, properties);
	}


	virtual Entity* createNewEntity(ComponentFactory* componentFactory, const std::string& type, Entity* parent, const yam2d::PropertySet& properties)
	{
		// TODO: Implementation... Use now default implementation instead.
		return DefaultComponentFactory::createNewEntity(componentFactory, type, parent, properties);
	}
private:
	Ref<Texture> m_playerTexture;
	Ref<Texture>m_enemyTexture;
	Map* m_map;
	Ref<b2World> m_world;
	TmxMap* map = 0;
};

