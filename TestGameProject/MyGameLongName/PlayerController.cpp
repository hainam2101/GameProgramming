#include "PlayerController.h"

PlayerController::PlayerController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties())
{
}

PlayerController::~PlayerController(void)
{
}

void PlayerController::update(float deltaTime)
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
}