#include "Grid.h"


Grid::Grid(int width, int height) :m_nWidth(width), m_nHeight(height)
{

	m_fcolor[0] = 0.5f;
	m_fcolor[1] = 0.5f;
	m_fcolor[2] = 0.5f;

	if (!m_Shader.LoadFormFile("shaders/grid.vert", GL_VERTEX_SHADER))
	{
		cerr << "Grid Shader Load is Failed" << endl;
	}
	if (!m_Shader.LoadFormFile("shaders/grid.frag", GL_FRAGMENT_SHADER))
	{
		cerr << "Grid Shader Load is failed" << endl;
	}
	m_Shader.CreateAndLinkProgram();
	m_Shader.Use();
		m_Shader.addAttribute("vVertex");
		m_Shader.addUniform("MVP");
		m_Shader.addUniform("vColor");
		glUniform3f(m_Shader("vColor"), m_fcolor[0], m_fcolor[1], m_fcolor[2]);
	m_Shader.Unuse();
	//线框初如化颜色

	Init();
}

Grid::~Grid()
{
}

void Grid::SetGrid(int width, int height)
{
	m_nWidth  = width;
	m_nHeight = height;
}

void Grid::FillIndicesBuffer(GLuint* pbuffer)
{
	GLuint *pIndex = pbuffer;
	for (int i = 0; i <m_nWidth*m_nHeight;i+=4)
	{
		*pIndex++ = i;
		*pIndex++ = i + 1;
		*pIndex++ = i + 2;
		*pIndex++ = i + 3;
	}
}

void Grid::FillVertexBuffer(GLfloat* pBuffer)
{
	glm::vec3 *vertices = (glm::vec3*)(pBuffer);
	int count = 0;
	int width = m_nWidth / 2;
	int height = m_nHeight / 2;
	for (int i = -width; i <= width; i++)
	{
		vertices[count++] = glm::vec3(i, 0, -height);
		vertices[count++] = glm::vec3(i, 0, height);

		vertices[count++] = glm::vec3(-width, 0, i);
		vertices[count++] = glm::vec3(width, 0, i);
	}

}

GLenum Grid::GetPrimitiveType()
{
	return GL_LINES;
}

int Grid::GetTotalVertex()
{
	return ((m_nWidth + 1) + (m_nHeight + 1)) * 2;
}

int Grid::GettotlIndices()
{
	return (m_nWidth * m_nHeight);
}

void Grid::SetCustomUniforms()
{
	glUniform3f(m_Shader("vColor"), m_fcolor[0],m_fcolor[1],m_fcolor[2]);
}

void Grid::SetColor(glm::vec3& _color)
{
	RenderObject::SetColor(_color);
}

