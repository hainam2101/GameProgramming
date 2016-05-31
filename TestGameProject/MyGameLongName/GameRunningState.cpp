#include "GameRunningState.h"
#include "MainMenuState.h"
#include "EndScreenState.h"

GameRunningState::GameRunningState(GameApp* app) : GameState(app), m_tmap(0), m_componentFactory(0), m_gameObject(0)
{
	esLogMessage("Initializing Level 1!");
	esLogMessage(__FUNCTION__);
	int cc = 0;
	esLogMessage("Init... %d", cc++);
	// Create new sprite batch group. This must be deleted at deinit.
	batch = new SpriteBatchGroup();

	esLogMessage("init... %d", cc++);
	// create new sprite, with default parameters.
	sprite = new Sprite(0);

	//esLogMessage("Init... %d", cc++);
	//// Load font texture. Made with font creation tool like bitmap font builder.
	fontTexture = new Texture("../assets/Fixedsys_24_Bold.png");

	esLogMessage("Init... %d", cc++);
	//// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
	font = SpriteSheet::autoFindFontFromTexture(fontTexture, "../assets/Fixedsys_24_Bold.dat");

	esLogMessage("Init... %d", cc++);
	// Create new text-object
	text = new Text(0, font);
	text2 = new Text(0, font);

	esLogMessage("Init... Done");
	m_tmap = new TmxMap();
	m_componentFactory = new MyGameComponentFactory();
	bool okay = m_tmap->loadMapFile("../assets/NewLevel.tmx", m_componentFactory);

	if (okay)
	{
		esLogMessage("Map loading okay!");
		m_tmap->getCamera()->setPosition(vec2(m_tmap->getWidth() / 2.0f - 0.5f, m_tmap->getHeight() / 2.0f - 0.5f));
	}
}

float GameRunningState::getZoom()
{
	return zoom;
}

void GameRunningState::setZoom(float newZoom)
{
	zoom = slm::clamp(newZoom, 0.25f, 8.0f);
}

bool GameRunningState::update(ESContext* ctx, float deltaTime)
{
	// Set text.
	text->setText("Player 1: ARROWS");
	text->setColor(0.0, 1.0, 0.0, 1.0);

	text2->setText("Player 2: WASD");
	text2->setColor(0.0, 1.0, 0.0, 1.0);

	// Clear sprite before add new dynamic sprites.
	batch->clear();

	// Add sprite. Rotate it according to total time. We need also scale font a bit (100 times, so the sprite is 100x100 pixels).

	// Add text to position -400,300
	batch->addText(fontTexture, text, vec2(-ctx->width / 2.6, ctx->height / 6 - ctx->height / 2), 0, vec2(1, 1));
	batch->addText(fontTexture, text2, vec2(-ctx->width / 2.65, ctx->height - ctx->height / 1.5), 0, vec2(1, 1));

	setZoom(getZoom() + getMouseWheelDelta());

	if (getKeyState(KEY_ESCAPE) == 1)
	{
		getApp()->setState(new MainMenuState(getApp()));
		return true;
	}

	slm::vec2 plaa = slm::vec2(0.0f);
	// Check if colliding with StaticColliders
	for (int i = 0; i < m_tmap->getLayer("StaticColliders")->getGameObjects().size(); i++)
	{
		if (m_tmap->findGameObjectByName("Ball")->collidesTo(m_tmap->getLayer("StaticColliders")->getGameObjects()[i], &plaa))
		{
			std::cout << plaa.x << " " << plaa.y << std::endl;
			m_tmap->findGameObjectByName("Ball")->getComponent<BallController>()
				->checkCollision(m_tmap->getLayer("StaticColliders")->getGameObjects()[i], deltaTime);
		}
	}
	// Check if colliding with DynamicObjects
	for (int i = 0; i < m_tmap->getLayer("DynamicObjects")->getGameObjects().size(); i++)
	{
		if (m_tmap->findGameObjectByName("Ball")->collidesTo(m_tmap->getLayer("DynamicObjects")->getGameObjects()[i], &plaa))
		{
			std::cout << plaa.x << " " << plaa.y << std::endl;
			m_tmap->findGameObjectByName("Ball")->getComponent<BallController>()
				->checkCollision(m_tmap->getLayer("DynamicObjects")->getGameObjects()[i], deltaTime);
		}
	}

	if (m_tmap->findGameObjectByName("Ball")->getComponent<BallController>()->getPlayer1Score() >= 10 
		|| m_tmap->findGameObjectByName("Ball")->getComponent<BallController>()->getPlayer2Score() >= 10)
		getApp()->setState(new EndScreenState(getApp()));
	else
		m_tmap->update(deltaTime);
	return true;
}

void GameRunningState::render(ESContext* ctx)
{
	// Set OpenGL clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the viewport to be full window area.
	glViewport(0, 0, ctx->width, ctx->height);

	// Set projection to identity
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate half screen size
	float left = -0.5f*ctx->width;
	float right = 0.5f*ctx->width;
	float bottom = -0.5f*ctx->height;
	float top = 0.5f*ctx->height;

	// Set OpenGL orthogonal projection for screen size <esContext->width,esContext->height>
	glOrthof(float(int(left)), float(int(right)), float(int(bottom)), float(int(top)), -1.0, 1.0f);

	// Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable alpha blending (transparency)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set screen size to camera.
	// Camera has a bug that width will be abnormal to the game itself
	m_tmap->getCamera()->setScreenSize(ctx->width / 0.95, ctx->height);
	batch->render();
	// Render map and all of its layers containing GameObjects to screen.
	m_tmap->render();
}

GameRunningState::~GameRunningState()
{
	// Delete game stuff
	esLogMessage("Deinit");
	delete m_componentFactory;
}