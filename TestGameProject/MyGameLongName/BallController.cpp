#include "BallController.h"

BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties())
{
	position = vec2(9, 5);
	velocity = 0;
	moveSpeed = 0;
}

void BallController::update(float deltaTime)
{
	// Set movespeed for the ball
	// Tiles / second
	moveSpeed = 0.3f;
	velocity = 0.001f;

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

void BallController::checkCollision(GameObject* objects, float deltaTime)
{
	if (movement)
	{
		// React to left and right walls
		if (objects->getName() == "LeftWall" || objects->getName() == "RightWall")
		{
			position.x *= -1.0f;
		}
		// React to top and bottom borders
		if (objects->getName() == "Top" || objects->getName() == "Bottom")
		{
			getGameObject()->setPosition(9, 5);
		}
		// React to player pads
		if (objects->getName() == "Player1Pad" || objects->getName() == "Player2Pad")
		{
			position.y *= -1.0f;
			velocity += 2.2f;
		}
	}
}

BallController::~BallController()
{

}