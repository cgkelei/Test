#ifndef GSHADER_H
#define GSHADER_H
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <map>
using namespace std;
class gShader
{
public:
	gShader(void);
	~gShader(void);
public:
	bool LoadFromString( string _path, GLenum _type );
	bool LoadFromFile( string _path, GLenum _whichShader );
	void CreateAndLink();
	void Use();
	void UnUse();
	void DeleteProgram();
	void adduniform(string _str);
	void addattribute(string _str);
	GLuint operator[]( string _attribute );
	GLuint operator()( string _uniform );
private:
	enum ShaderType{VERTEX_SHADER,FRAGMENT_SHADER,GEOMETRY_SHADER};
	int m_totalShaders;
	GLuint Shaders[3];
	GLuint _program;
	map<string, GLuint> m_attributeList;
	map<string, GLuint> m_uniformList;

};


#endif // !GSHADER_H
