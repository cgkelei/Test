#include "GLshader.h"
#include <fstream>



GLshader::GLshader() : m_totalShaders(0)
					  
{
	m_attributeList.clear();
	m_uniformList.clear();
	m_uShader[VERTEX_SHADER] = 0;
	m_uShader[FRAGMENT_SHADER] = 0;
	m_uShader[GEOMETRY_SHADER] = 0;
}

GLshader::~GLshader()
{
	m_attributeList.clear();
	m_uniformList.clear();
}

bool GLshader::LoadFormFile( const string& _fileName, GLenum whichShader )
{
	ifstream fp;
	fp.open(_fileName.c_str(), ios_base::in);
	if (fp)
	 {	
		 string line, buffer;
		 while (getline(fp, line))
		 {
			 buffer.append( line );
			 buffer.append( "\r\n" );
		 }
		 if (!LoadFromString( buffer, whichShader ))
		 {
			 return  false;
		 }
	 }
	 else
	 {
		 return false;
	 }
	 return true;
}

bool GLshader::LoadFromString( const string& _stringstream, GLenum whichShader )
{
	//创建shader
	GLuint shader = glCreateShader( whichShader );
	const char *source = _stringstream.c_str();
	//指定shader
	glShaderSource( shader, 1, &source,NULL );
	//编译shader
	glCompileShader( shader );
	GLint status;
 	glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
	if (status ==GL_FALSE)
	{
		GLint 	 infoLogLength;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength );
		GLchar* szlog = new GLchar[infoLogLength];
		glGetShaderInfoLog( shader, infoLogLength, NULL, szlog );
		cerr << "shader compile Error" <<szlog << endl;
		delete[] szlog;
		return false;
	}
	m_uShader[m_totalShaders++] = shader;
	return true;
}

void GLshader::CreateAndLinkProgram()
{	 
	//创建 program
	m_program = glCreateProgram();
	//结束program
	if (m_uShader[VERTEX_SHADER] != 0)
	{
		glAttachShader( m_program, m_uShader[VERTEX_SHADER] );
	}
	if (m_uShader[FRAGMENT_SHADER] != 0)
	{
		glAttachShader( m_program, m_uShader[FRAGMENT_SHADER] );
	}
	if (m_uShader[GEOMETRY_SHADER] !=0 )
	{
		glAttachShader( m_program, m_uShader[GEOMETRY_SHADER] );
	}
	GLint	status;
	//连接program
	glLinkProgram( m_program );
	
	glGetProgramiv( m_program, GL_LINK_STATUS, &status );
	if (status == GL_FALSE)
	{
		GLint 	 infoLogLength;
		glGetProgramiv( m_program, GL_INFO_LOG_LENGTH, &infoLogLength );
		GLchar* szLogo = new GLchar[infoLogLength];
		glGetProgramInfoLog( m_program, infoLogLength, NULL, szLogo );
		cerr << "Program error:" <<szLogo << endl;
		delete[] szLogo;
	}
	glDeleteShader( m_uShader[VERTEX_SHADER] );
	glDeleteShader( m_uShader[FRAGMENT_SHADER] );
	glDeleteShader( m_uShader[GEOMETRY_SHADER] );

}

void GLshader::Use()
{
	glUseProgram( m_program );
}

void GLshader::Unuse()
{
	glUseProgram( 0 );
}

void GLshader::addAttribute( const string & _attribute )
{
	m_attributeList[_attribute] = glGetAttribLocation( m_program, _attribute.c_str() );
}

void GLshader::addUniform( const string& _uniform )
{
	m_uniformList[_uniform] = glGetUniformLocation( m_program, _uniform.c_str() );
}

GLuint GLshader::operator()( const string &uniform )
{
	return m_uniformList[uniform];
}

GLuint GLshader::operator[]( const string & attribute )
{
	return m_attributeList[attribute];
}

void GLshader::DeleteShaderProgram()
{
	glDeleteProgram(m_program);
}
