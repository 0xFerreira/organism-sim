#include <vector>
#include <chrono>

#include "mlevosim/Logger.h"

#include "mlevosim/Viewer/TwoDimensionsViewer.h"
#include "mlevosim/Viewer/NoViewer.h"

#include "mlevosim/Core/SpaceTime.h"
#include "mlevosim/Core/World.h"
#include "mlevosim/Core/Organism.h"

#define WORLD_WIDTH 48
#define WORLD_HEIGHT 27
#define ORGANISM_START_COUNT 5
#define MS_PER_UPDATE 50

SpaceTime* buildSpaceTime()
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
    Viewer* viewer = new TwoDimensionsViewer();
    //Viewer* viewer = new NoViewer();

    unsigned long long previous = getCurrentTime();
    unsigned long long lag = 0;

    while (viewer->isRunning())
    {
        unsigned long long current = getCurrentTime();
        unsigned long long elapsed = current - previous;
        previous = current;
        lag += elapsed;

        viewer->processInput();

        while (lag >= MS_PER_UPDATE)
        {
            if(viewer->shouldTick()) {
                if(viewer->fowardInTime()) {
                    sT->foward();
                } else {
                    sT->backward();
                }

                viewer->ticked();
            }

            lag -= MS_PER_UPDATE;
        }

        viewer->draw(sT->now());
    }

    return 1;
}