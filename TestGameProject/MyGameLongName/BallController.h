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

	void checkCollision(GameObject* objects, float deltaTime);

	GameObject* getGameObject()
	{
		return (GameObject*)getOwner();
	}
	const GameObject* getGameObject() const
	{
		return (const GameObject*)getOwner();
	}

	int getPlayer1Score(){ return p1Score; }
	int getPlayer2Score(){ return p2Score; }

private:
	vec2 position;
	float moveSpeed;
	float angle;
	int p1Score;
	int p2Score;
	vec2 direction;
};