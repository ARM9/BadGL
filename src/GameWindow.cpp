#include "Precompiled.h"
#include "GameWindow.h"

GameWindow::GameWindow(int width, int height, const char * title)
:	m_Width(width),
	m_Height(height),
	m_Window(nullptr),
	m_Renderer(nullptr)
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	m_Window = glfwCreateWindow(m_Width, m_Height, title, NULL, NULL);
	if(!m_Window){
		printf("Error: could not initialize glfw.");
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	printf("\nGL version: %s", glGetString(GL_VERSION));
	printf("\nglfw GL version: %d.%d\n",
		glfwGetWindowAttrib(m_Window, GLFW_CONTEXT_VERSION_MAJOR),
		glfwGetWindowAttrib(m_Window, GLFW_CONTEXT_VERSION_MINOR));
}

GameWindow::~GameWindow()
{
	delete m_Renderer;
	glfwDestroyWindow(m_Window);
}

bool GameWindow::init()
{
	m_Renderer = new Renderer(m_Width, m_Height);
	return true;
}

void GameWindow::render(float dt)
{
	int tw, th;
	glfwGetFramebufferSize(m_Window, &tw, &th);
	m_Renderer->update(tw, th);
	m_Renderer->render(dt);
	glfwSwapBuffers(m_Window);
}

void GameWindow::update()
{

}

bool GameWindow::closed()
{
	return glfwWindowShouldClose(m_Window);
}
