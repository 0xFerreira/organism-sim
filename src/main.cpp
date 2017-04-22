#include "mlevosim/Logger.h"
#include "mlevosim/Organism.h"

int main(int argc, char** argv)
{
    Organism* org = new Organism(0);

    org->registerLogCallback([](const std::string& info) {
        Logger::write(info);
    });

    org->provideInput();

    return 1;
}