#include "BallController.h"

BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties())
{

}

void BallController::update(float deltaTime)
{
	// Set movespeed for the ball
	// Tiles / second
	float moveSpeed = 1.0f;
	float velocity = 0.001f;

	// 
	vec2 direction;
	vec2 position = vec2(3.0f, -1.0f);
	if (getKeyState(KEY_SPACE) && !movement)
	{
		movement = true;
	}

	if (movement == true)
	{
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*position);

	}

	// Returns ball position where it was first
	if (getKeyState(KEY_RETURN))
	{
		movement = false;
		return getGameObject()->setPosition(9, 10); // Positions are 64x64 tiels
	}

}

BallController::~BallController()
{

}