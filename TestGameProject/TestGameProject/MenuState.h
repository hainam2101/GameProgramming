#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"


class MenuState : public GameState
{
public:
	MenuState();
	~MenuState();

	virtual bool update(ESContext*, float deltaTime);

private:
	yam2d::Ref<yam2d::Map> m_map;
};

#endif