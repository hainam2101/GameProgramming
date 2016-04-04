#include "MainMenuState.h"


MainMenuState::MainMenuState(GameApp* app) : GameState(app), m_app(app), m_map(0), backgroundLayer(0), objectsLayer(0)
{
	// Tile size
	vec2 tileSize(64.0f, 64.0f);

	// Create new map, with width == tile, heigh == 32pixels/tile
	m_map = new Map(tileSize.x, tileSize.y);

	// Background layer
	backgroundLayer = new Layer(m_map, "Background", 1.0f, true, false);

	m_map->addLayer(Map::BACKGROUND0, backgroundLayer);

	// Create new sprite GameObject from texture (background sprite) size is same than screen size.
	GameObject* backgroundGameObject = createSpriteGameObject("../assets/menuBG.png", 1280.0f, 720.0f, false);

	// Add GameObject to background layer.
	backgroundLayer->addGameObject(backgroundGameObject);

	// Objects layer
	objectsLayer = new Layer(m_map, "Objects", 1.0f, true, false);

	m_map->addLayer(Map::MAPLAYER0, objectsLayer);

	// Create new start button object, and clip it, white color shall be transparent
	GameObject* startButtonObject = createSpriteGameObject("../assets/buttons.png", 242.0f, 96.0f, 0, 0, 242, 96, false);

	// Add start button to level
	objectsLayer->addGameObject(startButtonObject);

	// Set Start button position
	startButtonObject->setPosition(-6.0f, 2.0f);
	
	// Set button name
	startButtonObject->setName("Start");

	// Create new start button object, and clip it, white color shall be transparent
	GameObject* exitButtonObject = createSpriteGameObject("../assets/buttons.png", 242.0f, 96.0f, 242, 0, 242, 96, false);

	// Add exit button to level
	objectsLayer->addGameObject(exitButtonObject);

	// Set button size
	//exitButtonObject->setSize(tileSize.x / 2.0, tileSize.y / 2.0);

	// Set exit button position
	exitButtonObject->setPosition(-6.0f, 4.5f);

	// Setting object names
	exitButtonObject->setName("Exit");
}

GameObject* MainMenuState::createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
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

GameObject* MainMenuState::createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor = false)
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

bool MainMenuState::update(ESContext* ctx, float deltaTime)
{
	// Read mouse values
	float mouseX = float(getMouseAxisX());
	float mouseY = float(getMouseAxisY());

	// Convert mouse coordinates to map coordinates.
	vec2 mouseInMapCoordinates = m_map->screenToMapCoordinates(mouseX, mouseY);


	//esLogMessage("Mouse in map: <%2.2f, %2.2f>", mouseInMapCoordinates.x, mouseInMapCoordinates.y);

	GameObject* pickedObject = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);

	std::string start = "Start";
	std::string exit = "Exit";

	if (pickedObject != 0)
	{
		std::string test1 = pickedObject->getName();
		if (test1.compare(start) == 0 && getMouseButtonState(MOUSE_LEFT))
		{
			esLogMessage("%s pressed!", pickedObject->getName().c_str());
			getApp()->setState(new GameRunningState(getApp()));
			return true;
		}

		else if (test1.compare(exit) == 0 && getMouseButtonState(MOUSE_LEFT))
		{
			esLogMessage("%s pressed!", pickedObject->getName().c_str());
			return false;
		}
	}
	else
	{
		// Update map. this will update all GameObjects inside a map layers.
		m_map->update(deltaTime);
	}
}

void MainMenuState::render(ESContext* ctx)
{
	// Set OpenGL clear color (dark gray)
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Set screen size to camera.
	m_map->getCamera()->setScreenSize(ctx->width, ctx->height);

	// Render map and all of its layers containing GameObjects to screen.
	m_map->render();
}

MainMenuState::~MainMenuState()
{

}