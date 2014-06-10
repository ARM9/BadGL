#pragma once
#include "Precompiled.h"
#include "Renderer.h"
#include "Renderable.h"

class GameWindow : public Renderable
{
public:
	GameWindow(int width, int height, const char * title);
	virtual ~GameWindow();

	bool init();

	virtual void render(float dt);
	virtual void update();

	bool closed();

private:
	int m_Width, m_Height;
	GLFWwindow *m_Window;
	Renderer *m_Renderer;
};
