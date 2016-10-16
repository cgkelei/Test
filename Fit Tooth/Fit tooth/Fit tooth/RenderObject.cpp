#include "RenderObject.h"



RenderObject::RenderObject() :m_totalVertices(0), m_totalIndices(0)

{


}

RenderObject::~RenderObject()
{
	Destory();
}

void RenderObject::Render(float *MVP)
{
	m_Shader.Use();
	if (MVP != NULL)
	{
		glUniformMatrix4fv(m_Shader("MVP"), 1, GL_FALSE, MVP);
		SetCustomUniforms();
		glBindVertexArray(VAOID);
		glDrawElements(m_priType, m_totalIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	m_Shader.Unuse();
}

int RenderObject::GetTotalVertex()
{
	return m_totalVertices;
}

int RenderObject::GettotlIndices()
{
	return m_totalIndices;
}

GLenum RenderObject::GetPrimitiveType()
{
	return m_priType;
}

void RenderObject::SetColor(glm::vec3 &_color)
{
	m_fcolor[0] = _color.r;
	m_fcolor[1] = _color.g;
	m_fcolor[2] = _color.b;
}

void RenderObject::Init()
{
	glGenVertexArrays(1, &VAOID);
	glGenBuffers(1, &VBOID);
	glGenBuffers(1, &EBOID);

	m_totalVertices = GetTotalVertex();
	m_totalIndices = GettotlIndices();
	m_priType = GetPrimitiveType();


	glBindVertexArray(VAOID);

	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*m_totalVertices, 0, GL_STATIC_DRAW);

	GLfloat* pBuffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	FillVertexBuffer(pBuffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glEnableVertexAttribArray(m_Shader["vVertex"]);
	glVertexAttribPointer(m_Shader["vVertex"], 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_totalIndices*sizeof(GLuint), 0, GL_STATIC_DRAW);

	GLuint *pIndex = static_cast<GLuint*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	FillIndicesBuffer(pIndex);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	//Cancel bind
	glBindVertexArray(0);

	if (m_bIsSupperTexture)
	{	
		m_texture = new Texture(m_textureName);
		
	}

}

void RenderObject::Destory()
{
	m_Shader.DeleteShaderProgram();
	glDeleteBuffers(1, &VBOID);
	glDeleteBuffers(1, &EBOID);
	glDeleteBuffers(1, &VAOID);
}

void RenderObject::SetCustomUniforms()
{
	
}

GLshader* RenderObject::GetShader()
{
	return &m_Shader;
}
