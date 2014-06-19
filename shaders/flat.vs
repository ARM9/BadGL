#version 150 core

in vec3 vertexPosition_modelspace;
in vec3 vertexColor;
//layout(location = 0) in vec4 vertexPosition_modelspace;
//layout(location = 1) in vec4 vertexColor;

uniform vec2 offset;

out vec3 aVColor;

void main()
{
	gl_Position = vec4(vertexPosition_modelspace*vec4(offset, 1.0, 1.0));
	aVColor = vertexColor;
}
