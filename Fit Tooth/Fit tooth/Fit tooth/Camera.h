#ifndef CAMERA_H_
#define CAMERA_H_
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
class Camera
{
public:
	Camera();
    virtual ~Camera();
	void SetProjection(const float fovy,const float aspectRatio,const float near = 0.1f,const float far = 1000.0f);
	virtual void Update() = 0;
	virtual void Rotate(const float yaw, const float ptich, const float roll);
	const glm::mat4 GetViewMatrix()const;
	const glm::mat4 GetProjectionMatrix()const;
	void SetPosition(const glm::vec3& _position);
	const glm::vec3 GetPosition()const;
	void SetFov(const float _fov);
	const float GetFov()const;
	const float GetAspectRation()const;
protected:
	float m_fyaw, m_fpitch, m_froll;
	float m_faspect, m_fnear, m_ffar,m_ffov;
	static glm::vec3 m_up;
	glm::vec3 m_vlook;
	glm::vec3 m_vup;
	glm::vec3 m_vright;
	glm::vec3 m_vposition;
	glm::mat4 m_MV;
	glm::mat4 m_MP;

};


#endif // !CAMERA_H_
