//
// Created by Krzysiek on 30/01/2022.
//

#include "NextPieceBoard.hpp"
#include "Board.hpp"

void NextPieceBoard::reactToEvent(EventType type, int data)
{
	switch (type)
	{
		case NextPieceFiguredOut:
			this->nextPiece = pieces[data];
			break;
	}
}

void NextPieceBoard::draw(sf::RenderTarget *window, int cellWidth, int cellHeight)
{
	sf::Text text;
	text.setFillColor(sf::Color::White);
	text.setFont(this->font);
	text.setPosition(xPos, yPos);
	text.setString("Next piece:");
	window->draw(text);

	sf::RectangleShape cell;
	cell.setSize(sf::Vector2f(cellWidth, cellHeight));
	cell.setOutlineThickness(1);
	cell.setOutlineColor(sf::Color::White);

	std::vector<Pair> positions = this->nextPiece.cellPositions;
	for (Pair position: positions)
	{
		cell.setFillColor(nextPiece.color);
		cell.setPosition(xPos + position.x * cellWidth, yPos + 50 + position.y * cellHeight);
		window->draw(cell);
	}


}

NextPieceBoard::NextPieceBoard(Piece& nextPiece, sf::Font font, int xPos, int width, int yPos) :
		nextPiece(nextPiece),
		font(font)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->width = width;
}

