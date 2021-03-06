#pragma once

#include <SFML/Graphics.hpp>
//#include "Scene.h"

class Obstacle
{
public:
	Obstacle();
	Obstacle(sf::Vector2f, sf::Vector2f);

	void setPosition(sf::Vector2f, sf::Vector2f);
	sf::Vector2f getPointOne();
	sf::Vector2f getPointTwo();
	sf::Vertex* getShape();
private:
	sf::Vertex lines[2];
};