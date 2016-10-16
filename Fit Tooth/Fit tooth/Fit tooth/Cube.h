#pragma once
#include "RenderObject.h"
class Cube :public RenderObject
{
public:
	Cube();
	~Cube();

	virtual void FillIndicesBuffer(GLuint* pbuffer) override;


	virtual void FillVertexBuffer(GLfloat* pBuffer) override;


	virtual GLenum GetPrimitiveType() override;


	virtual int GetTotalVertex() override;


	virtual int GettotlIndices() override;


	virtual void SetCustomUniforms() override;

};

