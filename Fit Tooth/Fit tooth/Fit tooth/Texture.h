#ifndef Texture_H_
#define Texture_H_
#include <string>
#include <opencv2/opencv.hpp>
#include <map>
#include <GL/glew.h>
#include <vector>
class Texture
{
public:
	Texture(const std::string &_name);
	~Texture();
	void GenTexture();
	void AddTexture(const std::string & _name);
	const GLuint GetTextureID()const;
	
private:
	std::string m_szName;

	std::map<std::string, GLuint> m_textureList;
	GLuint m_textureId;
	std::vector <GLuint> m_textureIDList;
	cv::Mat		m_texture;
	int width;
	int height;

};


#endif // !Texture_H_
