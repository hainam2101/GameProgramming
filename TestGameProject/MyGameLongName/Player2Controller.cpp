#include "Player2Controller.h"

Player2Controller::Player2Controller(GameObject* owner)
	: Component(owner, Component::getDefaultProperties())
{
	ballIsColliding = false;
}

Player2Controller::~Player2Controller(void)
{
}

void Player2Controller::update(float deltaTime)
{
	float moveSpeed = 4.0f;	//Tiles / second
	vec2 direction;
	// Get move direction from keyboard

	// Position is counted by the size of 1 block e.g. (64 x 1.0f) 
	if (getKeyState(KEY_A) && getGameObject()->getPosition().x>1.0f)
	{
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*vec2(-1.0f, 0.0f));
	}
	if (getKeyState(KEY_D) && getGameObject()->getPosition().x<17.0f)
	{
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*vec2(1.0f, 0.0f));
	}
	
	if (getKeyState(KEY_SPACE) && ballIsColliding == true)
	{
		// Hold on to balls
		do{

		} while (getKeyState(KEY_SPACE));
	}
}