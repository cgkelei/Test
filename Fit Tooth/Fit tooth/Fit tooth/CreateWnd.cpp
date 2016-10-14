#include "CreateWnd.h"
#include <GL/freeglut.h>
#include <GL/glew.h>


CreateWnd::CreateWnd( int width, int height, const char* title ) :_width( width ),
																  _height( height ), 
																  m_szWndTitle( title )
																  
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
	glutInitContextFlags( GLUT_CORE_PROFILE );
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
	CHECKERROR;
	m_triangles[0].position = glm::vec3( -1, -1, 0 );
	m_triangles[1].position = glm::vec3( 0, 1, 0 );
	m_triangles[2].position = glm::vec3( 1, -1, 0 );

	m_triangles[0].color = glm::vec3( 1, 0, 0 );
	m_triangles[1].color = glm::vec3( 0, 1, 0 );
	m_triangles[2].color = glm::vec3( 0, 0, 1 );

	m_indices[0] = 1;
	m_indices[2] = 2;
	m_indices[3] = 3;


	glClearColor( m_fBkColor[0], m_fBkColor[1], m_fBkColor[2], 1.0f );
	if (!m_GLshader.LoadFormFile( "shaders/vshader.vert", GL_VERTEX_SHADER ))
	{
		cerr << "error" << endl;
	}
	CHECKERROR;
	m_GLshader.LoadFormFile( "shaders/fshader.frag" ,GL_FRAGMENT_SHADER);
	//CHECKERROR;
	m_GLshader.CreateAndLinkProgram();
	m_GLshader.Use();
	m_GLshader.addAttribute( "vVertex" );
	m_GLshader.addAttribute( "vColor" );
	m_GLshader.addUniform( "MVP" );
	m_GLshader.Unuse();
	TestTriangle();
}														   

void CreateWnd::Render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glBindVertexArray( _vertexID );
	m_GLshader.Use();
	
	glUniformMatrix4fv( m_GLshader( "MVP" ), 1, GL_FALSE, glm::value_ptr( m_MV*m_P ) );
	glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0 );


	m_GLshader.Unuse();

	glutSwapBuffers();
}

void CreateWnd::OnSize( int _x, int _y )
{
  if (_x<0||_y<0)
  {
	  _x = 1;
	  _y = 1;
  }
  glViewport( 0, 0, _x, _y );
  m_P = glm::ortho( -1, 1, -1, 1 );
}

void CreateWnd::OnClose()
{

}

void CreateWnd::GenBuffer()
{
	//CHECKERROR;
	glGenVertexArrays( 1, &_vertexID );
	glGenBuffers( 1, &_vertexbuffer );
	glGenBuffers( 1, &_indeicesbuffer );

	glBindVertexArray( _vertexID );
	glBindBuffer( GL_ARRAY_BUFFER, _vertexbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( m_triangles ), &m_triangles[0], GL_STATIC_DRAW );
	glEnableVertexAttribArray( m_GLshader["vVertex"] );
	glVertexAttribPointer( m_GLshader["vVertex"], 3, GL_FLOAT, GL_FALSE, sizeof( VERTEX ), 0 );
	
	glEnableVertexAttribArray( m_GLshader["vColor"] );
	glVertexAttribPointer( m_GLshader["vColor"], 3, GL_FLOAT, GL_FALSE, sizeof( VERTEX ), ( const void* )offsetof( VERTEX, color ) );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _indeicesbuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( m_indices ), &m_indices[0], GL_STATIC_DRAW );


	glBindVertexArray( 0 );
	CHECKERROR;


}

void CreateWnd::TestTriangle()
{
	GenBuffer();

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
}
