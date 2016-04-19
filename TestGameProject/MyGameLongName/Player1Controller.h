#pragma once

#include "SpriteComponent.h"
#include "GameObject.h"
#include "Input.h"

using namespace yam2d;

class Player1Controller : public Component, public Updatable
{
public:
	Player1Controller(GameObject* parent);
	virtual~Player1Controller();

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