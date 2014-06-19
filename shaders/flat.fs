#version 150 core

in vec3 aVColor;

out vec4 gl_FragColor;

void main()
{
	gl_FragColor = vec4(aVColor, 1.0);
}
