#include "Texture.h"


Texture::Texture(const std::string &_name)
{
	m_textureIDList.clear();
	m_textureId = 0;
	m_textureList.clear();
	m_texture = cv::imread(_name);
	width = m_texture.cols;
	height = m_texture.rows;
	GenTexture();
}


Texture::~Texture()
{
	m_textureIDList.clear();
	m_textureId = 0;
	m_textureList.clear();
	m_texture.release();
}

void Texture::GenTexture()
{
	glGenTextures(1, &m_textureId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	m_textureIDList.push_back(m_textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	GLubyte *pData = m_texture.data;
	//allocate Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pData);

	glGenerateMipmap(GL_TEXTURE_2D);
	m_texture.release();

}

void Texture::AddTexture(const std::string & _name)
{

}

const GLuint Texture::GetTextureID() const
{
	return m_textureId;
}
