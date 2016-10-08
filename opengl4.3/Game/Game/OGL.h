#ifndef OGL_H
#define OGL_H
#include <iostream>
#include "Log.h"
#include "statusCode.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Eigen/Core>

#define   GetGL() OGL::GetInstance() 
const int WIDTH = 800;
const int HEIGHT = 800;

class OGL 
{
public:
	 explicit OGL();
	~OGL();
	static OGL* GetInstance();
	STATUS Init( int argc, char **argv );
	void SetWindowSize( int _width, int _height );
	void SetWindowTitle( const char* title );
	void SetBKColor( const Eigen::Vector3f &_color );
	const Eigen::Vector3f GetBKColor()const;
	static void Render();
	//////////////////////////////////////////////////////////////////////////
	void DataInitialize();
	static void OnShutDown();
	static void OnReShape( int _width, int _height );


	
private:
	static OGL		   *m_Inistance;
	std::string			m_stringLogInfo;
	int				    m_width;
	int					m_height;
	std::string		    m_windowsTitle;
	Eigen::Vector3f		m_BKColor;

};
#endif // !GL_H


