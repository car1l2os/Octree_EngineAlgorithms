#pragma once
#include "Collider.hpp"

class AABB : public Collider 
{
public:

	AABB(glm::vec3 min, glm::vec3 max);
	~AABB();
	int type() { // used for swich test
		return 1;
	}

	bool collidesWith(Collider * other);
	bool collidesWith(AABB * other);
	bool collidesWith(OBB * other);

	bool Contains(Collider * compare_to);
	bool Contains(AABB * compare_to);
	bool Contains(OBB * compare_to);

	bool IsBeingContainedFor(AABB * compare_to);
	bool IsBeingContainedFor(OBB * compare_to);
};

