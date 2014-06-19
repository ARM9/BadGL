#version 150 core

//layout(location = 0) in vec4 vertexPosition;
in vec3 vertexPosition;

uniform vec2 offset;

void main()
{
	gl_Position = vertexPosition * vec4(offset, 1.0, 1.0);
}
