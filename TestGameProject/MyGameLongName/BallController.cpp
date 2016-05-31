#include "BallController.h"

BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties())
{
	p1Score = 0;
	p2Score = 0;

	angle = slm::radians(rand() % 90 + 315);
	direction.x = cosf(angle);
	direction.y = sinf(angle);

	if ((rand() % 100) < 50)
	{
		direction.x *= -1;
	}

	position = vec2(11, 10);
	moveSpeed = 0.4f;
}

void BallController::update(float deltaTime)
{
	getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*direction*position);


	// Returns ball position where it was first
	if (getKeyState(KEY_RETURN))
	{
		float angle = slm::radians(rand() % 90 + 315);
		direction.x = cosf(angle);
		direction.y = sinf(angle);

		if ((rand() % 100) < 50)
		{
			direction.x *= -1;
		}
		moveSpeed = 0.3f;
		return getGameObject()->setPosition(11, 10); // Positions are 64x64 tiels
	}

}

void BallController::checkCollision(GameObject* objects, float deltaTime)
{

	// React to left and right walls
	if (objects->getName() == "LeftWall" || objects->getName() == "RightWall")
	{
		position.x *= -1.0f;
		moveSpeed *= 1.05f;
	}
	// React to top and bottom borders
	if (objects->getName() == "Top")
	{
		p1Score++;
		angle = slm::radians(rand() % 90 + 315);
		direction.x = cosf(angle);
		direction.y = sinf(angle);
		moveSpeed = 0.3f;
		getGameObject()->setPosition(11, 10);
	}
	if (objects->getName() == "Bottom")
	{
		p2Score++;
		angle = slm::radians(rand() % 90 + 315);
		direction.x = cosf(angle);
		direction.y = sinf(angle);
		moveSpeed = 0.3f;
		getGameObject()->setPosition(11, 10);
	}
	// React to player pads
	if (objects->getName() == "Player1Pad" || objects->getName() == "Player2Pad")
	{
		position.y *= -1.0f;
		moveSpeed *= 1.15f;
	}
	
}

BallController::~BallController()
{

}