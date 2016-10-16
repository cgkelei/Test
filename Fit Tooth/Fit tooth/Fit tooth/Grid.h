#ifndef  GRID_H_
#define  GRID_H_
#include "RenderObject.h"
class Grid :
	public RenderObject
{
public:
	Grid(int width = 10,int height = 10);
	virtual ~Grid();
	void SetGrid(int width, int height);


	virtual void FillIndicesBuffer(GLuint* pbuffer) override;


	virtual void FillVertexBuffer(GLfloat* pBuffer) override;


	virtual GLenum GetPrimitiveType() override;


	virtual int GetTotalVertex() override;


	virtual int GettotlIndices() override;

	void SetCustomUniforms();

	void SetColor(glm::vec3& _color);
private:
	int m_nWidth;
	int m_nHeight;

};


#endif // ! GRID_H_
