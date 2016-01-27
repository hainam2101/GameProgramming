#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Object.h"
#include "es_util.h"
#include "Ref.h"
#include "Map.h"
#include "Input.h"
#include "SpriteBatch.h"
#include "Sprite.h"
#include "Text.h"
#include "SpriteSheet.h"
#include "Texture.h"
#include "GameApp.h"

class GameApp;

using namespace yam2d;

class GameState : public Object
{
protected:
	GameState(GameApp* app){}


	Ref<Texture>openGLTexture = 0;
	Ref<Text>text = 0;
	Ref<Texture>fontTexture = 0;
	Ref<Sprite>sprite = 0;
	Ref<SpriteBatchGroup>batch = 0;
	Ref<SpriteSheet>font = 0;

public:
	virtual~GameState(){}

	virtual bool update(ESContext* ctx, float deltaTime)
	{
		return true;
	}
	virtual void render(ESContext* ctx)
	{

	}
	
	GameApp* getApp(){ return m_app; };
private:
	GameApp* m_app;
};

#endif