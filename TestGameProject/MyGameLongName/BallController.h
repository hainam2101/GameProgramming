#pragma once

#include "SpriteComponent.h"
#include "GameObject.h"
#include "Input.h"

using namespace yam2d;

class BallController : public Component, public Updatable
{
public:
	BallController(GameObject* parent);
	virtual~BallController();

	virtual void update(float deltaTime);

	GameObject* getGameObject()
	{
		return (GameObject*)getOwner();
	}
	const GameObject* getGameObject() const
	{
		return (const GameObject*)getOwner();
	}

	void setPositionToMouse(slm::vec2 posMouse){ getGameObject()->setPosition(posMouse); }

private:
	bool movement = false;
};