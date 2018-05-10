#pragma once
#include "mge/core/GameObject.hpp"

class IntersectionRecord
{
public:

	IntersectionRecord();
	IntersectionRecord(GameObject* intersectedObject1, GameObject* intersectedObject2);
	~IntersectionRecord();
	bool Equals(IntersectionRecord* otherRecord);

	GameObject* m_intersectedObject1;
	GameObject* m_intersectedObject2;
};

