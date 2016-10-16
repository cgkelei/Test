#include "Camera.h"


Camera::Camera() :m_fnear(0.1f), m_ffar(1000.0f)
{
}


Camera::~Camera()
{
}

void Camera::SetProjection(const float fovy, const float aspectRatio, const float near /*= 0.1f*/, const float far /*= 1000.0f*/)
{
	m_MP = glm::perspective(fovy, aspectRatio, near, far);
	m_fnear = near;
	m_ffar  = far;
	m_faspect = aspectRatio;
	m_ffov = fovy;
}

void Camera::Update()
{

}

void Camera::Rotate(const float yaw, const float ptich, const float roll)
{
	m_fyaw   = glm::radians(yaw);
	m_fpitch = glm::radians(ptich);
	m_froll  = glm::radians(roll);
	Update();
}

const glm::mat4 Camera::GetViewMatrix() const
{
	return m_MV;
}

const glm::mat4 Camera::GetProjectionMatrix() const
{
	return m_MP;
}

void Camera::SetPosition(const glm::vec3& _position)
{
	m_vposition = _position;
}

const glm::vec3 Camera::GetPosition() const
{
	return m_vposition;
}

void Camera::SetFov(const float _fov)
{
	m_ffov = _fov;
	m_MP = glm::perspective(_fov, m_faspect, m_fnear, m_ffar);
}

const float Camera::GetFov() const
{
	return m_ffov;
}

const float Camera::GetAspectRation() const
{
	return  m_faspect;
}

glm::vec3 Camera::m_up = glm::vec3(0,1,0);
