#include <vector>

//#define WORLD_WIDTH 48
//#define WORLD_HEIGHT 27
#define WORLD_WIDTH 73
#define WORLD_HEIGHT 41
#define ORGANISM_START_COUNT 5

#include "mlevosim/Logger.h"

#include "mlevosim/Viewer/TwoDimensionsViewer.h"
#include "mlevosim/Viewer/NoViewer.h"

#include "mlevosim/Core/SpaceTime.h"
#include "mlevosim/Core/World.h"
#include "mlevosim/Core/Organism.h"

/* Code Quality & Refactoring */
//Move time control from main to twoDimensionsViewer
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


int main(int argc, char** argv)
{

    SpaceTime* spaceTime = new SpaceTime();
    spaceTime->registerLogCallback([](const std::string& info) {
        Logger::write("[SpaceTime] " + info);
    });

    World* world = new World(WORLD_WIDTH, WORLD_HEIGHT);
    world->registerLogCallback([](const std::string& info) {
        Logger::write("[World] " + info);
    });

    world->terraform();

    std::vector<Organism*> organisms;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0, WORLD_WIDTH-1);
	std::uniform_real_distribution<float> dist2(0, WORLD_HEIGHT-1);
    for(unsigned int i=0;i<ORGANISM_START_COUNT;i++) {
        Organism* org = new Organism();
        org->registerLogCallback([](const std::string& info) {
            Logger::write("[Organism] " + info);
        });

        organisms.push_back(org);
		org->setPosition({static_cast<int>(dist(mt)), static_cast<int>(dist2(mt))});
    }

    spaceTime->registerWorld(world);
    spaceTime->registerOrganisms(organisms);

    Viewer* viewer = new TwoDimensionsViewer();
    viewer->registerSpaceTime(spaceTime);

    viewer->run();

    return 1;
}
