#version 330 core

in vec4 aVColor;

out vec3 gl_FragColor;

void main()
{
	gl_FragColor = vec3(aVColor.r, aVColor.g, aVColor.b);
}
