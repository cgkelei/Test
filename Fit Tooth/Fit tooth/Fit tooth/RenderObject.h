/*!
 * \class RenderObject
 *
 * \brief This base class is used to create subclasses that can be rendered
 *
 * \author kelei
 * \date 十月 2016
 */
#ifndef RENDEROBJECT_H
#include <iostream>
#include <string>
#include "GLshader.h"
#include <glm.hpp>
#include "Texture.h"
class RenderObject
{
public:
	RenderObject();
	virtual ~RenderObject();
	void Render(float *MVP);

	virtual int GetTotalVertex() = 0;								//顶点数量
	virtual int GettotlIndices() = 0;								//索引数量
	virtual GLenum GetPrimitiveType() = 0;							//物体类型
	virtual void SetColor(glm::vec3 &_color);						//

	virtual void FillVertexBuffer(GLfloat* pBuffer) = 0;			//来填充一下顶点
	virtual  void FillIndicesBuffer(GLuint* pbuffer) = 0;			//来填充一下索引
	
	void Init();
	void Destory();
	virtual  void SetCustomUniforms();
	GLshader*	GetShader();

protected:
	GLuint		VAOID;
	GLuint		VBOID;
	GLuint		EBOID;
	GLuint		TBOID;
	GLenum		m_priType;
	GLint		m_totalVertices;
	GLint		m_totalIndices;
	GLshader	m_Shader;

	GLfloat		m_fcolor[3];
	GLboolean	m_bIsSupperTexture;
	Texture		*m_texture;
	string		m_textureName;


};


#endif // !RENDEROBJECT_H
