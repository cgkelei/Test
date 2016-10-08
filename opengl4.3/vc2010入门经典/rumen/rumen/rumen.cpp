// rumen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
#define GET_ERROR (assert(glGetError()==GL_NO_ERROR));

typedef struct VERTEX
{
	glm::vec3 _pos;
	glm::vec3 _color;
}VERTEX;

VERTEX g_Vertex[] = {
	glm::vec3{ -1, -1, 0 }, glm::vec3{ 1, 0, 0 },
	glm::vec3{ 1, -1, 0 }, glm::vec3{ 0, 1, 0 },
	glm::vec3{ 0.5, 1, 0 }, glm::vec3{ 0, 0, 1 }
};
GLushort g_index[3] = { 0, 1, 2 };
GLuint  g_vao;
GLuint  g_vbo;
GLuint	g_ind;
#include "gShader.h"
gShader g_shader;


glm::mat4 MV( 1);
glm::mat4 P( 1 );
void init()
{

	if (!g_shader.LoadFromFile( "./shaders/vertex.vert", GL_VERTEX_SHADER ))
	{
		cerr << "Load Vertex shader Error" << endl;
	}
	if (!g_shader.LoadFromFile( "./shaders/fragment.frag", GL_FRAGMENT_SHADER ) )
	{
		cerr << "Load Fragment Shader error " << endl;
	}
	g_shader.CreateAndLink();
	g_shader.Use();
	g_shader.addattribute( "vVertex" );
	g_shader.addattribute( "vColor" );
	g_shader.adduniform( "MVP" );
	GET_ERROR
	g_shader.UnUse();
	GET_ERROR
	glGenVertexArrays( 1, &g_vao );
	glGenBuffers( 1, &g_vbo );
	glGenBuffers( 1, &g_ind );

	
	glBindVertexArray( g_vao );

	glBindBuffer(GL_ARRAY_BUFFER,g_vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( g_Vertex ), &g_Vertex[0], GL_STATIC_DRAW );
	GET_ERROR

	glEnableVertexAttribArray( g_shader["vVertex"] );
	glVertexAttribPointer( g_shader["vVertex"], 3, GL_FLOAT, GL_FALSE, sizeof( VERTEX ), 0 );


	

	glEnableVertexAttribArray( g_shader["vColor"] );
	glVertexAttribPointer( g_shader["vColor"], 3, GL_FLOAT, GL_FALSE, sizeof( VERTEX ), ( const void * )offsetof( VERTEX, _color ) );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, g_ind );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( g_index ), &g_index[0], GL_STATIC_DRAW );
		
}
void OnRender()
{
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	g_shader.Use();
	glUniformMatrix4fv( g_shader( "MVP"),1,GL_FALSE ,glm::value_ptr( P*MV));
	glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0 );



	g_shader.UnUse();




	glutSwapBuffers();
}
void OnDown()
{
	cout << "Exit" << endl;
	
}

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void OnSize( int x, int y )
{
	glViewport( 0, 0, x, y );

	P = glm::ortho( -1, 1, -1, 1 );
}
int _tmain(int argc, char* argv[])
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA );
	glutInitContextVersion( 4, 3 );
	glutInitContextFlags( GLUT_CORE_PROFILE | GLUT_DEBUG);
	glutInitWindowSize( 400, 400 );
	glutCreateWindow( "simple triangle" );
	glewExperimental = GL_TRUE;
	GLenum  err = glewInit();
	if (err != GLEW_OK)
	{
		cerr << "error" << endl;
		return -1;
	}
	else
	{
		if (GLEW_VERSION_4_3)
		{
			cout << "glew_version 4.3" << endl;
		}
	}
	err = glGetError();
	cout << "glew version:" << glewGetString( GLEW_VERSION ) << endl;
	cout << "GLSL" << glGetString( GL_SHADING_LANGUAGE_VERSION ) << endl;
	cout << "GL version" << glGetString( GL_VERSION ) << endl;

	init();
	glutDisplayFunc( OnRender );
	glutReshapeFunc( OnSize );
	glutCloseFunc ( OnDown );
	glutMainLoop();
	return 0;
}

