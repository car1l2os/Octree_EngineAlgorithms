#pragma once
#include "mge\core\GameObject.hpp"
#include "glm.hpp"

class AABB;
class OBB;

class Collider
{
public:
	GameObject * m_gameObject;

	Collider(glm::vec3 center, glm::vec3 halfSize);
	~Collider();

	virtual int type() { // used for swich test
		return 0;
	}
	virtual bool collidesWith(Collider * other) = 0;
	virtual bool collidesWith(AABB * other) = 0;
	virtual bool collidesWith(OBB * other) = 0;

	// all specific checks todo, statics
	static bool isColliding(AABB * one, AABB * other);
	static bool isColliding(AABB * one, OBB * other);
	static bool isColliding(OBB * one, OBB * other);

	virtual bool Contains(Collider * compare_to) = 0;
	virtual bool Contains(AABB * compare_to) = 0;
	virtual bool Contains(OBB * compare_to) = 0;

	// all specific checks todo, statics
	static bool isContaining(AABB * one, AABB * other);
	static bool isContaining(AABB * one, OBB * other);

	static bool isContaining(OBB * one, OBB * other);
	static bool isContaining(OBB * one, AABB * other);

	virtual bool IsBeingContainedFor(AABB * other) = 0;
	virtual bool IsBeingContainedFor(OBB * other) = 0;

	//OBB & AABB
	glm::vec3 Max;
	glm::vec3 Min;
	glm::vec3 m_halfSize;
	glm::vec3 _center;


protected:
	bool _colliding;

private:
	static double SquaredDistPointAABB(glm::vec3 & p, const AABB & aabb);
};

