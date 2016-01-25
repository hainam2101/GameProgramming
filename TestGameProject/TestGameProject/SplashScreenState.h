#ifndef SPLASHSCREENSTATE_H
#define SLASHSCREENSTATE_H
#include "GameState.h"

class SplashScreenState : public GameState
{
public:
	SplashScreenState();
	virtual~SplashScreenState();
	virtual bool update(ESContext* ctx, float deltaTime);
private:
	Ref<Sprite> m_sprite;
};

#endif