#include "Precompiled.h"
#include "Shader.h"

Shader::Shader()
{
	m_ProgramID = glCreateProgram();
}

Shader::~Shader()
{
	deleteShaders();
	glDeleteProgram(m_ProgramID);
}

bool Shader::load(GLenum type, const char *file)
{
	std::ifstream inFile;
	std::string shaderCode;
	inFile.open(file, std::ios::in);
	if(inFile.is_open()){
		std::string line("");
		while(getline(inFile, line))
			shaderCode += "\n" + line;
		inFile.close();
	}else{
		printf("Error opening shader: %s", file);
		return false;
	}
#ifdef _DEBUG
	printf("\n%s", shaderCode.c_str());
#endif

	GLenum shaderID = glCreateShader(type);
	const char *cstrPtr = shaderCode.c_str();
	glShaderSource(shaderID, 1, &cstrPtr, NULL);
	glCompileShader(shaderID);

	GLint result = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if(GL_FALSE == result){
		int infoLogLen;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLen);
		std::vector<char> shaderErrorMsg(infoLogLen + 1);
		glGetShaderInfoLog(shaderID, infoLogLen, NULL, &shaderErrorMsg[0]);
		printf("GLSL Error: %s\n", &shaderErrorMsg[0]);
		return false;
	}
	m_Shaders.push_back(shaderID);
	
	return true;
}

bool Shader::link()
{
	for(auto& it : m_Shaders){
		glAttachShader(m_ProgramID, it);
	}
	glLinkProgram(m_ProgramID);

	GLint result = GL_FALSE;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);
	if(GL_FALSE == result){
		int infoLogLen;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLen);
		std::vector<char> programErrorMsg(infoLogLen+1);
		glGetProgramInfoLog(m_ProgramID, infoLogLen, NULL, &programErrorMsg[0]);
		printf("Link error: %s\n", &programErrorMsg[0]);
		return false;
	}
	deleteShaders();

	return true;
}

void Shader::use()
{
	glUseProgram(m_ProgramID);
}

void Shader::deleteShaders()
{
	for(auto& it : m_Shaders)
	{
		glDetachShader(m_ProgramID, it);
		glDeleteShader(it);
	}
	m_Shaders.clear();
}

GLint Shader::getUniformLocation(const char *name)
{
	return glGetUniformLocation(m_ProgramID, name);
}

