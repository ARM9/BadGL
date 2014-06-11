#include "Precompiled.h"
#include "Renderer.h"
#include "Shader.h"

const GLfloat g_TriangleVertices[] = {
	0.f, 1.0f, 0.f, 1.f,
	1.0f, -1.0f, 0.f, 1.f,
	-1.0f, -1.0f, 0.f, 1.f,

	1.f, 0.f, 0.f, 1.f,
	0.f, 1.f, 0.f, 1.f,
	0.f, 0.f, 1.f, 1.f};

const GLfloat g_fff[] = {
	0.6f, 0.6f, 0.f,
	-0.8f, .8f, 0.f,
	-0.7f, -0.6f, 0.f,
	0.9f, -0.9f, 0.f};

const GLubyte g_TriangleIndices[] = {
	0, 1, 2};

const GLubyte g_OutlineIndices[] = {
	0, 1, 2, 0};


Renderer::Renderer(int width, int height)
: m_iWidth(width), m_iHeight(height)
{
	glClearColor(0.2f, 0.6f, 0.8f, 0.0f);
	// create and bind vertex array object
	glGenVertexArrays(1, &m_FlatVaoID);
	glBindVertexArray(m_FlatVaoID);
	// create and bind buffer object for vertex data
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,  m_VertexBuffer);
	// copy data into buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_TriangleVertices), g_TriangleVertices, GL_STATIC_DRAW);
	// index buffer
	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_TriangleIndices), g_TriangleIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glGenVertexArrays(1, &m_OutlineVaoID);
	glBindVertexArray(m_OutlineVaoID);
	// vertex buffer
	glGenBuffers(2, m_OutlineBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_OutlineBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_TriangleVertices), g_TriangleVertices, GL_STATIC_DRAW);
	// index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OutlineBuffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_OutlineIndices), g_OutlineIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	

	glBindVertexArray(0);

	m_FlatShader = new Shader();
	m_FlatShader->load(GL_VERTEX_SHADER, "shaders/flat.vs");
	m_FlatShader->load(GL_FRAGMENT_SHADER, "shaders/flat.fs");

	m_OutlineShader = new Shader();
	m_OutlineShader->load(GL_VERTEX_SHADER, "shaders/outline.vs");
	m_OutlineShader->load(GL_FRAGMENT_SHADER, "shaders/outline.fs");

	if(!m_OutlineShader->link() ||
		!m_FlatShader->link())
	{
		printf("Error linking shaders, exiting");
		exit(EXIT_FAILURE);
	}
	m_OffsetLocation = m_FlatShader->getUniformLocation("offset");
	m_OutlineOffsetLocation = m_OutlineShader->getUniformLocation("offset");
}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_IndexBuffer);
	glDeleteBuffers(2, m_OutlineBuffer);
	glDeleteVertexArrays(1, &m_FlatVaoID);
	glDeleteVertexArrays(1, &m_OutlineVaoID);
	delete m_FlatShader;
	delete m_OutlineShader;
}

float dx = 0.0f, dy = 0.0f;
void Renderer::render(float dt)
{
	//float ratio = m_iWidth / (float)m_iHeight;
	glClear(GL_COLOR_BUFFER_BIT);
	dx = sin(glfwGetTime());
	dy = cos(glfwGetTime());
	// Draw model
	m_FlatShader->use();
	glUniform2f(m_OffsetLocation, dx, dy);
	glBindVertexArray(m_FlatVaoID);

	//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(4*3*sizeof(*g_TriangleVertices)));
	glDrawElements(GL_TRIANGLE_STRIP, sizeof(g_TriangleIndices)/sizeof(*g_TriangleIndices), GL_UNSIGNED_BYTE, (void*)0);

	// Draw outline
	m_OutlineShader->use();
	glUniform2f(m_OutlineOffsetLocation, dx, dy);
	glLineWidth(4.f);
	glBindVertexArray(m_OutlineVaoID);

	//glBindBuffer(GL_ARRAY_BUFFER, m_OutlineBuffer[0]);
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(GL_LINE_STRIP, sizeof(g_OutlineIndices)/sizeof(*g_OutlineIndices), GL_UNSIGNED_BYTE, (void*)0);
	
	glBindVertexArray(0);
	glUseProgram(0);
}

void Renderer::update()
{

}

void Renderer::update(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}
