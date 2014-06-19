#pragma once

/* Interface for glsl shaders */
class Shader
{
public:
	Shader();
	~Shader();

	bool load(GLenum type, const char * file);
	bool link();
	void use();

	void bindAttribLocation(GLuint index, const char *name);
	GLint getUniformLocation(const char *name);
protected:
	void deleteShaders();

	bool programError();
	bool shaderError(GLenum name);
private:
	GLuint m_ProgramID;
	std::vector<GLuint> m_Shaders;
};
