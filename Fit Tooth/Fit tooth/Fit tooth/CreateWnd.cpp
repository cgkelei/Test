#include "CreateWnd.h"
#include <GL/freeglut.h>
#include <GL/glew.h>
#include "FreeCamera.h"
#include <glm.hpp>

#define  EPSILON2 0.000001f
CreateWnd::CreateWnd( int width, int height, const char* title ) :_width( width ),
																  _height( height ), 
																  m_szWndTitle( title ),
																  m_IsUseFiltering(true),
																  m_ffov(0), m_fRx(0), m_fRy(0),
																  m_mouseX(0),m_mouseY(0)
																  
{
	try { 
		if (!InitWnd( 0, NULL ))
			throw "Windows Initialize fail";
		}
	catch(...){
		cerr << "windows error" << endl;
	}
	float Temcolor[3] = { 0.6f,0.6f,0.6f };

	memcpy( m_fBkColor, Temcolor, sizeof( GLfloat ) * 3 );

}

CreateWnd::~CreateWnd()
{

}

bool CreateWnd::InitWnd( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
	glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
	glutInitContextVersion( 4, 3 );
	glutInitWindowSize( _width, _height );
	glutCreateWindow( m_szWndTitle.c_str() );
	glewExperimental = GL_TRUE;
	GLenum status = glewInit();
	if (GLEW_OK != status)
	{
		cerr << "Glew initialize error" << endl;
	}
	else
	{
		if (GL_VERSION_4_3)
		{
			cout << "GL_4.3" << endl;
		}
	}
	status = glGetError();
	CHECKERROR;
	cout <<"\t 使用"<< glewGetString( GLEW_VERSION ) << endl;
	cout << "\t使用" << glGetString( GL_VENDOR ) << endl;
	cout << "\t使用" << glGetString( GL_RENDERER ) << endl;
	cout <<"\tGLSL" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	CHECKERROR;
	return true;

}

void CreateWnd::SetWindowTitle( const char * title )
{
	m_szWndTitle = title;
}

void CreateWnd::SetWindowSize( int width, int height )
{
	_width  = width;
	_height = height;
}

void CreateWnd::Initdata()
{

	m_pGrid = new Grid(20, 20);
	m_pGrid->SetColor(glm::vec3(0.0f, 1.0f, 1.0f));
	m_pCamera = new FreeCamera();


	
	glm::vec3 p(4);
	m_pCamera->SetPosition(p);
	glm::vec3 look = glm::normalize(p);
	float yaw = glm::degrees(float(atan2(look.z, look.x) + 3.1415926f));
	float pitch = glm::degrees(asin(look.y));
	m_fRx = yaw;
	m_fRy = pitch;
	if (m_IsUseFiltering)
	{
		for (int i = 0; i < MOUSE_HISTORY_BUFFER_SIZE;i++)
		{
			mouseHistory[i] = glm::vec2(m_fRx, m_fRy);
		}
	}
	m_pCamera->Rotate(m_fRx, m_fRy,0);


	
	CHECKERROR;
	m_triangles[0].position = glm::vec3( -1, -1, 0 );
	m_triangles[1].position = glm::vec3( 0, 1, 0 );
	m_triangles[2].position = glm::vec3( 1, -1, 0 );

	m_triangles[0].color = glm::vec3( 1, 0, 0 );
	m_triangles[1].color = glm::vec3( 0, 1, 0 );
	m_triangles[2].color = glm::vec3( 0, 0, 1 );


	m_triangles[0].uv = glm::vec2(0.0f, 0.0f);
	m_triangles[1].uv = glm::vec2(1.0f, 0.0f);
	m_triangles[2].uv = glm::vec2(0.5f, 1.0f);

	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;

	CHECKERROR;
	glClearColor( m_fBkColor[0], m_fBkColor[1], m_fBkColor[2], 1.0f );
	if (!m_GLshader.LoadFormFile( "shaders/shader.vert", GL_VERTEX_SHADER ))
	{
		cerr << "error" << endl;
	}
	CHECKERROR;
	m_GLshader.LoadFormFile( "shaders/shader.frag" ,GL_FRAGMENT_SHADER);
	CHECKERROR;
	m_GLshader.CreateAndLinkProgram();
	m_GLshader.Use();
	m_GLshader.addAttribute( "vVertex" );
	m_GLshader.addAttribute( "uv" );
	m_GLshader.addUniform("textureMap");
	m_GLshader.addUniform( "MVP" );
	glUniform1i(m_GLshader("textureMap"), 0);

	m_GLshader.Unuse();
	CHECKERROR;
	m_MV = glm::mat4(1.0f);
	GenBuffer();
}		

void CreateWnd::Render()
{
	CHECKERROR;

	m_last_time = m_current_time;
	m_current_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	m_dlteTime = m_current_time - m_last_time;

	m_MV = m_pCamera->GetViewMatrix();
	m_P = m_pCamera->GetProjectionMatrix();
	glm::mat4 mvp = m_P*m_MV;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		m_GLshader.Use();
		glBindVertexArray(_vertexID);
	
		glUniformMatrix4fv(m_GLshader("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
		glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0 );
		
		CHECKERROR;
	m_GLshader.Unuse();

	
	m_pGrid->Render(glm::value_ptr(mvp));
	
	glutSwapBuffers();
}

void CreateWnd::OnSize( int _x, int _y )
{
  //if (_x<0||_y<0)
  //{
	 // _x = 1;
	 // _y = 1;
  //}
  glViewport( 0, 0, _x, _y );
  //m_P = glm::ortho( -1, 1, -1, 1 );
  m_pCamera->SetProjection(45.0f, (GLfloat)_x/ _y);
}

void CreateWnd::OnClose()
{
	glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_indeicesbuffer);
	glDeleteVertexArrays(1, &_vertexID);
	m_GLshader.DeleteShaderProgram();
}

void CreateWnd::GenBuffer()
{
	CHECKERROR;
	glGenVertexArrays( 1, &_vertexID );
	glGenBuffers( 1, &_vertexbuffer );
	glGenBuffers( 1, &_indeicesbuffer );

	glBindVertexArray( _vertexID );

	glBindBuffer( GL_ARRAY_BUFFER, _vertexbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( m_triangles ), &m_triangles[0], GL_STATIC_DRAW );


	glEnableVertexAttribArray( m_GLshader["vVertex"] );
	glVertexAttribPointer( m_GLshader["vVertex"], 3, GL_FLOAT, GL_FALSE, sizeof( VERTEX ), 0 );
	
	//glEnableVertexAttribArray( m_GLshader["vColor"] );
	//glVertexAttribPointer( m_GLshader["vColor"], 3, GL_FLOAT, GL_FALSE, sizeof( VERTEX ), ( const void* )offsetof( VERTEX, color ) );

	glEnableVertexAttribArray(m_GLshader["uv"]);
	glVertexAttribPointer(m_GLshader["uv"], 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX), (const void*)offsetof(VERTEX, uv));

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _indeicesbuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( m_indices ), &m_indices[0], GL_STATIC_DRAW );
	CHECKERROR;
	m_texture = new Texture("image/Lenna.png");
	glBindVertexArray( 0 );
	CHECKERROR;

	

}

void CreateWnd::OnKeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		m_IsUseFiltering = !m_IsUseFiltering;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void CreateWnd::OnMouseDown(int button, int s, int x, int y)
{
	
	if (s == GLUT_DOWN)
	{
		m_noldx = x;
		m_noldy = y;
	
	}

	if (button == GLUT_MIDDLE_BUTTON)
		m_nstate = 0;
	else if (button == GLUT_RIGHT_BUTTON)
		m_nstate = 2;
	else
		m_nstate = 1;

}

void CreateWnd::OnMouseMove(int x, int y)
{
	if (m_nstate == 0)
	{

		m_ffov += (y - m_noldy)/20.0f;
		m_pCamera->SetProjection(m_ffov, m_pCamera->GetAspectRation());
	}
	else if (m_nstate == 1)
	{
	/*	m_fRx += (x - m_noldx) / 5.0f;
		m_fRy += (y - m_noldy) / 5.0f;


		if (m_IsUseFiltering)
		{
			FilterMouseMoves((float)x, (float)y);
		}
		else
		{
			m_mouseX = m_fRx;
			m_mouseY = m_fRy;
		}*/
		m_fRx = (float)x - m_noldx;
		m_fRy = (float)y - m_noldy;
		m_mouseX -= m_fRx;
		m_mouseY += m_fRy;
		m_pCamera->Rotate(m_mouseX, m_mouseY, 0);
	}
	m_noldx = x;
	m_noldy = y;
	glutPostRedisplay();

}

void CreateWnd::TestTriangle()
{
	

}

GLfloat* CreateWnd::GetColor()
{
	return m_fBkColor;
}

void CreateWnd::SetColor( int _red, int _green, int _blue )
{
	m_fBkColor[0] = _red / 255.0f;
	m_fBkColor[1] = _green / 255.0f;
	m_fBkColor[2] = _blue / 255.0f;
	glClearColor(m_fBkColor[0], m_fBkColor[1], m_fBkColor[2], 1.0f);
}

void CreateWnd::FilterMouseMoves(float dx, float dy) {
	for (int i = MOUSE_HISTORY_BUFFER_SIZE - 1; i > 0; --i) {
		mouseHistory[i] = mouseHistory[i - 1];
	}

	// Store current mouse entry at front of array.
	mouseHistory[0] = glm::vec2(dx, dy);

	float averageX = 0.0f;
	float averageY = 0.0f;
	float averageTotal = 0.0f;
	float currentWeight = 1.0f;

	// Filter the mouse.
	for (int i = 0; i < MOUSE_HISTORY_BUFFER_SIZE; ++i)
	{
		glm::vec2 tmp = mouseHistory[i];
		averageX += tmp.x * currentWeight;
		averageY += tmp.y * currentWeight;
		averageTotal += 1.0f * currentWeight;
		currentWeight *= MOUSE_FILTER_WEIGHT;
	}

	m_mouseX = averageX / averageTotal;
	m_mouseY = averageY / averageTotal;

}

void CreateWnd::OnIdle()
{
	if (GetAsyncKeyState(VK_W) & 0x8000)
	{
		m_pCamera->Walk(m_dlteTime);
		cout << "W" << endl;
	}
	if (GetAsyncKeyState(VK_S) & 0x8000)
	{
		m_pCamera->Walk(-m_dlteTime);
	}
	if (GetAsyncKeyState(VK_A) & 0x8000)
	{
		m_pCamera->Left(-m_dlteTime);
		cout << "A" << endl;
	}
	if (GetAsyncKeyState(VK_D) & 0x8000)
	{
		m_pCamera->Left(m_dlteTime);
	}
	if (GetAsyncKeyState(VK_Z) & 0x8000)
	{
		m_pCamera->UP(m_dlteTime);
	}
	if (GetAsyncKeyState(VK_Q) & 0x8000)
	{
		m_pCamera->UP(-m_dlteTime);
	}

	glm::vec3 t = m_pCamera->GetTranslation();
	if (glm::dot(t, t) > EPSILON2) {
		m_pCamera->SetTranslation(t*0.95f);
	}

	//call the display function
	glutPostRedisplay();
}
