#pragma once
#include "Octree.hpp"
#include "IntersectionRecord.hpp"
#include "OBB.hpp"
#include "AABB.hpp"

#include "mge\octree\TestManager.hpp"


/*
to do the "space boxes" better a class with the info or maths every time?
--> im going to try it with maths idk
*/


Octree::Octree(AABB* region, int levelsLeft) : levels(levelsLeft)
{
	m_region = region;
	if (levelsLeft == 0)
		m_isLeaf = true;
	else
	{
		m_isLeaf = false;
		BuildTree();
		for (int i = 0;i < 8;i++)
		{
			m_childNode[i] = new Octree(m_octant[i], levelsLeft - 1);
			m_childNode[i]->_parent = this;
		}
	}
}
Octree::Octree(AABB* region)
{
	m_region = region;
}

Octree::~Octree()
{
	/*if (m_isLeaf == false)
	{
		for (int i = 0;i < 8;i++)
		{
			delete m_childNode[i];
			m_childNode[i] = nullptr;
			delete m_octant[i];
			m_octant[i] = nullptr;
		}
	}*/

	/*for (list<GameObject*>::iterator it = m_objects.begin();it != m_objects.end();it++)
	{
		*it = nullptr;
	}

	for (list<GameObject*>::iterator it = to_insert.begin();it != to_insert.end();it++)
	{
		*it = nullptr;
	}
	_parent = nullptr;
	m_region = nullptr;*/
}

void Octree::BuildTree()
{
	glm::vec3 dimensions{ 0.0f,0.0f,0.0f };
	dimensions[0] = m_region->Max[0] - m_region->Min[0];
	dimensions[1] = m_region->Max[1] - m_region->Min[1];
	dimensions[2] = m_region->Max[2] - m_region->Min[2];

	/*Algo extraño que no creo que me pase*/
	/*if (dimensions[0] == 0 && dimensions[1] == 0 && dimensions[2] == 0)
	{
		//FindEnclosingCube(); //???
		dimensions[0] = m_region->Max[0] - m_region->Min[0];
		dimensions[1] = m_region->Max[1] - m_region->Min[1];
		dimensions[2] = m_region->Max[2] - m_region->Min[2];
	}*/

	//Check to see if the dimensions of the box are greater than the minimum dimensions
	if (dimensions[0] <= MIN_SIZE && dimensions[1] <= MIN_SIZE && dimensions[2] <= MIN_SIZE)
	{
		return;
	}

	float half[3];
	half[0] = dimensions[0] / 2.0f;
	half[1] = dimensions[1] / 2.0f;
	half[2] = dimensions[2] / 2.0f;

	float center[3];
	center[0] = m_region->Min[0] + half[0];
	center[1] = m_region->Min[1] + half[1];
	center[2] = m_region->Min[2] + half[2];

	//Create subdivided regions for each octant
	glm::vec3 tmp_min;
	glm::vec3 tmp_center;

	tmp_min = { m_region->Min[0], m_region->Min[1], m_region->Min[2] }; //Abajo a la izquierda 
	tmp_center = { center[0], center[1], center[2] };
	m_octant[0] = new AABB(tmp_min, tmp_center);

	tmp_min = { center[0] , m_region->Min[1], m_region->Min[2] };
	tmp_center = { m_region->Max[0], center[1], center[2] };
	m_octant[1] = new AABB(tmp_min, tmp_center);

	tmp_min = { center[0] , m_region->Min[1], center[2] };
	tmp_center = { m_region->Max[0], center[1], m_region->Max[2] };
	m_octant[2] = new AABB(tmp_min, tmp_center);

	tmp_min = { m_region->Min[0] , m_region->Min[1], center[2] };
	tmp_center = { center[0], center[1], m_region->Max[2] };
	m_octant[3] = new AABB(tmp_min, tmp_center);

	tmp_min = { m_region->Min[0] , center[1], m_region->Min[2] };
	tmp_center = { center[0], m_region->Max[1], center[2] };
	m_octant[4] = new AABB(tmp_min, tmp_center);

	tmp_min = { center[0] , center[1], m_region->Min[2] };
	tmp_center = { m_region->Max[0], m_region->Max[1], center[2] };
	m_octant[5] = new AABB(tmp_min, tmp_center);

	tmp_center = { center[0], center[1], center[2] };
	tmp_min = { m_region->Max[0], m_region->Max[1], m_region->Max[2] };
	m_octant[6] = new AABB(tmp_center, tmp_min);

	tmp_center = { m_region->Min[0], center[1], center[2] };
	tmp_min = { center[0], m_region->Max[1], m_region->Max[2] };
	m_octant[7] = new AABB(tmp_center, tmp_min);
}


void Octree::Insert(GameObject* Item)
{
	if (Item->_isStatic == false)
	{
		/*make sure we're not inserting an object any deeper into the tree than we have to.
		-if the current node is an empty leaf node, just insert and leave it.*/
		if (m_isLeaf)
		{
			to_insert.push_back(Item); //correct?
			return;
		}

		bool found = false;
		if (Item->_boundingBox->Max != Item->_boundingBox->Min) //Necesario?
		{
			if (m_region->Contains(Item->_boundingBox) == true)
			{
				//we will try to place the object into a child node. If we can't fit it in a child node, then we insert it into the current node object list.
				for (int a = 0;a < 8;a++)
				{
					//is the object fully contained within a quadrant?
					if (m_childNode[a]->m_region->Contains(Item->_boundingBox) == true)
					{
						m_childNode[a]->Insert(Item);   //Add the item into that tree and let the child tree figure out what to do with it
						found = true;
						break;
					}
				}
			}
		}
		if (!found) to_insert.push_back(Item);
	}
	else
	{
		/*make sure we're not inserting an object any deeper into the tree than we have to.
		-if the current node is an empty leaf node, just insert and leave it.*/
		if (m_isLeaf)
		{
			m_static_objects.push_back(Item); //correct?
			return;
		}

		bool found = false;
		if (Item->_boundingBox->Max != Item->_boundingBox->Min) //Necesario?
		{
			if (m_region->Contains(Item->_boundingBox) == true)
			{
				//we will try to place the object into a child node. If we can't fit it in a child node, then we insert it into the current node object list.
				for (int a = 0;a < 8;a++)
				{
					//is the object fully contained within a quadrant?
					if (m_childNode[a]->m_region->Contains(Item->_boundingBox) == true)
					{
						m_childNode[a]->Insert(Item);   //Add the item into that tree and let the child tree figure out what to do with it
						found = true;
						break;
					}
				}
			}
		}
		if (!found) m_static_objects.push_back(Item);
	}
}

std::string Octree::getInfo()
{
	std::string to_return = "";

	to_return += std::string("Objects:") + std::to_string(m_objects.size());
	for (int i = 0;i < 8;i++)
	{
		if (m_childNode[i] != nullptr)
			to_return += m_childNode[i]->getInfo();
	}
	return to_return;
}



void Octree::UpdateOctree()
{
	//supposed all the objects are going to be in movement 
	if (m_objects.size() != 0)
	{
		//If an object moved, we can insert it into the parent and that will insert it into the correct tree node.
		//note that we have to do this last so that we don't accidentally update the same object more than once per frame.
		list<GameObject*>::iterator it = m_objects.begin();
		while (it != m_objects.end())	//std::prev > --it in some cases http://en.cppreference.com/w/cpp/iterator/prev
		{
			GameObject* obj = *it;
			Octree* current = this;

			//figure out how far up the tree we need to go to reinsert our moved object
			//try to move the object into an enclosing parent node until we've got full containment
			while (current->m_region->Contains(obj->_boundingBox) == false)
			{
				if (current->_parent != NULL) current = current->_parent;
				else break;
			}
			//now, remove the object from the current node and insert it into the current containing node.
			m_objects.erase(it);
			it++;
			current->Insert(obj);   //this will try to insert the object as deep into the tree as we can go.
			//haciendolo asi cuando llegue al nodo en el que se ha metido este objeto lo volverá a comprobar.
			//optimizacion, pero por ahora funciona
		}
	}

	if (m_isLeaf == false)
	{
		for (int i = 0;i < 8;i++)
		{
			m_childNode[i]->UpdateOctree();
		}
	}
	//We merge to_insert --> m_objects
	m_objects.insert(m_objects.end(), to_insert.begin(), to_insert.end());
	to_insert.clear();
}

list<IntersectionRecord*>* Octree::GetIntersections(list<GameObject*>* parentObjs, list<IntersectionRecord*>* intersections) {

	if (intersections == nullptr)
		intersections = new list<IntersectionRecord*>;

	GameObject* one;
	GameObject* other;
	//assume all parent objects have already been processed for collisions against each other.
	//check all parent objects against all objects in our local node
	if (parentObjs != nullptr)
	{
		if (parentObjs->size() > 0)
		{
			for (list<GameObject*>::iterator it = parentObjs->begin();it != parentObjs->end();it++)
			{
				one = *it;
				for (list<GameObject*>::iterator it2 = m_objects.begin();it2 != m_objects.end();it2++) //non-static objects
				{
					other = *it2;
					//We let the two objects check for collision against each other. They can figure out how to do the coarse and granular checks.
					//all we're concerned about is whether or not a collision actually happened.
					if (one->_boundingBox->collidesWith(other->_boundingBox) == true)
					{
						TestManager::collisions++;
						intersections->push_back(new IntersectionRecord(one, other));
					}
				}
				for (list<GameObject*>::iterator it2 = m_static_objects.begin();it2 != m_static_objects.end();it2++) //static objects
				{
					other = *it2;
					//We let the two objects check for collision against each other. They can figure out how to do the coarse and granular checks.
					//all we're concerned about is whether or not a collision actually happened.
					if (one->_boundingBox->collidesWith(other->_boundingBox) == true)
					{
						TestManager::collisions++;
						intersections->push_back(new IntersectionRecord(one, other));
					}
				}
			}
		}
	}
	else
	{
		parentObjs = new list<GameObject*>; //we have to free this memory but it gives me an error
	}

	//now, check all our local objects against all other local objects in the node
	if (m_objects.size() > 1)
	{
		for (list<GameObject*>::iterator it = m_objects.begin();it != m_objects.end();it++)
		{
			one = *it;
			list<GameObject*>::iterator it2 = it;
			for (it2++;it2 != m_objects.end();it2++) //check ++it //non-static
			{
				other = *it2;
				if (one->_boundingBox->collidesWith(other->_boundingBox) == true)
				{
					TestManager::collisions++;
					intersections->push_back(new IntersectionRecord(one, other));
				}
			}
			for (it2 = m_static_objects.begin();it2 != m_static_objects.end();it2++) //check ++it //static
			{
				other = *it2;
				if (one->_boundingBox->collidesWith(other->_boundingBox) == true)
				{
					TestManager::collisions++;
					intersections->push_back(new IntersectionRecord(one, other));
				}
			}
		}
	}

	if (m_isLeaf == false)
	{
		//parentObjs->insert(parentObjs->end(),m_objects.begin(),m_objects.end()); //por qué con merge se eliminan los objetos?

		//each child node will give us a list of intersection records, which we then merge with our own intersection records.
		for (int i = 0;i < 8;i++)
		{
			//Prueba
			list<GameObject*>* to_pass = new list<GameObject*>;
			to_pass->insert(to_pass->end(), parentObjs->begin(), parentObjs->end());
			to_pass->insert(to_pass->end(), m_objects.begin(), m_objects.end());
			to_pass->insert(to_pass->end(), m_static_objects.begin(), m_static_objects.end());

			m_childNode[i]->GetIntersections(to_pass, intersections);
			delete to_pass;
			to_pass = nullptr;
		}
	}
	return intersections;
}

list<IntersectionRecord*>* Octree::GetStaticIntersections(list<GameObject*>* parentObjs, list<IntersectionRecord*>* intersections)
{
	if (intersections == nullptr)
		intersections = new list<IntersectionRecord*>;

	GameObject* one;
	GameObject* other;
	//assume all parent objects have already been processed for collisions against each other.
	//check all parent objects against all objects in our local node
	if (parentObjs != nullptr)
	{
		if (parentObjs->size() > 0)
		{
			for (list<GameObject*>::iterator it = parentObjs->begin();it != parentObjs->end();it++)
			{
				one = *it;
				for (list<GameObject*>::iterator it2 = m_static_objects.begin();it2 != m_static_objects.end();it2++)
				{
					other = *it2;
					//We let the two objects check for collision against each other. They can figure out how to do the coarse and granular checks.
					//all we're concerned about is whether or not a collision actually happened.
					if (one->_boundingBox->collidesWith(other->_boundingBox) == true)
					{
						TestManager::collisions++;
						intersections->push_back(new IntersectionRecord(one, other));
					}
				}
			}
		}
	}
	else
	{
		parentObjs = new list<GameObject*>; //we have to free this memory but it gives me an error
	}

	//now, check all our local objects against all other local objects in the node
	if (m_static_objects.size() > 1)
	{
		for (list<GameObject*>::iterator it = m_static_objects.begin();it != m_static_objects.end();it++)
		{
			one = *it;
			list<GameObject*>::iterator it2 = it;
			for (it2++;it2 != m_static_objects.end();it2++) //check ++it
			{
				other = *it2;
				if (one->_boundingBox->collidesWith(other->_boundingBox) == true)
				{
					TestManager::collisions++;
					intersections->push_back(new IntersectionRecord(one, other));
				}
			}
		}
	}

	if (m_isLeaf == false)
	{
		//parentObjs->insert(parentObjs->end(),m_objects.begin(),m_objects.end()); //por qué con merge se eliminan los objetos?

		//each child node will give us a list of intersection records, which we then merge with our own intersection records.
		for (int i = 0;i < 8;i++)
		{
			//Prueba
			list<GameObject*>* to_pass = new list<GameObject*>;
			to_pass->insert(to_pass->end(), parentObjs->begin(), parentObjs->end());
			to_pass->insert(to_pass->end(), m_static_objects.begin(), m_static_objects.end());

			m_childNode[i]->GetIntersections(to_pass, intersections);
			delete to_pass;
			to_pass = nullptr;
		}
	}
	static_intersections_done = true;
	return intersections;
}

int Octree::getObjectsCount()
{
	int result = m_objects.size();
	if (m_isLeaf == false)
	{
		for (int i = 0;i < 8;i++)
		{
			result += m_childNode[i]->getObjectsCount();
		}
	}

	return result;
}

list<GameObject*>* Octree::getGameObjects(list<GameObject*>* result)
{
	if (result == nullptr)
		result = new list<GameObject*>;

	if (m_isLeaf == false)
	{
		for (int i = 0;i < 8;i++)
		{
			m_childNode[i]->getGameObjects(result);
		}
	}

	list<GameObject*>::iterator it;
	for (it = m_objects.begin();it != m_objects.end();it++)
	{
		result->push_back(*it);
	}

	return result;
}

void Octree::Reset()
{
	m_objects.clear();
	to_insert.clear();
}


