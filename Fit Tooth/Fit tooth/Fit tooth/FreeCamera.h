#ifndef FREECAMERA_H_
#define FREECAMERA_H_
#include "Camera.h"
class FreeCamera :
	public Camera
{
public:
	FreeCamera();
	~FreeCamera();

	virtual void Update() override;

	void Walk(const float _walk);
	void UP(const float _value);
	void Left(const float _left);

	void SetTranslation(const glm::vec3& t);
	glm::vec3 GetTranslation()const;
	void SetSpeed(const float _speed);
	const float GetSpeed()const;
protected:
	float m_fSpeed;
	glm::vec3 m_translation;


};


#endif // !FREECAMERA_H_
