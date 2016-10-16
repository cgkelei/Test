#ifndef CREATEWND_H_
#define CREATEWND_H_
#include <string>
#include <iostream>
#include <Gl/glew.h>
#include <GL/freeglut.h>
#include <assert.h>
#include "GLshader.h"
#include <glm.hpp>
#include <../glm/gtx/transform.hpp>
#include <../glm/gtc/type_ptr.hpp>

#include "Grid.h"
#include "FreeCamera.h"
#include "Texture.h"
using namespace std;
#define  CHECKERROR  assert(glGetError() == GL_NO_ERROR);

const int VK_W = 0x57;
const int VK_S = 0x53;
const int VK_A = 0x41;
const int VK_D = 0x44;
const int VK_Q = 0x51;
const int VK_Z = 0x5a;
const int MOUSE_HISTORY_BUFFER_SIZE = 128;

struct VERTEX
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;
};
class CreateWnd
{
public:
	CreateWnd(int width, int height, const char* title);
	~CreateWnd();
	bool InitWnd(int argc, char **argv);
	void SetWindowTitle(const char* title);
	void SetWindowSize(int width, int height);
	void Initdata();
	void Render();
	void OnSize(int _x, int _y);
	void OnClose();

	void GenBuffer();


	void OnKeyDown(unsigned char key,int x,int y);
	void OnMouseDown(int button, int s, int x, int y);
	void OnMouseMove(int x, int y);
	void FilterMouseMoves(float dx, float dy);
	void OnIdle();
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

	Grid*		 m_pGrid;
	FreeCamera*	 m_pCamera;


	///

private:
	GLfloat		m_fBkColor[3];
	GLint		_width;
	GLint		_height;
	string		m_szWndTitle;
	GLshader	m_GLshader;

	Texture		*m_texture;
	GLboolean	m_IsUseFiltering;
	int			m_nstate;
	int			m_noldx, m_noldy;
	int			m_ncureentX;
	int			m_ncurrentY;

	float		m_ffov;
	float		m_fRx;
	float		m_fRy;

	float		m_mouseX;
	float		m_mouseY;

	float		m_last_time, m_current_time;
	float		m_dlteTime;




	glm::vec2 mouseHistory[MOUSE_HISTORY_BUFFER_SIZE];
	const float MOUSE_FILTER_WEIGHT = 0.75f;
	const int MOUSE_HISTORY_BUFFER_SIZE = 10;

public:
	GLfloat* GetColor();
	void SetColor(int _red, int _green, int _blue);
};


#endif // !CREATEWND_H_
