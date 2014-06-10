#pragma once
#include "Precompiled.h"
#include "GameWindow.h"

class App
{
public:
	App();
	~App();

	void run();
private:
	GameWindow *m_GameWindow;
};
