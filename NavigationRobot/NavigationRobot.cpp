#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Robot.h"
#include "Obstacle.h"
#include "Chemin.h"
#include "Orientation.h"
#include "Deplacement.h"

Robot robotD;
Robot robotA;
Obstacle obstacle;
sf::RenderWindow window(sf::VideoMode(420, 420), "Casse-Briques");


void navigationRobot()
{
	Point* chemins;

	chemins = calculCheminOptimal(robotA.getPos(), robotD.getPos(), obstacle);

	for (int i = 0; i > sizeof(chemins) / sizeof(sf::Vector2f); i++)
	{
		Point chemin = chemins[i];

		orientationRobot(robotA, chemin);
		deplacerRobot(robotA, chemin);
	}

	robotA.setAngle(robotD.getAngle());
}

void update()
{
	window.draw(robotD.getShape());
	window.draw(robotA.getShape());
	window.draw(obstacle.getShape(), 2, sf::Lines);
}

int main()
{
	sf::Vector2f obstPoint1;
	sf::Vector2f obstPoint2;
	sf::Clock clock;
	int x , y;

	window.setVisible(false);

	std::cout << "Entrer la position de depart du robot" << std::endl;
	std::cout << "X: "; std::cin >> x;
	std::cout << "Y: "; std::cin >> y;
	robotD.setPosition(x, y);

	std::cout << "Entrer la position d'arrivee du robot" << std::endl;
	std::cout << "X: "; std::cin >> x;
	std::cout << "Y: "; std::cin >> y;
	robotA.setPosition(x, y);

	std::cout << "Entrer la position de l'obstacle du robot" << std::endl;
	std::cout << "X1: "; std::cin >> x;
	std::cout << "Y1: "; std::cin >> y;
	obstPoint1 = sf::Vector2f(x, y);
	std::cout << "X2: "; std::cin >> x;
	std::cout << "Y2: "; std::cin >> y;
	obstPoint2 = sf::Vector2f(x, y);

	std::cout << "Demarage de la visualisation..." << std::endl;

	navigationRobot();
	window.setVisible(true);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					return 0;
			}
		}

		if (clock.getElapsedTime().asMilliseconds() > 10)
		{
			update();
			clock.restart();
		}
	}
	window.close();
}