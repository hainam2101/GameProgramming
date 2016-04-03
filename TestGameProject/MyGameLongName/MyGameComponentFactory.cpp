#include "MyGameComponentFactory.h"

MyGameComponentFactory::MyGameComponentFactory()
	: DefaultComponentFactory(), m_gameObject(0), m_map(0)
{

}

Component* MyGameComponentFactory::createNewComponent(const std::string& type, Entity* owner, const PropertySet& properties)
{
	return DefaultComponentFactory::createNewComponent(type, owner, properties);
}

Entity* MyGameComponentFactory::createNewEntity(ComponentFactory* m_componentFactory, const std::string& type, Entity* parent, const PropertySet& properties)
{
	if ("StaticColliders" == type)
	{
		m_gameObject = new GameObject(parent, properties);
		return m_gameObject;
	}
	else if ("Ball" == type)
	{
		m_gameObject = new GameObject(parent, properties);
		m_gameObject->addComponent(m_componentFactory->createNewComponent("Tile", m_gameObject, properties));
		BallController* ballController = new BallController(m_gameObject);
		m_gameObject->addComponent(ballController);
		m_gameObject->setName("Ball");
		return m_gameObject;
	}
	else if ("Brick" == type)
	{
		m_gameObject = new GameObject(parent, properties);
		m_gameObject->addComponent(m_componentFactory->createNewComponent("Tile", m_gameObject, properties));
		return m_gameObject;
	}
	else if ("PlayerPad" == type)
	{
		m_gameObject = new GameObject(parent, properties);
		m_gameObject->addComponent(m_componentFactory->createNewComponent("Tile", m_gameObject, properties));
		PlayerController* playerController = new PlayerController(m_gameObject);
		m_gameObject->addComponent(playerController);
		m_gameObject->setName("PlayerPad");
		return m_gameObject;
	}

	// Default functionality.
	Entity* res = DefaultComponentFactory::createNewEntity(m_componentFactory, type, parent, properties);
	assert(res != 0);
	return res;
}
MyGameComponentFactory::~MyGameComponentFactory()
{
}