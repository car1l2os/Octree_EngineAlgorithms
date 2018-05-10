#pragma once
#include "AABB.hpp"

AABB::AABB(glm::vec3 min, glm::vec3 max) : Collider(max / 2, (min - max) / 2)
{
	Max = max;
	Min = min;
}
AABB::~AABB()
{

}

bool AABB::collidesWith(Collider * other) { // call other providing this correct type
	return other->collidesWith(this);
}
bool AABB::collidesWith(AABB * other) {
	return isColliding(this, other);
}
bool AABB::collidesWith(OBB * other) {
	return isColliding(this, other);
}

bool AABB::Contains(Collider * compare_to) {
	return compare_to->IsBeingContainedFor(this);
}

bool AABB::Contains(AABB * compare_to) {
	return isContaining(this, compare_to);
}
bool AABB::Contains(OBB * compare_to) {
	return isContaining(this, compare_to);
}

bool AABB::IsBeingContainedFor(AABB * compare_to)
{
	return isContaining(compare_to,this);
}

bool AABB::IsBeingContainedFor(OBB * compare_to)
{
	return isContaining(compare_to, this);
}


