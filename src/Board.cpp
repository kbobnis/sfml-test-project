//
// Created by Krzysiek on 26/01/2022.
//

#include <SFML/Graphics.hpp>
#include "Board.h"

using namespace sf;
using namespace std;

Board::Board(const int x, const int y, const int cellWidth, int cellHeight, float moveTime) :
		moveTime(moveTime),
		cell(Vector2f(cellWidth, cellHeight))
{
	this->x = x;
	this->y = y;
	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;

	this->createNewPiece();

	cells.resize(x);
	for (int i = 0; i < x; ++i)
	{
		cells[i].resize(y);
	}

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			cells[i][j] = false;
		}
	}

	cell.setOutlineColor(Color::Green);
	cell.setOutlineThickness(cellWidth / 20);
}

void Board::createNewPiece()
{
	currentPiece = static_cast<PieceType>(rand() % PieceType::Z);
	currentPieceX = x / 2;
}

void Board::drawPiece(RenderTarget *window)
{
	cell.setFillColor(Color::Green);

	const std::vector<bool> shape = pieces[currentPiece];

	for (int i = 0; i < 4; i++)
	{ //first line
		if (shape[i])
		{
			cell.setPosition(i + currentPieceX, 0 + currentPieceY);
			window->draw(cell);
		}
	}
	for (int i = 4; i < 8; i++)
	{ //second line
		if (shape[i])
		{
			cell.setPosition(i + currentPieceX, 0 + currentPieceY);
			window->draw(cell);
		}
	}
}

void Board::draw(RenderTarget *window)
{
	for (int y = 0; y < this->y; y++)
	{
		for (int x = 0; x < this->x; x++)
		{
			switch (cells[x][y])
			{
				case false:
					cell.setFillColor(Color::Black);
					break;
				case true:
					cell.setFillColor(Color::Blue);
					break;
			}

			cell.setPosition(Vector2f(x * cellWidth, y * cellHeight));
			window->draw(cell);
		}
	}

	drawPiece(window);
}

void Board::tick(const sf::Time &delta)
{
	sinceLastPieceMove += delta.asSeconds();

	if (sinceLastPieceMove > moveTime)
	{
		currentPieceY++;
		sinceLastPieceMove -= moveTime;
	}
}

void Board::handleKeyPress(Keyboard::Key key)
{
	switch (key)
	{
		case Keyboard::Left:
			currentPieceX--;
			break;
		case Keyboard::Right:
			currentPieceX++;
			break;
	}
}


std::map<PieceType, std::vector<bool>> pieces = {
		{
				PieceType::I, {1, 1, 1, 1}
		},
		{
				PieceType::J, {
				               1, 0, 0, 0,
						              1, 1, 1, 0
				              }
		},
		{
				PieceType::L, {0, 0, 0, 1,
						              0, 1, 1, 1}
		},
		{
				PieceType::O, {
				               0, 1, 1, 0,
						              0, 1, 1, 0}
		},
		{
				PieceType::S, {
				               0, 1, 1, 0,
						              1, 1, 0, 0}
		},
		{
				PieceType::T, {
				               0, 1, 0, 0,
						              1, 1, 1, 0}
		},
		{
				PieceType::Z, {
				               1, 1, 0, 0,
						              0, 1, 1, 0}
		},
};