#include "FreeCamera.h"
#include <gtx/euler_angles.hpp>

FreeCamera::FreeCamera()
{
	m_translation = glm::vec3(0);
	m_fSpeed = 0.2f;
}

FreeCamera::~FreeCamera()
{

}

void FreeCamera::Update()
{
	glm::mat4 R = glm::yawPitchRoll(m_fyaw, m_fpitch, m_froll);
	m_vposition += m_translation;
	m_vlook = glm::vec3(R*glm::vec4(0, 0, 1, 0));
	m_vup = glm::vec3(R*glm::vec4(0, 1, 0, 0));

	m_vright = glm::cross(m_vlook, m_vup);
	glm::vec3 tgt = m_vposition + m_vlook;
	m_MV = glm::lookAt(m_vposition, tgt, m_vup);

	//m_vlook = glm::normalize(m_vlook);
	//m_up = glm::normalize(m_up);
	//m_vright = glm::normalize(m_vright);
}

void FreeCamera::Walk(const float _walk)
{
	m_translation += (m_vlook*m_fSpeed*_walk);
	Update();
}

void FreeCamera::UP(const float value)
{
	m_translation += (m_vup*m_fSpeed*value);
	Update();
}

void FreeCamera::Left(const float _left)
{
	m_translation += (m_vright*m_fSpeed*_left);
	Update();
}

void FreeCamera::SetTranslation(const glm::vec3& t)
{
	m_translation = t;
	Update();
}

glm::vec3 FreeCamera::GetTranslation() const
{
	return  m_translation;
}

void FreeCamera::SetSpeed(const float _speed)
{
	m_fSpeed = _speed;
}

const float FreeCamera::GetSpeed() const
{
	return m_fSpeed;
}
