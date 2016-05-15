#pragma once

#include "SpriteComponent.h"
#include "GameObject.h"
#include "Input.h"

using namespace yam2d;

class Player2Controller : public Component, public Updatable
{
public:
	Player2Controller(GameObject* parent);
	virtual~Player2Controller();

	virtual void update(float deltaTime);

	GameObject* getGameObject()
	{
		return (GameObject*)getOwner();
	}
	const GameObject* getGameObject() const
	{
		return (const GameObject*)getOwner();
	}
	void setBallIsColliding(bool state)
	{
		ballIsColliding = state;
	}
	
private:
	bool ballIsColliding;
};

