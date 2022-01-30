//
// Created by Krzysiek on 30/01/2022.
//

#include "Scoreboard.h"
#include <string>
#include <SFML/Graphics.hpp>

Scoreboard::Scoreboard(sf::Font& font)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(10, 25);
	sf::Vector2<float> score_scale(1.5f, 1.5f);
	text.setScale(score_scale);
	text.setString("Lines: 0");
	this->text = text;
}

void Scoreboard::reactToEvent(EventType type, int data)
{
	switch (type)
	{
		case RowsCleared:
			this->lines += data;
			std::string text = "Lines: " + std::to_string(lines);
			this->text.setString(text);
			break;
	}
}

sf::Text Scoreboard::getScore()
{
	return this->text;
}
