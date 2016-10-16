/*!
 * \class RenderObject
 *
 * \brief This base class is used to create subclasses that can be rendered
 *
 * \author kelei
 * \date ʮ�� 2016
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

	virtual int GetTotalVertex() = 0;								//��������
	virtual int GettotlIndices() = 0;								//��������
	virtual GLenum GetPrimitiveType() = 0;							//��������
	virtual void SetColor(glm::vec3 &_color);						//

	virtual void FillVertexBuffer(GLfloat* pBuffer) = 0;			//�����һ�¶���
	virtual  void FillIndicesBuffer(GLuint* pbuffer) = 0;			//�����һ������
	
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
