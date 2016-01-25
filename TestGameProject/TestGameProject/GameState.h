#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Object.h"
#include "es_util.h"
#include "Ref.h"
#include "Map.h"
#include "Sprite.h"

class GameApp;

using namespace yam2d;

class GameState : public Object
{
public:
	GameState();
	virtual~GameState();

	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void render(ESContext* ctx);

	
	GameApp* getApp();
private:

};

#endif