#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"



class MenuState : public GameState
{
public:
	MenuState(GameApp* app) : GameState(app){}
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
	Ref<Map> m_map;
};

#endif