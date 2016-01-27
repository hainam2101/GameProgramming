#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"



class MenuState : public GameState
{
public:
	MenuState(GameApp* app) : GameState(app), m_app(app)
	{
	}
	virtual~MenuState()
	{

	}

	virtual bool update(ESContext* ctx, float deltaTime)
	{
		return true;
	}

private:
	GameApp* m_app;
	Ref<Map> m_map;
	//Ref<Layer>Background, Objects;
};

#endif