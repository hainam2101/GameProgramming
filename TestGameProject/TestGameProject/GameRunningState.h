#ifndef GAMERUNNINGSTATE_H
#define GAMERUNNINGSTATE_H

#include "GameState.h"
#include "MenuState.h"
#include "MyGameComponentFactory.h"
#include <iostream>

class GameRunningState : public GameState
{
public:
	GameRunningState(GameApp* app);
	virtual~GameRunningState();

	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void render(ESContext* ctx);
	float getZoom();
	void setZoom(float newZoom);

private:
	float deltaTime = 0;
	float zoom = 1.0f;
	Ref<GameObject> m_gameObject;
	Ref<TmxMap> m_tmap;
	MyGameComponentFactory* m_componentFactory;
	float mouseX = 0.0f;
	float mouseY = 0.0f;

};

#endif