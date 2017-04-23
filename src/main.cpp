#include <vector>

#include "mlevosim/Logger.h"

#include "mlevosim/SpaceTime.h"
#include "mlevosim/World.h"
#include "mlevosim/Organism.h"

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 10
#define ORGANISM_START_COUNT 5

SpaceTime* buildSpaceTime()
{
    SpaceTime* spaceTime = new SpaceTime();

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

    spaceTime->registerWorld(world);
    spaceTime->registerOrganisms(organisms);

    return spaceTime;
}

int main(int argc, char** argv)
{

    SpaceTime* sT = buildSpaceTime();

    sT->nextTick();

    return 1;
}