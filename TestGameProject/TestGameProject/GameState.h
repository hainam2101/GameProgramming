#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Object.h"


class GameState : yam2d::Object
{
public:
	GameState();
	~GameState();

	virtual bool update(ESContext*, float deltaTime);
	virtual void render(ESContext*);
private:

};

#endif