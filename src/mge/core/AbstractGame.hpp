#ifndef ABSTRACTGAME_HPP
#define ABSTRACTGAME_HPP

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <string>
#include "glm.hpp"


class World;
class Renderer;
class Octree;

/**
 * Defines the basic structure for a game, with defaults already filled in.
 * The only item that MUST be overridden/implemented is _initializeScene()
 * where you build up your world, the rest is optional to override (with care/caution).
 */
class AbstractGame
{
    public:

        AbstractGame();
        virtual ~AbstractGame();

        //creates a window, initializes glew, a renderer and a world instance
        virtual void initialize();
        //run the actual process of updating all objects, rendering them and processing events
        virtual void run();

		//Testing 
		virtual Octree* SetOctree(int levels, float initial_region_size) = 0;
		virtual void SetOctree(Octree* oc) = 0;
		virtual void PopulateGame(int numberObjects, float percentage, float obbsPercentage, bool staticObjectsOptimitation = false) = 0;
		virtual void Reset() = 0;
		virtual void Loop() = 0;

    protected:

        //methods above delegate behaviour to the methods below so that you can override it in a subclass

        //initialize sfml rendering context
        virtual void _initializeWindow();
        //print info about the current driver version etc
        virtual void _printVersionInfo();
        //initialize the extension wrangler
        virtual void _initializeGlew();
        //create our own custom renderer instance
        virtual void _initializeRenderer();
        //initialize a scene root to which we can attach/add objects
        virtual void _initializeWorld();

        //initialize the actual scene, HAS to be done by a subclass
        virtual void _initializeScene() = 0;

        //call update on all game objects in the display root
        virtual void _update(float pStep);
        //render all game objects in the display root
        virtual void _render();
        //process any sfml window events (see SystemEventDispatcher/Listener)
        virtual void _processEvents();

		sf::RenderWindow* _window;  //sfml window to render into
		Renderer* _renderer;        //the renderer class to render the world
		World* _world;              //the root game object that represents our scene
		float _fps;                 //stores the real fps
		Octree* _octree;
		int loop_collisions = 0;
		float _timeInGame = 0.0f;

		//Testing 
		sf::Clock renderClock;
		int frameCount = 0;
		float timeSinceLastFPSCalculation = 0;

		//settings to make sure the update loop runs at 60 fps
		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
		sf::Clock updateClock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;



    private:
        AbstractGame(const AbstractGame&);
        AbstractGame& operator=(const AbstractGame&);


};

#endif // ABSTRACTGAME_HPP
