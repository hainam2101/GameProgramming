// Include OpenGL ES Engine utils
#include <es_util.h>
#include "GameState.h"
#include "SplashScreenState.h"
#include "GameApp.h"

using namespace yam2d;

namespace
{
	GameApp* game;
	SplashScreenState* splash;
}
// Initialize the game
bool init(ESContext *esContext)
{
	game = new GameApp();
	splash = new SplashScreenState();
	return true;
}


// Deinitialize the game
void deinit(ESContext *esContext)
{
}


// Draw game
void draw(ESContext *esContext)
{
	game->render(esContext);
}

void update(ESContext* ctx, float deltaTime)
{
	game->update(ctx, deltaTime);

	if (false)
		esQuitApp;
}


//extern "C" void app_dummy();



int main(int argc, char *argv[])
{
	
	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "MenuTesti", 1280, 720, ES_WINDOW_DEFAULT);


	esRegisterInitFunc(&esContext, init);
	esRegisterDrawFunc(&esContext, draw);
	esRegisterUpdateFunc(&esContext, update);
	esRegisterDeinitFunc(&esContext, deinit);

	esMainLoop(&esContext);
	return 0;
}
