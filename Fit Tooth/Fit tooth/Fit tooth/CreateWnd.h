#pragma once
#include <string>
#include <iostream>
#include <Gl/glew.h>
#include <GL/freeglut.h>
#include <assert.h>
#include "GLshader.h"
#include <glm.hpp>
#include <../glm/gtx/transform.hpp>
#include <../glm/gtc/type_ptr.hpp>
using namespace std;
#define  CHECKERROR  assert(glGetError() == GL_NO_ERROR)


struct VERTEX
{
	glm::vec3 position;
	glm::vec3 color;
};
class CreateWnd
{
public:
	CreateWnd( int width, int height, const char* title );
	~CreateWnd();
	bool InitWnd( int argc, char **argv );
	void SetWindowTitle( const char* title );
	void SetWindowSize( int width, int height );
	void Initdata();
	void Render();
	void OnSize( int _x, int _y );
	void OnClose();

	void GenBuffer();

 ///triangle
public:
	void TestTriangle();
private:
	glm::mat4	m_MV;
	glm::mat4	m_P;
	VERTEX		m_triangles[3]; //Èý½ÇÃæ
	GLushort 	m_indices[3];	 //Ë÷Òý
	GLuint	    _vertexID;
	GLuint		_vertexbuffer;
	GLuint		_indeicesbuffer;




///

private:
	GLfloat		m_fBkColor[3];
	GLint		_width;
	GLint		_height;
	string		m_szWndTitle;
	GLshader	m_GLshader;
	


public:
	GLfloat* GetColor();
	void SetColor( int _red, int _green, int _blue );
};

