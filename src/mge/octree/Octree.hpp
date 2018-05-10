#pragma once
#include "mge/core/GameObject.hpp"

#include <list>
#include <vector>
#include <queue>
#include <array>

class AABB;
class IntersectionRecord;
using namespace std; 


/*
1.- Creamos el arbol con el nivel de detalle especificado. Simplemente vamos dividiendo regiones hasta llegar al nivel pedido
2.- Poblamos el arbol con una lista de objetos que entra en la raiz y va bajando de nivel hasta que no puede más
		-Quepo en algún hijo? (si tiene) --> Sí. --> Me paso al hijo.
							             --> NO --> Me quedo aquí.
								-->Si no tiene hijos me quedo aqui
*/

/*
1- Create the tree with the level required. Just divide the regions until we get the maximum level
2.- We fill the tree with a list of objects that enter from the root and go deeper until reach the correct level.
		-Can I go in some child?(if any) --> Yes --> Insert in child
										 --> No  --> I stay here
								--> If no childs --> I stay here
*/


class Octree
{
public:
	Octree(AABB * region);
	Octree(AABB * region, int levelsLefts);
	~Octree();
	AABB* m_region;
	void Insert(GameObject* to_insert);

	std::string getInfo();
	void Octree::UpdateOctree();
	list<IntersectionRecord*>* GetIntersections(list<GameObject*>* parentObjs = nullptr, list<IntersectionRecord*>* intersections = nullptr);
	list<IntersectionRecord*>* GetStaticIntersections(list<GameObject*>* parentObjs = nullptr, list<IntersectionRecord*>* intersections = nullptr);
	list<GameObject*> m_objects;
	list<GameObject*> m_static_objects;
	Octree* m_childNode[8];
	list<GameObject*> to_insert;
	Octree* _parent;
	int getObjectsCount();
	int levels;
	list<GameObject*>* getGameObjects(list<GameObject*>* result = nullptr);
	void Reset();
	bool static_intersections_done = false;

private:

	void BuildTree();

	AABB* m_octant[8];
	const int MIN_SIZE = 1;
	
	//This is a bitmask indicating which child nodes are actively being used.
	//It adds slightly more complexity, but is faster for performance since there is only one comparison instead of 8.
	///unsigned char m_activeNodes; //dynamic octree variable
	bool m_isLeaf;
	

	//this is how many frames we'll wait before deleting an empty tree branch. Note that this is not a constant. The maximum lifespan doubles 
	//--> Not in use in the static octree implementation --> I'm going to keep it for the future In case I have time
	//int m_maxLifespan = 8;
	//int m_curLife = -1;             //this is a countdown time showing how much time we have left to live
};

