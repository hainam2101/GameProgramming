#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"
#include "GameRunningState.h"



class MenuState : public GameState
{
public:
	MenuState(GameApp* app) : GameState(app), m_app(app), Background(0), Objects(0)
	{
		esLogMessage(__FUNCTION__);

		///////////////////////////////////////
		
		// Level tile size
		vec2 tileSize(242, 96);

		// Create new map, which tile width == tile height == 32 pixels/tile
		m_map = new Map(tileSize.x, tileSize.y);

		Background = new Layer(m_map, "Background", 1.0f, true, false);
		m_map->addLayer(Map::BACKGROUND0, Background);
		GameObject* backGroundGameObject = createSpriteGameObject("menu.png", 1280.0f, 720.0f, false);
		Background->addGameObject(backGroundGameObject);

		Objects = new Layer(m_map, "Objects", 1.0f, true, false);
		m_map->addLayer(Map::MAPLAYER0, Objects);

		GameObject* startButtonObject = createSpriteGameObject("buttons.png", tileSize.x, tileSize.y, 0, 0, 242, 96, true);
		Objects->addGameObject(startButtonObject);
		startButtonObject->setPosition(0.0, 2);
		startButtonObject->setSize(tileSize.x / 1.5f, tileSize.y / 1.5f);
		startButtonObject->setName("Start");

		GameObject* exitButtonObject = createSpriteGameObject("buttons.png", tileSize.x, tileSize.y, 242, 0, 242, 96, true);
		Objects->addGameObject(exitButtonObject);
		exitButtonObject->setPosition(0.0, 3);
		exitButtonObject->setSize(tileSize.x/2, tileSize.y/2);
		exitButtonObject->setName("Exit");

		esLogMessage("Init... Done");
	}

	GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
	{
		// Load texture to be used as texture for sprite.
		Texture* texture = new Texture(bitmapFileName.c_str());

		// If user wants to create texture which white coros is treated as atransparent color.
		if (isWhiteTransparentColor)
		{
			// Set white to transparent. Here color values are from 0 to 255 (RGB)
			texture->setTransparentColor(255, 255, 255);
		}

		// Create new sprite GameObject from texture.
		GameObject* gameObject = new GameObject(0, 0);
		SpriteComponent* sprite = new SpriteComponent(gameObject, texture);

		// Resize the sprite to be correct size
		gameObject->setSize(sizeX, sizeY);

		// Add sprite component to game object
		gameObject->addComponent(sprite);
		return gameObject;
	}

	GameObject* MenuState::createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor)
	{
		// Load texture to be used as texture for sprite.
		Texture* texture = new Texture(bitmapFileName.c_str());

		// If user wants to create texture which white coros is treated as atransparent color.
		if (isWhiteTransparentColor)
		{
			// Set white to transparent. Here color values are from 0 to 255 (RGB)
			texture->setTransparentColor(255, 255, 255);
		}

		// Create new sprite GameObject from texture.
		GameObject* gameObject = new GameObject(0, 0);
		SpriteComponent* sprite = new SpriteComponent(gameObject, texture);

		// Resize the sprite to be correct size
		gameObject->setSize(sizeX, sizeY);

		// Specify clip area by start point and size in pixels
		Sprite::PixelClip clip;
		clip.topLeft.x = clipStartX;
		clip.topLeft.y = clipStartY;
		clip.clipSize.x = clipSizeX;
		clip.clipSize.y = clipSizeY;

		// Set pixel clip for sprite
		sprite->getSprite()->setClip(float(texture->getWidth()), float(texture->getHeight()), clip);

		// Add sprite component to game object
		gameObject->addComponent(sprite);
		return gameObject;
	}

	virtual~MenuState(){}

	virtual bool update(ESContext* ctx, float deltaTime)
	{
		// Read mouse values
		float mouseX = float(getMouseAxisX());
		float mouseY = float(getMouseAxisY());

		// Convert mouse coordinates to map coordinates.
		vec2 mouseInMapCoordinates = m_map->screenToMapCoordinates(mouseX, mouseY);

		GameObject* pickedObject = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);
		
		std::string start = "Start";
		std::string exit = "Exit";

		if (pickedObject != nullptr)
		{

			std::string test1 = pickedObject->getName();
			if (test1.compare(start) == 0 && getMouseButtonState(MOUSE_LEFT))
			{
				esLogMessage("Object %s picked!", pickedObject->getName().c_str());
				getApp()->setState(new GameRunningState(getApp()));
				return true;
			}
			else if (test1.compare(exit) == 0 && getMouseButtonState(MOUSE_LEFT))
			{
				esLogMessage("Object %s picked!", pickedObject->getName().c_str());
				return false;
			}
		}
		else
		{
			m_map->update(deltaTime);
		}
	}

	virtual void render(ESContext* ctx)
	{
		// Set OpenGL clear color (dark gray)
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// Set screen size to camera.
		m_map->getCamera()->setScreenSize(ctx->width, ctx->height, 720, 1280.0f / 720.0f);

		// Render map and all of its layers containing GameObjects to screen.
		m_map->render();
	}

private:
	GameApp* m_app;
	Ref<Map> m_map;
	Ref<Layer>Background, Objects;

};

#endif