#include "Precompiled.h"
#include "App.h"

App::App()
{
	if(!glfwInit()){
		printf("Error: could not initialize glfw.");
		exit(EXIT_FAILURE);
	}
	
 	m_GameWindow = new GameWindow(640, 480, "sod sfml");

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(GLEW_OK != err){
		printf("Error: %s", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	if(!m_GameWindow->init()){
		printf("Error: could not create GameWindow");
		exit(EXIT_FAILURE);
	}
}

App::~App()
{
	delete m_GameWindow;
	glfwTerminate();
	printf("glfw terminated successfully, exiting");
}

void App::run()
{
	double now, prev = glfwGetTime(), dt;
	while(!m_GameWindow->closed())
	{
		now = glfwGetTime();
		dt = now - prev;
		prev = now;
		m_GameWindow->render(dt);
		glfwPollEvents();
	}
}
