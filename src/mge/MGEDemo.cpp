#include <iostream>
#include <string>


#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/MovementBehaviour.hpp"

#include "octree\Octree.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"

#include "mge\octree\TestManager.hpp"

//Octree

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame(), _hud(0)
{
}

void MGEDemo::initialize() {
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;

	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	objectMeshS = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");

	//MATERIALS

	//create some materials to display the cube, the plane and the light
	objectMaterial = new ColorMaterial(glm::vec3(0, 0, 1));
}

//build the game _world
void MGEDemo::_initializeScene()
{
	//SCENE SETUP
   //add camera first (it will be updated last)
	Camera* camera = new Camera("camera", glm::vec3(375, 250, 350));
	camera->rotate(glm::radians(55.0f), glm::vec3(0, 1, 0));
	camera->rotate(glm::radians(-25.0f), glm::vec3(1, 0, 0));

	_world->add(camera);
	_world->setMainCamera(camera);
}

void MGEDemo::_render() {
	AbstractGame::_render();
	_updateHud();
}
void MGEDemo::_updateHud() {
	std::string debugInfo = "";
	debugInfo += std::string("Current test:") + TestManager::currentTest + "\n" +
		std::string("FPS:") + std::to_string(TestManager::fps) + "\n" +
		std::string("Run:") + std::to_string(TestManager::run_i) + "\n" +
		std::string("Objects:") + std::to_string(TestManager::objects) + "\n" +
		std::string("Percentage of static:") + std::to_string(TestManager::statics) + "%\n" +
		std::string("Percentage of OBBs:") + std::to_string(TestManager::obbs_percentage) + "%\n" +
		std::string("Levels:") + std::to_string(TestManager::levels) + "\n" +
		std::string("Updates:") + std::to_string(TestManager::updates) + "\n" +
		std::string("Fit tests:") + std::to_string(TestManager::fitTests) + "\n" +
		std::string("Collision tests:") + std::to_string(TestManager::collisionTests) + "\n" +
		/*std::string("Padre ") + std::to_string((int)_octree->m_objects.size()) + "\n" +
		std::string("Hijo 0 ") + std::to_string((int)_octree->m_childNode[0]->m_objects.size()) + "\n" +
		std::string("Hijo 1 ") + std::to_string((int)_octree->m_childNode[1]->m_objects.size()) + "\n" +
		std::string("Hijo 2 ") + std::to_string((int)_octree->m_childNode[2]->m_objects.size()) + "\n" +
		std::string("Hijo 3 ") + std::to_string((int)_octree->m_childNode[3]->m_objects.size()) + "\n" +
		std::string("Hijo 4 ") + std::to_string((int)_octree->m_childNode[4]->m_objects.size()) + "\n" +
		std::string("Hijo 5 ") + std::to_string((int)_octree->m_childNode[5]->m_objects.size()) + "\n" +
		std::string("Hijo 6 ") + std::to_string((int)_octree->m_childNode[6]->m_objects.size()) + "\n" +
		std::string("Hijo 7 ") + std::to_string((int)_octree->m_childNode[7]->m_objects.size()) + "\n" +*/
		std::string("Collisions ") + std::to_string(TestManager::collisions);


	/*std::string("Padre ") + std::to_string((int)_octree->m_objects.size()) + "\n" +
	std::string("Hijo 0 ") + std::to_string((int)_octree->m_childNode[0]->m_objects.size()) + "\n" +
	std::string("Hijo 1 ") + std::to_string((int)_octree->m_childNode[1]->m_objects.size()) + "\n" +
	std::string("Hijo 2 ") + std::to_string((int)_octree->m_childNode[2]->m_objects.size()) + "\n" +
	std::string("Hijo 3 ") + std::to_string((int)_octree->m_childNode[3]->m_objects.size()) + "\n" +
	std::string("Hijo 4 ") + std::to_string((int)_octree->m_childNode[4]->m_objects.size()) + "\n" +
	std::string("Hijo 5 ") + std::to_string((int)_octree->m_childNode[5]->m_objects.size()) + "\n" +
	std::string("Hijo 6 ") + std::to_string((int)_octree->m_childNode[6]->m_objects.size()) + "\n" +
	std::string("Hijo 7 ") + std::to_string((int)_octree->m_childNode[7]->m_objects.size()) + "\n" +*/

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}
MGEDemo::~MGEDemo()
{
	//dtor
}


//For testing
Octree* MGEDemo::SetOctree(int levels, float initial_region_size)
{
	float half_region = initial_region_size / 2.0f;
	glm::vec3 min = { -half_region, -half_region, -half_region };
	glm::vec3 max = { half_region, half_region, half_region };
	AABB * initialRegion = new AABB(min, max);

	Octree * test = new Octree(initialRegion, levels);
	_octree = test;
	_octree->_parent = nullptr;

	return test;
}
void MGEDemo::SetOctree(Octree * oc)
{
	_octree = oc;
}
void MGEDemo::PopulateGame(int numberObjects, float staticPercentage, float obbsPercetage, bool staticObjectsOptimitation)
{
	if (staticObjectsOptimitation == false)
	{
		/*srand(time(NULL));

		AABB * initialRegion = _octree->m_region;
		GameObject* go;

		int n_no_static = numberObjects*staticPercentage;
		int n_static = numberObjects*(1.0f - staticPercentage);

		for (int i = 0;i < n_no_static; i++)
		{
			for (int j = 0;j < n_no_static *obbsPercetage; j++)
			{
				go = new GameObject("gameObject" + i);
				go->setMesh(objectMeshS);
				go->_isStatic = false;
				go->setMaterial(objectMaterial);
				go->translate(glm::vec3
				{
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.x * 2.0f * 0.9f - _octree->m_region->m_halfSize.x * 0.9f,
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.y * 2.0f * 0.9f - _octree->m_region->m_halfSize.y * 0.9f,
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.z * 2.0f * 0.9f - _octree->m_region->m_halfSize.z * 0.9f,
				});
				go->createCollider(true);
				_octree->Insert(go);
				_world->add(go);
			}
			for (int j = 0;j < n_no_static * (1.0f-obbsPercetage); j++)
			{
				go = new GameObject("gameObject" + i);
				go->setMesh(objectMeshS);
				go->_isStatic = false;
				go->setMaterial(objectMaterial);
				go->translate(glm::vec3
				{
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.x * 2.0f * 0.9f - _octree->m_region->m_halfSize.x * 0.9f,
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.y * 2.0f * 0.9f - _octree->m_region->m_halfSize.y * 0.9f,
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.z * 2.0f * 0.9f - _octree->m_region->m_halfSize.z * 0.9f,
				});
				go->createCollider();
				_octree->Insert(go);
				_world->add(go);
			}
		}
		for (int i = 0;i < n_static;i++)
		{
			for (int j = 0;j < n_static * obbsPercetage; j++)
			{
				go = new GameObject("gameObject" + i);
				go->_isStatic = false;
				go->setMesh(objectMeshS);
				go->setMaterial(objectMaterial);
				go->translate(glm::vec3
				{
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.x * 2.0f * 0.9f - _octree->m_region->m_halfSize.x * 0.9f,
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.y * 2.0f * 0.9f - _octree->m_region->m_halfSize.y * 0.9f,
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.z * 2.0f * 0.9f - _octree->m_region->m_halfSize.z * 0.9f,
				});
				float velX = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
				float velY = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
				float velZ = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
				go->setBehaviour(new MovementBehaviour(glm::vec3{ velX,velY,velZ }, initialRegion));
				go->createCollider(true);
				_octree->Insert(go);
				_world->add(go);
			}
			for (int j = 0;j < n_static * (1.0f - obbsPercetage); j++)
			{
				go = new GameObject("gameObject" + i);
				go->_isStatic = false;
				go->setMesh(objectMeshS);
				go->setMaterial(objectMaterial);
				go->translate(glm::vec3
				{
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.x * 2.0f * 0.9f - _octree->m_region->m_halfSize.x * 0.9f,
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.y * 2.0f * 0.9f - _octree->m_region->m_halfSize.y * 0.9f,
					((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.z * 2.0f * 0.9f - _octree->m_region->m_halfSize.z * 0.9f,
				});
				float velX = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
				float velY = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
				float velZ = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
				go->setBehaviour(new MovementBehaviour(glm::vec3{ velX,velY,velZ }, initialRegion));
				go->createCollider();
				_octree->Insert(go);
				_world->add(go);
			}
		}*/
	}
	else
	{
		srand(time(NULL));

		AABB * initialRegion = _octree->m_region;
		GameObject* go;

		int static_objects = numberObjects*staticPercentage;
		int non_stc_objects = numberObjects*(1.0f - staticPercentage);

		for (int i = 0;i < static_objects; i++)
		{
			go = new GameObject("gameObject" + i);
			go->_isStatic = true;
			go->setMesh(objectMeshS);
			go->setMaterial(objectMaterial);
			go->translate(glm::vec3
			{
				((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.x * 2.0f * 0.9f - _octree->m_region->m_halfSize.x * 0.9f,
				((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.y * 2.0f * 0.9f - _octree->m_region->m_halfSize.y * 0.9f,
				((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.z * 2.0f * 0.9f - _octree->m_region->m_halfSize.z * 0.9f,
			});

			if (i < static_objects*obbsPercetage)
				go->createCollider(true); //true = obb collider
			else
				go->createCollider(); //true = AABB collider

			_octree->Insert(go);
			_world->add(go);
		}

		for (int i = 0;i < non_stc_objects;i++)
		{
			go = new GameObject("gameObject" + i);
			go->_isStatic = false;
			go->setMesh(objectMeshS);
			go->setMaterial(objectMaterial);
			go->translate(glm::vec3
			{
				((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.x * 2.0f * 0.9f - _octree->m_region->m_halfSize.x * 0.9f,
				((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.y * 2.0f * 0.9f - _octree->m_region->m_halfSize.y * 0.9f,
				((float)rand() / (float)RAND_MAX) * _octree->m_region->m_halfSize.z * 2.0f * 0.9f - _octree->m_region->m_halfSize.z * 0.9f,
			});
			float velX = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
			float velY = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
			float velZ = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
			go->setBehaviour(new MovementBehaviour(glm::vec3{ velX,velY,velZ }, initialRegion));

			if (i < non_stc_objects*obbsPercetage)
				go->createCollider(true);
			else
				go->createCollider();
			_octree->Insert(go);
			_world->add(go);
		}
	}
}
void MGEDemo::Reset()
{
	delete _world;
	delete _octree;
	_initializeWorld();
	_initializeScene();
}
void MGEDemo::Loop()
{
	if (_window->isOpen()) {
		timeSinceLastUpdate += updateClock.restart();

		//if (timeSinceLastUpdate > timePerFrame)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//while (timeSinceLastUpdate > timePerFrame) {
			//	timeSinceLastUpdate -= timePerFrame;
			_update(timePerFrame.asSeconds());
			//}

			_render();
			_window->display();

			//fps count is updated once every 1 second
			frameCount++;
			timeSinceLastFPSCalculation += renderClock.restart().asSeconds();
			if (timeSinceLastFPSCalculation > 1) {
				TestManager::fps = frameCount / timeSinceLastFPSCalculation;
				timeSinceLastFPSCalculation -= 1;
				frameCount = 0;
			}
		}

		//empty the event queue
		_processEvents();
	}
}
