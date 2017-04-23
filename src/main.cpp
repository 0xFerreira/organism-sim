#include <vector>

#include "mlevosim/Logger.h"

#include "mlevosim/Viewer/TwoDimensionsViewer.h"
#include "mlevosim/Viewer/NoViewer.h"

#include "mlevosim/Core/TimeTravel.h"
#include "mlevosim/Core/World.h"
#include "mlevosim/Core/Organism.h"

#define WORLD_WIDTH 48
#define WORLD_HEIGHT 27
#define ORGANISM_START_COUNT 10

/* Code Quality & Refactoring */
//Move time control from main
//Add and work with namespaces
//Move organism logic to brain class and polymorphics
//Check warnings and static analysis
//Compiler flags


/* Core Features */
//Give surrounding blocks and input info for organisms
//Create an organism brain that tries to stay alive
//Organism internal world map
//Organism communication when on close tiles

/* TwoDimensionsViewer Features */
//Isometric artistic tiles
//Much Better juicing/User Feedback
//option to select organism and show info
//option to select tile and show info

/* Performance */
//Make structs/classes pure when possible
//Try to align memory for performance
//Check loops for stupid memory reading

/* Performance: Big as fuck work */
//Check simd operations, only using 1 of 4 cores right now
//Check openCL or nvidia alternative

// int main(int argc, char** argv)
// {
//     Universe* universe = new Universe();
//     Pyshics*  physics  = new AsapPhysics();
//     Entities* entities = new Entities();
//     Creator*  creator  = new SimpleCreator();
//     Viewer*   viewer   = new TwoDimensionsViewer();

//     creator->registerEntityRegister([](Entity* entity){
//         entities->registerEntity(entity);
//     });

//     physics->registerEntities(entities);

//     universe->registerPhysics(physics);

//     universe->simulate();

//     return 0;
// }

/*
    const double alpha = accumulator / dt;

    State state = currentState * alpha +
        previousState * ( 1.0 - alpha );
*/

int main(int argc, char** argv)
{

    TimeTravel* timeTravel = new TimeTravel();

    timeTravel->registerLogCallback([](const std::string& info) {
        Logger::write("[TimeTravel] " + info);
    });

    World* world = new World(WORLD_WIDTH, WORLD_HEIGHT);
    world->registerLogCallback([](const std::string& info) {
        Logger::write("[World] " + info);
    });

    world->terraform();

    std::vector<Organism*> organisms;

    for(unsigned int i=0;i<ORGANISM_START_COUNT;i++) {
        Organism* org = new Organism();
        org->registerLogCallback([](const std::string& info) {
            Logger::write("[Organism] " + info);
        });

        organisms.push_back(org);
    }

    timeTravel->registerWorld(world);
    timeTravel->registerOrganisms(organisms);

    Viewer* viewer = new TwoDimensionsViewer();

    viewer->draw(timeTravel->now());

    return 1;
}