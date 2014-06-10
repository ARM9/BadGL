#pragma once
#include "Cube.h"
#include "Renderable.h"
#include "Shader.h"

class Renderer : public Renderable
{
public:
	Renderer(int w, int h);
	~Renderer();

	virtual void render(float dt);
	virtual void update();
	void update(int w, int h);

private:
	// internal resolution
	int m_iWidth, m_iHeight;

	GLuint m_FlatVaoID;
	GLuint m_OutlineVaoID;
	GLuint m_VertexBuffer;
	GLuint m_ColorBuffer;
	GLuint m_IndexBuffer;

	GLuint m_OutlineBuffer[2];

	GLint m_OffsetLocation;
	GLint m_OutlineOffsetLocation;

	Shader *m_FlatShader;
	Shader *m_OutlineShader;
};
