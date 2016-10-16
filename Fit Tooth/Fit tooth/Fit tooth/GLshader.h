#pragma once
#include <iostream>
#include <Gl/glew.h>
#include <string>
#include <map>
using namespace std;
class GLshader
{
public:
	GLshader();
	~GLshader();
	bool LoadFormFile( const string& _fileName, GLenum whichShader );
	bool LoadFromString( const string& _stringstream, GLenum whichShader );
	void CreateAndLinkProgram();
	void Use();
	void Unuse();
	void addAttribute( const string & _attribute );
	void addUniform( const string& _uniform );
	GLuint operator()( const string &uniform );
	GLuint operator[]( const string & attribute );
	void DeleteShaderProgram();
private:
	enum ShaderType{VERTEX_SHADER,FRAGMENT_SHADER,GEOMETRY_SHADER};	  
	GLuint				m_program;
	int					m_totalShaders;
	GLuint				m_uShader[3];
	map<string, GLuint> m_attributeList;
	map<string, GLuint> m_uniformList;

};

