#ifndef _TwoDimensionsViewerClass_
#define _TwoDimensionsViewerClass_

#define MS_PER_UPDATE 50

#include <algorithm>

#include <SFML/Graphics.hpp>

#include "mlevosim/Time.h"

#include "mlevosim/Viewer/Viewer.h"

class TwoDimensionsViewer : public  Viewer
{
private:
protected:
    bool running = false;
    sf::RenderWindow* window = nullptr;
    bool shouldTick   = false;
    bool fowardInTime = true;

    unsigned long long animationCounter = 0;

    sf::RectangleShape tileShape;
    sf::CircleShape organismShape;
public:
    TwoDimensionsViewer()
    {
        this->running = true;
        //this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "ML Evo Sim", sf::Style::Default, sf::ContextSettings(24,8,16));
		this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "ML Evo Sim", sf::Style::Fullscreen, sf::ContextSettings(24,8,16));
        this->window->setFramerateLimit(60);

        this->tileShape = sf::RectangleShape({25.f, 25.f});
        this->organismShape = sf::CircleShape(12.5f);
    }

    void run()
    {
        unsigned long long previous = Time::getCurrentTime();
        unsigned long long lag = 0;

		unsigned long long autoFoward = 0;
        while (this->running)
        {
            unsigned long long current = Time::getCurrentTime();
            unsigned long long elapsed = current - previous;
            previous = current;
            lag += elapsed;

            this->processInput();

            while (lag >= MS_PER_UPDATE)
            {
                if(this->shouldTick || autoFoward > 500) {
                    this->animationCounter = 0;
                    if(this->fowardInTime || autoFoward > 500) {
                        this->spaceTime->foward();
                    } else {
                        this->spaceTime->backward();
                    }

                    this->shouldTick = false;
					autoFoward = 0;
                }

                lag -= MS_PER_UPDATE;
            }
            this->animationCounter += elapsed;
			autoFoward  += elapsed;
            this->draw((float)lag/(float)MS_PER_UPDATE);
        }
    }

    void processInput()
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
                this->running = false;
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                   this->shouldTick = true;
                   this->fowardInTime = true;
                } else if (event.key.code == sf::Keyboard::Left) {
                    this->shouldTick = true;
                    this->fowardInTime = false;
                } else if (event.key.code == sf::Keyboard::K) {
					std::vector<int> toDelete;
					int index = 0;
					for(Organism* organism : this->spaceTime->now()->organisms) {
						if(!organism->isAlive()) {
							toDelete.emplace_back(index);
						}
						index++;
					}
					std::reverse(toDelete.begin(),toDelete.end());

					for(int deleteIndex : toDelete) {
						this->spaceTime->now()->organisms.erase(this->spaceTime->now()->organisms.begin() + deleteIndex);
					}
                }
            }
        }
    }

    void draw(float deltaTime)
    {
        window->clear();

        auto tiles = this->spaceTime->now()->world->getTiles();

        unsigned int x = 0;
        unsigned int y = 0;
        for(auto& row : tiles) {
            y = 0;
            for(auto& tile : row.second) {
                float energyCapacity = (float)tile.second->getEnergy()/(float)tile.second->getMaxEnergy();
                this->tileShape.setFillColor(sf::Color(255*energyCapacity, 255*energyCapacity, 255*energyCapacity));
                this->tileShape.setPosition({14.0f + 26.f*x, 8.0f + 26.f*y});
                window->draw(this->tileShape);
                y++;
            }
            x++;
        }

        for(Organism* organism : this->spaceTime->now()->organisms) {

            this->organismShape.setOutlineThickness(2.0f);
            this->organismShape.setOutlineColor(sf::Color::Black);

            this->organismShape.setFillColor(organism->getColor());
            this->organismShape.setScale({1.0f, 1.0f});

            Vector2i lastPosition = organism->getLastPosition();
            Vector2i position = organism->getPosition();

            float x = 0.0f;
            float y = 0.0f;

            if(this->animationCounter < 500) {
                x = lastPosition.x + (position.x - lastPosition.x)*(this->animationCounter/500.f);
                y = lastPosition.y + (position.y - lastPosition.y)*(this->animationCounter/500.f);
            } else {
                x =  position.x;
                y =  position.y;
            }

            this->organismShape.setPosition({14.0f + 26.f*x, 8.0f + 26.f*y});

            if(!organism->isAlive()) {
                this->organismShape.setFillColor(sf::Color(255, 0, 0, 80));
                this->organismShape.setScale({0.5f, 0.5f});
                this->organismShape.setPosition({21.0f + 26.f*x, 14.0f + 26.f*y});
            }

            window->draw(this->organismShape);
        }
        window->display();
    }
};

#endif //_TwoDimensionsViewerClass_
