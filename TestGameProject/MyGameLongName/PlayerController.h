#pragma once

#include "SpriteComponent.h"
#include "GameObject.h"
#include "Input.h"

using namespace yam2d;

class PlayerController : public Component, public Updatable
{
public:
	PlayerController(GameObject* parent);
	virtual~PlayerController();

	virtual void update(float deltaTime);

	GameObject* getGameObject()
	{
		return (GameObject*)getOwner();
	}
	const GameObject* getGameObject() const
	{
		return (const GameObject*)getOwner();
	}

private:

};