#ifndef SPLASHSCREENSTATE_H
#define SLASHSCREENSTATE_H
#include "GameState.h"
#include "MenuState.h"

class SplashScreenState : public GameState
{
public:
	SplashScreenState(GameApp* app) : GameState(app), m_app(app)
	{
		esLogMessage(__FUNCTION__);
		int cc = 0;
		esLogMessage("Init... %d", cc++);
		// Create new sprite batch group. This must be deleted at deinit.
		batch = new SpriteBatchGroup();

		esLogMessage("Init... %d", cc++);
		// Load OpenGL logo to be used as texture for sprite.
		openGLTexture = new Texture("opengl-logo.png");

		esLogMessage("Init... %d", cc++);
		// Create new sprite, with default parameters.
		sprite = new Sprite(0);

		esLogMessage("Init... %d", cc++);
		// Load font texture. Made with font creation tool like bitmap font builder.
		fontTexture = new Texture("Fixedsys_24_Bold.png");

		esLogMessage("Init... %d", cc++);
		// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
		font = SpriteSheet::autoFindFontFromTexture(fontTexture, "Fixedsys_24_Bold.dat");

		esLogMessage("Init... %d", cc++);
		// Create new text-object
		text = new Text(0, font);

		esLogMessage("Init... Done");
		
	}

	virtual~SplashScreenState()
	{
	}
	virtual bool update(ESContext* ctx, float deltaTime)
	{
		//esLogMessage(__FUNCTION__);
		// Update total time counter.
		//count += deltaTime;

		// Set text.
		text->setText("Moro mualima!!");

		// Clear sprite before add new dynamic sprites.
		batch->clear();

		// Add sprite. Rotate it according to total time. We need also scale font a bit (100 times, so the sprite is 100x100 pixels).
		batch->addSprite(openGLTexture, sprite, vec2(0, 0), 0, vec2(100));

		// Add text to position -400,300
		batch->addText(fontTexture, text, vec2(-ctx->width / 3, ctx->height / 3), 0);
		m_totalTime += deltaTime;
		if (m_totalTime > 3.0f)
		{
			//MenuState* menu = new MenuState(getApp());
			getApp()->setState(new MenuState(getApp()));
			return true;
		}
		return true;
	}

	virtual void render(ESContext* ctx)
	{
		// Set OpenGL clear color
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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

		// Draw batched objects to screen.
		batch->render();
	}
private:
	float m_totalTime;
	GameApp* m_app;

};

#endif