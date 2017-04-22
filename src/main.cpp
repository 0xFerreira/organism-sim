#include <vector>

#include "mlevosim/Logger.h"

#include "mlevosim/SpaceTime.h"
#include "mlevosim/World.h"
#include "mlevosim/Organism.h"

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 10
#define ORGANISM_START_COUNT 5

int main(int argc, char** argv)
{
    SpaceTime* spaceTime = new SpaceTime();

    World* world = new World(WORLD_WIDTH, WORLD_HEIGHT);
    world->registerLogCallback([](const std::string& info) {
        Logger::write("[World] " + info);
    });

    world->terraform();

    std::vector<Organism*> organisms;


    Organism* org = new Organism();
    org->registerLogCallback([](const std::string& info) {
        Logger::write("[Organism] " + info);
    });

    organisms.push_back(org);
    for(unsigned int i=0;i<ORGANISM_START_COUNT-1;i++) {
        organisms.push_back(org->clone());
    }

    //spaceTime->registerWorld(world);
    //spaceTime->registerOrganisms();

    return 1;
}