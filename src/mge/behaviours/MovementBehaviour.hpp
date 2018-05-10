#ifndef MOVEMENTBEHAVIOUR_HPP
#define MOVEMENTBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/octree/AABB.hpp"



class MovementBehaviour : public AbstractBehaviour
{
public:
	MovementBehaviour();
	MovementBehaviour(glm::vec3 startingSpeed, AABB *bounds);
	virtual ~MovementBehaviour();

	virtual bool update(float pStep);
	glm::vec3 m_speed;
	AABB* m_bounds;
};

#endif // ROTATINGBEHAVIOUR_HPP
