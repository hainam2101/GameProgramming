#include "BallController.h"

BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties())
{
	position = vec2(9, 5);
}

void BallController::update(float deltaTime)
{
	// Set movespeed for the ball
	// Tiles / second
	float moveSpeed = 0.3f;
	float velocity = 0.001f;

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
		return getGameObject()->setPosition(9, 5); // Positions are 64x64 tiels
	}

}

BallController::~BallController()
{

}