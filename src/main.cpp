#include "mlevosim/Logger.h"

#include "mlevosim/World.h"
#include "mlevosim/Organism.h"

int main(int argc, char** argv)
{
    World* world = new World(10, 10);
    world->registerLogCallback([](const std::string& info) {
        Logger::write("[World] " + info);
    });

    Organism* org = new Organism();
    org->registerLogCallback([](const std::string& info) {
        Logger::write("[Organism] " + info);
    });

    world->populate();
    org->provideInput();

    return 1;
}