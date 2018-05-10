#pragma once
#include "IntersectionRecord.hpp"


IntersectionRecord::IntersectionRecord()
{
	m_intersectedObject1 = nullptr;
	m_intersectedObject2 = nullptr;
}
IntersectionRecord::IntersectionRecord(GameObject* intersectedObject1, GameObject* intersectedObject2) //not really good pass arraysw https://stackoverflow.com/questions/9426932/how-do-i-pass-an-array-to-a-constructor
{
	m_intersectedObject1 = intersectedObject1;
	m_intersectedObject2 = intersectedObject2;
}
IntersectionRecord::~IntersectionRecord()
{
	m_intersectedObject1 = nullptr;
	m_intersectedObject2 = nullptr;
}

bool IntersectionRecord::Equals(IntersectionRecord* otherRecord)
{
		if (otherRecord == nullptr)
			return false;
		if (otherRecord->m_intersectedObject1 == m_intersectedObject1 && otherRecord->m_intersectedObject2 == m_intersectedObject2)
			return true;
		if (otherRecord->m_intersectedObject1 == m_intersectedObject2 && otherRecord->m_intersectedObject2 == m_intersectedObject1)
			return true;
		return false;
	return false;
}


