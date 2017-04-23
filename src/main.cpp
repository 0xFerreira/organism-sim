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

/* Code Quality & Refactoring */
//Add and work with namespaces
//Move time control from main to twoDimensionsViewer
//Move organism logic to brain class and polymorphics

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

        float deltaTime = (float)lag/(float)MS_PER_UPDATE;
        viewer->draw(sT->now(), deltaTime);
    }

    return 1;
}