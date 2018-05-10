#ifndef MGEDEMO_HPP
#define MGEDEMO_HPP

#include "mge/core/AbstractGame.hpp"
#include "glm.hpp"


class DebugHud;
class Mesh;
class AbstractMaterial;
class GameObject;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class MGEDemo: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MGEDemo();
		virtual ~MGEDemo();

        //override initialize so we can add a DebugHud
        virtual void initialize();

		//Testing
		virtual Octree* SetOctree(int levels, float initial_region_size);
		virtual void SetOctree(Octree* oc);
		virtual void PopulateGame(int numberObjects, float staticPercentage, float obbsPercentage,bool staticObjectsOptimitation = false);
		virtual void Reset();
		virtual void Loop();

	protected:
	    //override so we can construct the actual scene
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();



	private:
		DebugHud* _hud;                   //hud display
		Mesh* objectMeshS;
		AbstractMaterial* objectMaterial;

		std::vector<GameObject*> gos;
        void _updateHud();

        MGEDemo(const MGEDemo&);
        MGEDemo& operator=(const MGEDemo&);
};

#endif // MGEDEMO_HPP
