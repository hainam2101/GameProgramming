#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"



class MenuState : public GameState
{
public:
	MenuState();
	virtual~MenuState();

	virtual bool update(ESContext* ctx, float deltaTime);

private:
	Ref<Map> m_map;
};

#endif