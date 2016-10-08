#version 430 core
layout(location = 0) in vec3 vVertex;
layout (location = 1) in vec3 vColor;
smooth out vec4 fragmentcolor;
uniform mat4 MVP;
void main()
{
	fragmentcolor = vec4(vColor,1.0f);
	gl_Position = MVP*vec4(vVertex,1.0f);
}