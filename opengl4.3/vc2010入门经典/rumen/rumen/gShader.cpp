#include "stdafx.h"
#include "gShader.h"
#include <iostream>

gShader::gShader() :m_totalShaders(0)
{
	m_uniformList.clear();
	m_attributeList.clear();
	for (size_t i = 0; i < 3;i++)
	{
		Shaders[i] = 0;
	}
}


gShader::~gShader()
{
	m_uniformList.clear();
	m_attributeList.clear();
	glDeleteProgram( _program );
}

bool gShader::LoadFromString( string _path, GLenum _type )
{
	GLuint shader = glCreateShader( _type );
	const char* pstr = _path.c_str();
	glShaderSource( shader, 1, &pstr, NULL );
	glCompileShader( shader );
	GLint status;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
	if (status == GL_FALSE)
	{
		int nlength;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &nlength );
		GLchar *str = new GLchar[nlength];
		glGetShaderInfoLog( shader, nlength, NULL,str);
		cerr << str << endl;
		delete[] str;
		return false;
	}
	Shaders[m_totalShaders++] = shader;
	return true;
}

bool gShader::LoadFromFile( string _path, GLenum _whichShader )
{
	ifstream inf( _path.c_str(), ios::in );
	if (!inf)
	{
		cerr << "Open File Error" << endl;
		return false;
	}
	string line, buffer;
	while (getline( inf, line ))
	{
		buffer.append(line);
		buffer.append( "\r\n" );
	}
	if (!LoadFromString( buffer, _whichShader ))
	{
		return false;
	}
	return true;
}

void gShader::CreateAndLink()
{
	_program = glCreateProgram();
	if (Shaders[VERTEX_SHADER] != 0)
	{
		glAttachShader( _program, Shaders[VERTEX_SHADER] );
	}
	if (Shaders[FRAGMENT_SHADER] != 0)
	{
		glAttachShader( _program, Shaders[FRAGMENT_SHADER] );
	}
	if (Shaders[GEOMETRY_SHADER] != 0)
	{
		glAttachShader( _program, Shaders[GEOMETRY_SHADER] );
	}
	
	GLint status;
	glLinkProgram( _program );
	glGetProgramiv( _program, GL_LINK_STATUS, &status );
	if (status == GL_FALSE)
	{
		int nlength = 0;
		glGetProgramiv( _program, GL_INFO_LOG_LENGTH, &nlength );
		GLchar *str = new GLchar[nlength];
		glGetProgramInfoLog( _program, nlength, NULL, str );
		cerr << str << endl;
		delete[] str;
		return;
	}
	glDeleteShader( Shaders[VERTEX_SHADER] );
	glDeleteShader( Shaders[FRAGMENT_SHADER] );
	glDeleteShader( Shaders[GEOMETRY_SHADER] );

}

void gShader::Use()
{
	glUseProgram( _program );
}

void gShader::UnUse()
{
	glUseProgram( 0 );
}

void gShader::DeleteProgram()
{
	glDeleteProgram( _program );
}

void gShader::adduniform( string _str )
{
	m_uniformList[_str] = glGetUniformLocation( _program,_str.c_str());
}

void gShader::addattribute( string _str )
{
	m_attributeList[_str] = glGetUniformLocation( _program, _str.c_str() );
}

GLuint gShader::operator[]( string _attribute )
{
	return m_attributeList[_attribute];
}

GLuint gShader::operator()( string _uniform )
{
	return m_uniformList[_uniform];
}
