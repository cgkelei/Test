#ifndef SHAER_H
#define SHAER_H
#include "statusCode.h"
#include<GL/glew.h>
#include <string>
#include <map>
using namespace std;
class Shader
{
public:
	
public:
	Shader();
	~Shader();
	STATUS LoadFromString( const char* _file, GLenum _whichShader);
	STATUS LoadFromFile( const char* _fileName ,GLenum _whichShader);
	void   CreateAndLink();
	void   Use();
	void   UnUse();
	void   AddAttribute( const string& _attribute );
	void   AddUniform( const string& _uniform );
	GLuint operator[]( const string& _uniform );
	GLuint operator()( const string& _attribute );
	void   DeleteShaderProgram();

private:
	enum SHADERTYPE{ VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
	GLuint					m_program;
	int						totalShaders;
	GLuint					m_shaders[3];
	map<string, GLuint>		m_uniformList;
	map<string, GLuint>		m_attributeList;
};


#endif // !SHAER_H
