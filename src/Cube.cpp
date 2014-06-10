#include "Precompiled.h"
#include "Cube.h"

Cube::Cube(float scale = 1.f)
: m_Scale(scale), m_Vertices({
	1.0, 1.0, 0.0,
	1.0, -1.0, 0.0,
	-1.0, -1.0, 0.0,
	-1.0, 1.0, 0.0})
{
	for(auto& it : m_Vertices)
	{
		it *= m_Scale;
	}

	buildGeometry();
}

Cube::~Cube() 
{
	
}

void Cube::buildGeometry()
{

}

