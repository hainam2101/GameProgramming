#pragma once

#include "SpriteComponent.h"
#include "GameObject.h"
#include "Input.h"
#include "Player1Controller.h"
#include "Player2Controller.h"

using namespace yam2d;

class BallController : public Component, public Updatable
{
public:
	BallController(GameObject* parent);
	virtual~BallController();

	virtual void update(float deltaTime);

	void checkCollision(GameObject* objects, float deltaTime);

	void addBallObjects(GameObject* ball);

	void spawnBalls(GameObject* ball);

	GameObject* getGameObject()
	{
		return (GameObject*)getOwner();
	}
	const GameObject* getGameObject() const
	{
		return (const GameObject*)getOwner();
	}
	
	std::vector<GameObject*> getBallVector()
	{ 
		return balls; 
	}

	BallController * clone() const
	{
		return new BallController(*this);
	}
private:
	int activeBalls;
	float timeSinceLastSpawn;
	bool movement = false;
	vec2 position;
	float velocity;
	float moveSpeed;
	Player1Controller p1();
	Player2Controller p2();
	std::vector<GameObject*> balls;
	std::vector<GameObject*>::iterator it;
};