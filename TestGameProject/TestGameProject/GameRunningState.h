#ifndef GAMERUNNINGSTATE_H
#define GAMERUNNINGSTATE_H

#include "GameState.h"

class GameRunningState :
	public GameState
{
public:
	GameRunningState();
	virtual~GameRunningState();

	virtual bool update(ESContext* ctx, float deltaTime)
	{
	}
	virtual void render(ESContext* ctx);
private:
};

#endif