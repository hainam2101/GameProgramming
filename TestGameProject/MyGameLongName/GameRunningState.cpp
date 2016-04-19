#include "GameRunningState.h"
#include "MainMenuState.h"

GameRunningState::GameRunningState(GameApp* app) : GameState(app), m_tmap(0), m_componentFactory(0), m_gameObject(0)
{
	esLogMessage("Initializing Level 1!");
	m_tmap = new TmxMap();
	m_componentFactory = new MyGameComponentFactory();

	bool okay = m_tmap->loadMapFile("../assets/level.tmx", m_componentFactory);

	if (okay)
	{
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
	//setZoom(getZoom() + getMouseWheelDelta());

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
			m_tmap->findGameObjectByName("Ball")->getComponent<BallController>()->checkCollision(m_tmap->getLayer("StaticColliders")->getGameObjects()[i], deltaTime);
		}
	}
	// Check if colliding with DynamicObjects
	for (int i = 0; i < m_tmap->getLayer("DynamicObjects")->getGameObjects().size(); i++)
	{
		if (m_tmap->findGameObjectByName("Ball")->collidesTo(m_tmap->getLayer("DynamicObjects")->getGameObjects()[i], &plaa))
		{
			std::cout << plaa.x << " " << plaa.y << std::endl;
			m_tmap->findGameObjectByName("Ball")->getComponent<BallController>()->checkCollision(m_tmap->getLayer("DynamicObjects")->getGameObjects()[i], deltaTime);
		}
	}

	m_tmap->update(deltaTime);
	return true;
}

void GameRunningState::render(ESContext* ctx)
{
	// Set OpenGL clear color
	glClearColor(0.5f, 0.0f, 0.0f, 1.0f);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set screen size to camera.
	// Camera has a bug that width will be abnormal to the game itself
	m_tmap->getCamera()->setScreenSize(ctx->width / 0.95, ctx->height);

	// Render map and all of its layers containing GameObjects to screen.
	m_tmap->render();
}

GameRunningState::~GameRunningState()
{
	// Delete game stuff
	esLogMessage("Deinit");
	delete m_componentFactory;
}