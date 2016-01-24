#ifndef SPLASHSCREENSTATE_H
#define SLASHSCREENSTATE_H
#include "GameState.h"

class SlashScreenState : public GameState
{
public:
	SlashScreenState();
	~SlashScreenState();
	virtual bool update(ESContext*, float deltaTime);
private:
	yam2d::Ref<yam2d::Sprite> m_sprite;
};

#endif