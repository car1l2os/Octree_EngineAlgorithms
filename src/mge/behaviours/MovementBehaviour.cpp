#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"

MovementBehaviour::MovementBehaviour() :AbstractBehaviour()
{
	m_speed = { 0.0f,0.0f,0.0f };
}

MovementBehaviour::MovementBehaviour(glm::vec3 startingSpeed, AABB *bounds) :AbstractBehaviour()
{
	m_speed = startingSpeed;
	m_bounds = bounds;
}

MovementBehaviour::~MovementBehaviour()
{
	//dtor
}

bool MovementBehaviour::update(float pStep) //delta time tiene que ser constante o habra problemas 
{
	_owner->translate(pStep * m_speed);
	_owner->_boundingBox->Max += m_speed*pStep;
	_owner->_boundingBox->Min += m_speed*pStep;

	glm::vec3 tmpPos = _owner->getWorldPosition();
	if (tmpPos.x > m_bounds->Max.x || tmpPos.x < m_bounds->Min.x)
	{
		m_speed.x *= -1;
		//std::cout << "X bound detection" << std::endl;
	}
	if (tmpPos.y > m_bounds->Max.y || tmpPos.y < m_bounds->Min.y)
	{
		m_speed.y *= -1;
		//std::cout << "Y bound detection" << std::endl;

	}
	if (tmpPos.z > m_bounds->Max.z || tmpPos.z < m_bounds->Min.z)
	{
		m_speed.z *= -1;
		//std::cout << "Z bound detection" << std::endl;
	}


	/*glm::vec3 pos = _owner->getWorldPosition();
	std::cout << "X position: " << pos.x << std::endl;
	std::cout << "Y position: " << pos.y << std::endl;
	std::cout << "Z position: " << pos.z << std::endl;
	std::cout << "-------------------------" << std::endl;*/


	if (m_speed.x == 0 && m_speed.y == 0 && m_speed.z == 0)
		return false;
	return true;
}




