//
// Created by Krzysiek on 30/01/2022.
//

#ifndef HELLOSFML_SCOREBOARD_HPP
#define HELLOSFML_SCOREBOARD_HPP

#include <SFML/Graphics.hpp>
#include "observer/Observer.hpp"

class Scoreboard : public Observer
{
private:
	int lines = 0;

public:
	Scoreboard(sf::Font& font, int xPos, int boardWidth);
	sf::Text text;

	void reactToEvent(EventType type, int data) override;

	sf::Text getScore();
};


#endif //HELLOSFML_SCOREBOARD_HPP
