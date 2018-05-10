#pragma once
#include "Collider.hpp"

class OBB : public Collider
{
public:

	OBB(glm::vec3 min, glm::vec3 max);
	~OBB();	
	int type() { // used for swich test
		return 2;
	}

	bool collidesWith(Collider * other);
	bool collidesWith(OBB * other);
	bool collidesWith(AABB * other);

	bool Contains(Collider * compare_to);
	bool Contains(AABB * compare_to);
	bool Contains(OBB * compare_to);

	bool IsBeingContainedFor(AABB * compare_to);
	bool IsBeingContainedFor(OBB * compare_to);

	//OBB
	glm::mat4 m_orientation;
};

