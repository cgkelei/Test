#include "OGL.h"

OGL * OGL::m_Inistance = NULL;

std::string WINDOWTITLES = "Hello OGL";

OGL::OGL() :m_width(WIDTH), m_height(HEIGHT), m_windowsTitle(WINDOWTITLES)
, m_BKColor(Eigen::Vector3f(0.8f,0.8f,0.8f))
{
	Log::SetLog( "OGL initialize Success" );
}

OGL::~OGL()
{
	if ( m_Inistance != NULL )
	{
		delete m_Inistance;
		Log::SetLog( "GL Untialize Success" );
	}
}

OGL* OGL::GetInstance()
{
	 if ( m_Inistance == NULL )
	 {
		   m_Inistance = new OGL();
		   Log::SetLog( "GL initialize Success" );
	 }
	 return m_Inistance;
}

void OGL::Render()
{
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glutSwapBuffers();
}

void OGL::DataInitialize()
{
	glClearColor( m_BKColor[0], m_BKColor[1], m_BKColor[2],1.0f );
}

void OGL::OnShutDown()
{

}

void OGL::OnReShape( int _width, int _height )
{
	glViewport( 0, 0, _width, _height );
}

STATUS OGL::Init(int argc,char **argv)
{
	/*glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DEPTH | GLUT_RGBA |GLUT_DOUBLE );
	glutInitContextVersion( 4, 3 );
	glutInitContextFlags( GLUT_CORE_PROFILE | GLUT_DEBUG );
	glutInitContextProfile( GLUT_FORWARD_COMPATIBLE );
	glutInitWindowSize( m_width, m_height );
	glutCreateWindow( m_windowsTitle.c_str() );
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if ( GLEW_OK != err )
	{
	Log::SetLog( "glew initialize faild" );
	return STATUS::FAILED;
	}
	else
	{
	if (GLEW_VERSION_3_0)
	{
	Log::SetLog( "glew version 3.0" );
	}
	}
	char *str = (char*)glewGetString( GLEW_VERSION );
	Log::SetLog(str);
	str = ( char* )glGetString( GL_VENDOR );
	Log::SetLog( str );
	str = ( char* )glGetString( GL_RENDERER );
	Log::SetLog( str );


	glutCloseFunc( OnShutDown );
	glutDisplayFunc( Render );
	glutReshapeFunc(OnReShape);
	Log::PrintLog();
	glutMainLoop();	 */

	return STATUS::SUCCESS;
}

void OGL::SetWindowSize( int _width, int _height )
{
	m_width = _width;
	m_height = _height;
}

void OGL::SetWindowTitle( const char* title )
{
	m_windowsTitle = title;
}

void OGL::SetBKColor( const Eigen::Vector3f &_color )
{
	m_BKColor = _color;
}

const Eigen::Vector3f OGL::GetBKColor() const
{
	return m_BKColor;
}



