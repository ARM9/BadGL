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

	if (shaderError(shaderID)){
		return false;
	}
	
	m_Shaders.push_back(shaderID);
	
	return true;
}

bool Shader::link()
{
	if(!m_Shaders.empty())
	{
		for(auto& it : m_Shaders){
			glAttachShader(m_ProgramID, it);
		}
		glLinkProgram(m_ProgramID);
		
		deleteShaders();
		
		if(!programError())
			return true;
	}else{
		printf("Error: no shaders to link\n");
	}
	return false;
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

bool Shader::programError()
{
	GLint result = GL_FALSE;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);
	if (GL_FALSE == result){
		int infoLogLen;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLen);
		std::vector<char> errorMsg(infoLogLen + 1);
		glGetProgramInfoLog(m_ProgramID, infoLogLen, NULL, &errorMsg[0]);
		printf("%s\n", &errorMsg[0]);
		return true;
	}
	return false;
}

bool Shader::shaderError(GLenum name)
{
	GLint result = GL_FALSE;
	glGetShaderiv(name, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result){
		int infoLogLen;
		glGetShaderiv(name, GL_INFO_LOG_LENGTH, &infoLogLen);
		std::vector<char> errorMsg(infoLogLen + 1);
		glGetShaderInfoLog(name, infoLogLen, NULL, &errorMsg[0]);
		printf("%s\n", &errorMsg[0]);
		return true;
	}
	return false;
}

