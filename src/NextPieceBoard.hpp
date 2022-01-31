//
// Created by Krzysiek on 30/01/2022.
//

#ifndef HELLOSFML_NEXTPIECEBOARD_HPP
#define HELLOSFML_NEXTPIECEBOARD_HPP


#include <SFML/Graphics/RenderWindow.hpp>
#include "observer/Observer.hpp"
#include "Piece.hpp"

class NextPieceBoard : public Observer
{
	int xPos, yPos, width;
	Piece& nextPiece;
	sf::Font font;

public:
	NextPieceBoard(Piece& nextPiece, sf::Font font, int xPos, int width, int yPos);
	void draw(sf::RenderTarget *window, int cellWidth, int cellHeight);
	void reactToEvent(EventType type, int data) override;
};


#endif //HELLOSFML_NEXTPIECEBOARD_HPP
