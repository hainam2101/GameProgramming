#include "GameApp.h"


GameApp::GameApp()
{
}


GameApp::~GameApp()
{
}

bool GameApp::update(ESContext* ctx, float deltaTime)
{
	return true;
}

void GameApp::render(ESContext* ctx)
{
	float vertexData[] =
	{
		0.3f, -0.3f, 0.0f,
		-0.3f, -0.3f, 0.0f,
		0.0f, 0.3f, 0.0f,
	};

	// Set the viewport
	glViewport(0, 0, ctx->width, ctx->height);

	// Set OpenGL clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);

	// Set vertex data
	glVertexPointer(3, GL_FLOAT, 0, &vertexData);

	// Draw one triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);
}

void GameApp::setState(GameState* newState)
{
	m_currentState = newState;
}