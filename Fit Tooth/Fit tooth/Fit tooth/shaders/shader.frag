#version 330 core

layout(location=0) out vec4 vFragColor;	//fragment shader output

//input form the vertex shader
smooth in vec4 vSmoothColor;		//interpolated colour to fragment shader
smooth in  vec2 vUV;
uniform sampler2D textureMap;
void main()
{
	//set the interpolated colour as the shader output
	vFragColor = texture(textureMap,vUV);
}