#version 330 core
 
layout(location = 0) in vec3 vVertex;	//object space vertex position


//output from the vertex shader
smooth out vec4 vSmoothColor;		//smooth colour to fragment shader

//uniform
uniform mat4 MVP;	//combined modelview projection matrix
uniform vec3 vColor;
void main()
{
	//assign the per-vertex colour to vSmoothColor varying
   vSmoothColor = vec4(vColor,1.0f);

   //get the clip space position by multiplying the combined MVP matrix with the object space 
   //vertex position
   gl_Position = MVP*vec4(vVertex,1);
}