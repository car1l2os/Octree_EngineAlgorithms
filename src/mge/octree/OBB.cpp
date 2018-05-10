#pragma once
#include "OBB.hpp"

OBB::OBB(glm::vec3 min, glm::vec3 max) : Collider(max/2,(min-max)/2)
{
	Max = max;
	Min = min;
}
OBB::~OBB()
{
}

bool OBB::collidesWith(Collider * other) { // call other providing this correct type
	return other->collidesWith(this);
}
bool OBB::collidesWith(AABB * other) {
	return isColliding(other, this); // note the order of args
}
bool OBB::collidesWith(OBB * other) {
	return isColliding(this, other);
}


bool OBB::Contains(Collider * compare_to) {
	return compare_to->Contains(this);
}
bool OBB::Contains(AABB * compare_to) {
	return isContaining(this, compare_to);
}
bool OBB::Contains(OBB * compare_to) {
	return isContaining(this, compare_to);
}

bool OBB::IsBeingContainedFor(AABB * compare_to)
{
	return isContaining(compare_to, this);
}

bool OBB::IsBeingContainedFor(OBB * compare_to)
{
	return isContaining(compare_to, this);
}

