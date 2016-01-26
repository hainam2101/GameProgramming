#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "GameState.h"
#include "Object.h"
#include "Ref.h"

using namespace yam2d;

class GameApp : public Object
{
public:
	GameApp();
	virtual~GameApp();

	bool update(ESContext* ctx, float deltaTime);
	void render(ESContext* ctx);
	void setState(GameState* newState);

private:
	Ref<GameState> m_currentState;

};

#endif