#include "BallController.h"

BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties())
{
	activeBalls = 0;
	timeSinceLastSpawn = 0.0f;
	position = vec2(0, 0);
	moveSpeed = 0.1f;
	velocity = 1.1f;
}

void BallController::update(float deltaTime)
{
	if (timeSinceLastSpawn >= 5.0f)
	{
		esLogMessage("Spawning a new ball, active balls: %d", activeBalls);
		spawnBalls(balls.front() + activeBalls);
		timeSinceLastSpawn = 0.0f;
	}

	if (activeBalls >= 1)
	{
		for (it = balls.begin(); it != balls.end(); it++)
		{
			(*it)->setPosition((*it)->getPosition() + deltaTime * moveSpeed * position);
		}
	}
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*position);

	timeSinceLastSpawn += deltaTime;
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
	balls.clear();
}