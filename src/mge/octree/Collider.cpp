#pragma once
#include "Collider.hpp"
#include "AABB.hpp"
#include "OBB.hpp"
#include "TestManager.hpp"


Collider::Collider(glm::vec3 center, glm::vec3 halfSize)
	: _center(center), m_halfSize(halfSize)
{
}
Collider::~Collider()
{
	//dtor
}
//Colisiona
bool Collider::isColliding(AABB * one, AABB * other)
{
	TestManager::collisionTests++;
	//http://www.miguelcasillas.com/?p=30
	//Check if Box1's max is greater than Box2's min and Box1's min is less than Box2's max
	return(one->Max.x > other->Min.x &&
		one->Min.x < other->Max.x &&
		one->Max.y > other->Min.y &&
		one->Min.y < other->Max.y &&
		one->Max.z > other->Min.z &&
		one->Min.z < other->Max.z);
}
bool Collider::isColliding(AABB * one, OBB * other)
{
	TestManager::collisionTests++;
	glm::vec3 oneCenter = one->m_gameObject->getWorldPosition(); // object's pos = collider center
	glm::mat4 oneTransform = glm::scale(one->m_gameObject->getTransform(), one->m_halfSize); // scaling for halfsize
	glm::vec3 otherCenter = other->m_gameObject->getWorldPosition();
	glm::mat4 otherTransform = glm::scale(other->m_gameObject->getTransform(), other->m_halfSize);

	for (int a = 0; a < 3; a++) {
		glm::vec3 l = glm::vec3(oneTransform[a]); // one axis to project on
		float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
		float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
		float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
		float penetration = (ra + rb) - tl;
		if (penetration <= 0) { // no overlap
			return false;
		}
	}
	for (int b = 0; b < 3; b++) {
		glm::vec3 l = glm::vec3(otherTransform[b]); // other axis to project on
		float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
		float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
		float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
		float penetration = (ra + rb) - tl;
		if (penetration <= 0) { // no overlap
			return false;
		}
	}
	for (int a = 0; a < 3; a++) {
		glm::vec3 aAxis = glm::vec3(oneTransform[a]);
		for (int b = 0; b < 3; b++) {
			glm::vec3 bAxis = glm::vec3(otherTransform[b]);
			if (aAxis != bAxis) {
				glm::vec3 l = glm::cross(aAxis, bAxis); // has flaw when axis are same, result in (0,0,0), solved by if
				float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
				float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
				float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
				float penetration = (ra + rb) - tl;
				if (penetration <= 0) { // no overlap
					return false;
				}
			}
		}
	}
	return true;
}
bool Collider::isColliding(OBB * one, OBB * other)
{
	TestManager::collisionTests++;
	glm::vec3 oneCenter = one->m_gameObject->getWorldPosition(); // object's pos = collider center
	glm::mat4 oneTransform = glm::scale(one->m_gameObject->getTransform(), one->m_halfSize); // scaling for halfsize
	glm::vec3 otherCenter = other->m_gameObject->getWorldPosition();
	glm::mat4 otherTransform = glm::scale(other->m_gameObject->getTransform(), other->m_halfSize);

	for (int a = 0; a < 3; a++) {
		glm::vec3 l = glm::vec3(oneTransform[a]); // one axis to project on
		float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
		float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
		float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
		float penetration = (ra + rb) - tl;
		if (penetration <= 0) { // no overlap
			return false;
		}
	}
	for (int b = 0; b < 3; b++) {
		glm::vec3 l = glm::vec3(otherTransform[b]); // other axis to project on
		float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
		float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
		float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
		float penetration = (ra + rb) - tl;
		if (penetration <= 0) { // no overlap
			return false;
		}
	}
	for (int a = 0; a < 3; a++) {
		glm::vec3 aAxis = glm::vec3(oneTransform[a]);
		for (int b = 0; b < 3; b++) {
			glm::vec3 bAxis = glm::vec3(otherTransform[b]);
			if (aAxis != bAxis) {
				glm::vec3 l = glm::cross(aAxis, bAxis); // has flaw when axis are same, result in (0,0,0), solved by if
				float tl = std::abs(glm::dot(l, otherCenter) - glm::dot(l, oneCenter)); // center distance
				float ra = std::abs(glm::dot(l, glm::vec3(oneTransform[0]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[1]))) + std::abs(glm::dot(l, glm::vec3(oneTransform[2])));
				float rb = std::abs(glm::dot(l, glm::vec3(otherTransform[0]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[1]))) + std::abs(glm::dot(l, glm::vec3(otherTransform[2])));
				float penetration = (ra + rb) - tl;
				if (penetration <= 0) { // no overlap
					return false;
				}
			}
		}
	}
	return true;
}


//Contiene
bool Collider::isContaining(AABB * one, AABB * other)
{
	//cout << "AABB-AABB" << endl;
	TestManager::fitTests++;
	if (one->Min[0] < other->Min[0] && one->Min[1] < other->Min[1] && one->Min[2] < other->Min[2]
		&& one->Max[0] > other->Max[0] && one->Max[1] > other->Max[1] && one->Max[2] > other->Max[2])
		return true;
	return false;
}
bool Collider::isContaining(AABB * one, OBB * other)
{
	TestManager::fitTests++;
	if (one->Min[0] < other->Min[0] && one->Min[1] < other->Min[1] && one->Min[2] < other->Min[2]
		&& one->Max[0] > other->Max[0] && one->Max[1] > other->Max[1] && one->Max[2] > other->Max[2])
		return true;
	return false;
}
bool Collider::isContaining(OBB * one, OBB * other) {
	TestManager::fitTests++;
	if (one->Min[0] < other->Min[0] && one->Min[1] < other->Min[1] && one->Min[2] < other->Min[2]
		&& one->Max[0] > other->Max[0] && one->Max[1] > other->Max[1] && one->Max[2] > other->Max[2])
		return true;
	return false;
}
bool Collider::isContaining(OBB * one, AABB * other) {
	TestManager::fitTests++;
	if (one->Min[0] < other->Min[0] && one->Min[1] < other->Min[1] && one->Min[2] < other->Min[2]
		&& one->Max[0] > other->Max[0] && one->Max[1] > other->Max[1] && one->Max[2] > other->Max[2])
		return true;
	return false;
}

bool Collider::IsBeingContainedFor(AABB * compare_to)
{
	return compare_to->Contains(this);
}

bool Collider::IsBeingContainedFor(OBB * compare_to)
{
	return compare_to->Contains(this);
}

double Collider::SquaredDistPointAABB(glm::vec3 & p, const AABB & aabb)
{
	auto check = [&](
		const double pn,
		const double bmin,
		const double bmax) -> double
	{
		double out = 0;
		double v = pn;

		if (v < bmin)
		{
			double val = (bmin - v);
			out += val * val;
		}

		if (v > bmax)
		{
			double val = (v - bmax);
			out += val * val;
		}

		return out;
	};

	// Squared distance
	double sq = 0.0;

	sq += check(p.x, aabb.Min.x, aabb.Max.x);
	sq += check(p.y, aabb.Min.y, aabb.Max.y);
	sq += check(p.z, aabb.Min.z, aabb.Max.z);

	return sq;
}





