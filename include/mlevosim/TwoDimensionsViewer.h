#ifndef _TwoDimensionsViewerClass_
#define _TwoDimensionsViewerClass_

#include <SFML/Graphics.hpp>

#include "mlevosim/Viewer.h"

class TwoDimensionsViewer : public  Viewer
{
private:
protected:
    bool running = false;
    sf::RenderWindow* window = nullptr;

public:
    TwoDimensionsViewer()
    {
        this->running = true;
        this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "ML Evo Sim");
    }

    bool isRunning()
    {
        return this->running;
    }

    void draw(SpaceTime::State* state)
    {
        sf::RectangleShape tileShape({25.f, 25.f});
        sf::CircleShape organismShape(12.5f);


        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
                this->running = false;
            }
        }
        window->clear();

        auto tiles = state->world->getTiles();

        unsigned int x = 0;
        unsigned int y = 0;
        for(auto& row : tiles) {
            y = 0;
            for(auto& tile : row.second) {
                float energyCapacity = (float)tile.second->getEnergy()/(float)tile.second->getMaxEnergy();
                tileShape.setFillColor(sf::Color(255*(1-energyCapacity), 255*energyCapacity, 255*(1-energyCapacity*0.5)));
                tileShape.setPosition({14.0f + 26.f*x, 8.0f + 26.f*y});
                window->draw(tileShape);
                y++;
            }
            x++;
        }

        for(Organism* organism : state->organisms) {
            organismShape.setFillColor(sf::Color::Black);
            organismShape.setPosition({14.0f + 26.f*organism->x, 8.0f + 26.f*organism->y});
            window->draw(organismShape);
        }
        window->display();
    }
};

#endif //_TwoDimensionsViewerClass_