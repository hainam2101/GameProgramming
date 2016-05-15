#include "BallController.h"

BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties())
{
	activeBalls = 0;
	movement = true;
	position = vec2(11, 10);
	moveSpeed = 0.3f;
	velocity = 1.1f;
}

void BallController::update(float deltaTime)
{
	//printf_s("DeltaTime: %d\n", deltaTime);
	for (int i = 0; i < balls.size(); i++)
	{
		if (deltaTime >= 0.03f)
		{
			esLogMessage("Spawning a new ball!");
			spawnBalls(balls.front() + activeBalls);
			//deltaTime = 0.0f;
		}
		// Set movespeed for the ball
		// Tiles / second

		if (getKeyState(KEY_SPACE) && !movement)
		{
			movement = true;
		}

		if (movement == true)
		{
			getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*position);

		}

		// Returns ball position where it was first
		if (getKeyState(KEY_R))
		{
			moveSpeed = 0.3f;
			movement = false;
			return getGameObject()->setPosition(11, 10); // Positions are 64x64 tiels
		}
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
			moveSpeed *= velocity;
		}
		// React to top and bottom borders
		if (objects->getName() == "Top" || objects->getName() == "Bottom")
		{
			//balls.erase(balls.begin(), balls.begin()+i);
			objects->setPosition(3, 3);
			activeBalls--;
		}
		// React to player pads
		if (objects->getName() == "Player1Pad")
		{
			//p1.setBallIsColliding(true);
			position.y *= -1.0f;
			moveSpeed *= velocity;
		}
		if (objects->getName() == "Player2Pad")
		{
			//p2.setBallIsColliding(true);
			position.y *= -1.0f;
			moveSpeed *= velocity;
		}
	}

}

void BallController::spawnBalls(GameObject* ball)
{
	ball->setPosition(11, 10);
	activeBalls++;
}

void BallController::addBallObjects(GameObject* ball)
{
	balls.push_back(ball);
}

BallController::~BallController()
{

}