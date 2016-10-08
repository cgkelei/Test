#include "Shader.h"
#include "fstream"
#include "Log.h"

Shader::Shader() :m_program(0), totalShaders(0)
{
	m_attributeList.clear();
	m_uniformList.clear();
	m_shaders[VERTEX_SHADER]	= 0;
	m_shaders[FRAGMENT_SHADER]	= 0;
	m_shaders[GEOMETRY_SHADER]	= 0;	
}

Shader::~Shader()
{
	m_attributeList.clear();
	m_uniformList.clear();
}

STATUS Shader::LoadFromString( const char* _file, GLenum _whichShader )
{
	GLuint _shader = glCreateShader( _whichShader );
	glShaderSource( _shader, 1, &_file, NULL );
	GLint status;
	glCompileShader( _shader );
	glGetShaderiv( _shader, GL_COMPILE_STATUS, &status );
	if (status == GL_FALSE)
	{
		GLint infologLength;
		glGetShaderiv( _shader, GL_INFO_LOG_LENGTH, &infologLength );
		GLchar* infoLog = new GLchar[infologLength];
		glGetShaderInfoLog( _shader, infologLength, NULL, infoLog );
		Log::SetLog( infoLog );
		delete []infoLog;
		return STATUS::FAILED;
	}
	m_shaders[totalShaders++] = _shader;
	return STATUS::SUCCESS;
}

STATUS Shader::LoadFromFile( const char* _fileName, GLenum _whichShader )
{
	ifstream inf( _fileName, ios_base::in );
	if (!_fileName)
	{
		char str[200] = { 0 };
		sprintf( str, "Shader:%sLoad Failed", _fileName );
		Log::SetLog( str );
		return STATUS::FAILED;
	}
	string line, buffer;
	while (getline( inf, line ))
	{
		buffer.append( line );
		buffer.append( "\r\n" );
	}
	
	if (STATUS::FAILED == LoadFromString( buffer.c_str(), _whichShader ))
	{
		char str[200] = { 0 };
		sprintf( str, "%s Load Failed",buffer.c_str() );
		Log::SetLog( str );
		return STATUS::FAILED;
	}
	return STATUS::SUCCESS;
}

void Shader::CreateAndLink()
{
	m_program = glCreateProgram();
	if (m_shaders[VERTEX_SHADER] != 0)
	{
		glAttachShader( m_program, m_shaders[VERTEX_SHADER] );
	}
	if (m_shaders[FRAGMENT_SHADER] != 0)
	{
		glAttachShader( m_program, m_shaders[FRAGMENT_SHADER] );
	}
	if (m_shaders[GEOMETRY_SHADER] != 0)
	{
		glAttachShader( m_program, m_shaders[GEOMETRY_SHADER] );
	}
	GLint status;
	glLinkProgram( m_program );
	glGetProgramiv( m_program, GL_LINK_STATUS, &status );
	if (status == GL_FALSE)
	{
		GLint infologlength;
		glGetProgramiv( m_program, GL_INFO_LOG_LENGTH, &infologlength );
		GLchar * infolog = new GLchar[infologlength];
		glGetProgramInfoLog( m_program, infologlength,NULL, infolog );
		cerr << "link log" << infolog << endl;
		delete[] infolog;
	}
	glDeleteShader( m_shaders[VERTEX_SHADER] );
	glDeleteShader( m_shaders[FRAGMENT_SHADER] );
	glDeleteShader( m_shaders[GEOMETRY_SHADER] );
}


void Shader::Use()
{
	glUseProgram( m_program );
}

void Shader::UnUse()
{
	glUseProgram( 0 );
}

void Shader::AddAttribute( const string& _attribute )
{
	m_attributeList[_attribute] = glGetAttribLocation( m_program, _attribute.c_str() );
}

void Shader::AddUniform( const string& _uniform )
{
	m_uniformList[_uniform] = glGetUniformLocation( m_program, _uniform.c_str());
}

GLuint Shader::operator()( const string& _uniform )
{
	return m_uniformList[_uniform];
}

GLuint Shader::operator[]( const string& _attribute )
{
	return m_attributeList[_attribute];
}

void Shader::DeleteShaderProgram()
{
	glDeleteShader( m_program );
}
