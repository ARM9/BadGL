#pragma once

class Cube
{
public:
	Cube(float scale);
	~Cube();

	void buildGeometry();
private:
	float m_Scale;
	std::vector<GLfloat> m_Vertices;
};
