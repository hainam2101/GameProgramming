#include "Player1Controller.h"

Player1Controller::Player1Controller(GameObject* owner)
	: Component(owner, Component::getDefaultProperties())
{
	ballIsColliding = false;
}

Player1Controller::~Player1Controller(void)
{
}

void Player1Controller::update(float deltaTime)
{
	float moveSpeed = 4.0f;	//Tiles / second
	vec2 direction;
	// Get move direction from keyboard

	// Position is counted by the size of 1 block e.g. (64 x 1.0f) 
	if (getKeyState(KEY_LEFT) && getGameObject()->getPosition().x>1.0f)
	{
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*vec2(-1.0f, 0.0f));
	}
	if (getKeyState(KEY_RIGHT) && getGameObject()->getPosition().x<17.0f)
	{
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*vec2(1.0f, 0.0f));
	}
	
	if (getKeyState(KEY_NUMPAD0) && ballIsColliding == true)
	{
		// Hold on to balls
		//do{

		//} while (getKeyState(KEY_NUMPAD0));
	}
}