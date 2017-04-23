#include <vector>
#include <chrono>

#include "mlevosim/Logger.h"

#include "mlevosim/TwoDimensionsViewer.h"

#include "mlevosim/SpaceTime.h"
#include "mlevosim/World.h"
#include "mlevosim/Organism.h"

#define WORLD_WIDTH 40
#define WORLD_HEIGHT 25
#define ORGANISM_START_COUNT 5
#define MS_PER_UPDATE 25

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

unsigned long long getCurrentTime()
{
    return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
}


int main(int argc, char** argv)
{

    SpaceTime* sT = buildSpaceTime();
    Viewer* renderer = new TwoDimensionsViewer();

    unsigned long long previous = getCurrentTime();
    unsigned long long lag = 0;

    while (renderer->isRunning())
    {
        unsigned long long current = getCurrentTime();
        unsigned long long elapsed = current - previous;
        previous = current;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE)
        {
            sT->nextTick();
            lag -= MS_PER_UPDATE;
        }

        renderer->draw(sT->now());
    }

    return 1;
}