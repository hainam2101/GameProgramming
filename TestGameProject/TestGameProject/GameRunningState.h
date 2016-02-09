#ifndef GAMERUNNINGSTATE_H
#define GAMERUNNINGSTATE_H

#include "GameState.h"

namespace
{
	class MyComponentFactory : public yam2d::DefaultComponentFactory
	{
	public:
		virtual Component* createNewComponent(const std::string& type, Entity* owner, const yam2d::PropertySet& properties)
		{
			// TODO: Implementation... Use now default implementation instead.
			return DefaultComponentFactory::createNewComponent(type, owner, properties);
		}


		virtual Entity* createNewEntity(ComponentFactory* componentFactory, const std::string& type, Entity* parent, const yam2d::PropertySet& properties)
		{
			// TODO: Implementation... Use now default implementation instead.
			return DefaultComponentFactory::createNewEntity(componentFactory, type, parent, properties);
		}
	private:
		Ref<Texture> m_playerTexture;
		Ref<Texture>m_enemyTexture;
		Map* m_map;

	};
}

class GameRunningState :
	public GameState
{
public:
	GameRunningState(GameApp* app) : GameState(app), m_map(0)
	{
		esLogMessage("Init first level");
		int cc = 0;

		float zoom = 1.0f;

		esLogMessage("Init... %d", cc++);
		m_map = new TmxMap();
		componentFactory = new MyComponentFactory();

		bool okay = m_map->loadMapFile("assets/testiLevel.tmx", componentFactory);

		if (okay)
		{
			esLogMessage("Map load OK");
			// Move camera to middle of map.
			m_map->getCamera()->setPosition(vec2(m_map->getWidth() / 2.0f - 0.5f, m_map->getHeight() / 2.0f - 0.5f));
		}

		//objectsLayer = new Layer(m_map, "Objects", 1.0f, true, false);

		//m_map->addLayer(Map::MAPLAYER1, objectsLayer);

		m_paddle = createSpriteGameObjects("assets/paddle.png", 256.0f, 64.0f, 0, 0, 256.0f, 64.0f, true);

		
		m_map->getLayer("Objects")->addGameObject(m_paddle);

		m_paddle->setPosition(vec2(m_map->getWidth()/2, 11));

		m_paddle->setName("Paddle");

		esLogMessage("Init... Done");
	}
	virtual~GameRunningState()
	{ 
		delete componentFactory;
		//delete m_map;
		//delete m_paddle;
	}
	virtual Entity* createNewEntity(ComponentFactory* componentFactory, const std::string& type, Entity* parent, const PropertySet& properties)
	{
		if ("StaticColliders" == type)
		{
			// asd
		}
	}

	GameObject* GameRunningState::createSpriteGameObjects(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor = false)
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

	float getZoom()
	{
		return zoom;
	}

	void setZoom(float newZoom)
	{
		zoom = slm::clamp(newZoom, 0.25f, 8.0f);
	}

	virtual bool update(ESContext* ctx, float deltaTime)
	{
		setZoom(getZoom() + getMouseWheelDelta());

		//if (getKeyState(KEY_ESCAPE) == 1)
		//{
		//	getApp()->setState(new MenuState(getApp()));
		//	return true;
		//	//return false;
		//}
		m_map->update(deltaTime);

		return true;
	}

	void moveGameObject(GameObject paddle, float speed, float deltaTime, bool direction)
	{

	}
	virtual void render(ESContext* ctx)
	{
		// Set OpenGL clear color
		glClearColor(0.5f, 0.0f, 0.0f, 1.0f);

		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set screen size to camera.
		m_map->getCamera()->setScreenSize(ctx->width, ctx->height, 400 / getZoom());

		// Draw batched objects to screen.
		m_map->render();
	}
private:
	GameApp* m_app;
	Ref<TmxMap>m_map = 0;
	ComponentFactory* componentFactory = 0;
	float zoom = 1.0f;
	Ref<GameObject> m_paddle = 0;
};

#endif