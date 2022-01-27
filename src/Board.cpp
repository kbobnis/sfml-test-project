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
			cells[i][j] = Empty;
		}
	}

	cell.setOutlineColor(Color::Green);
	cell.setOutlineThickness(cellWidth / 20);
}

void Board::createNewPiece()
{
	currentPiece = static_cast<PieceType>(rand() % PieceType::Z);
	currentPieceX = x / 2;
	currentPieceY = 0;
}

void Board::draw(RenderTarget *window)
{
	for (int y = 0; y < this->y; y++)
	{
		for (int x = 0; x < this->x; x++)
		{
			switch (cells[x][y])
			{
				case Empty:
					cell.setFillColor(Color::Black);
					break;
				case Filled:
					cell.setFillColor(Color::Blue);
					break;
				case PiecePart:
					cell.setFillColor(Color::Green);
					break;
			}

			cell.setPosition(Vector2f(x * cellWidth, y * cellHeight));
			window->draw(cell);
		}
	}

}

void Board::tick(const sf::Time &delta)
{
	sinceLastPieceMove += delta.asSeconds();

	if (sinceLastPieceMove > moveTime)
	{
		if (this->canMove(0, 1) == false)
		{
			vector<Pair> pieceParts = getPieceParts();
			for (int i = 0; i < pieceParts.size(); ++i)
			{
				cells[pieceParts[i].x][pieceParts[i].y] = Filled;
				createNewPiece();
			}
		} else
		{
			currentPieceY++;
		}
		sinceLastPieceMove -= moveTime;
	}
	updateBoard();
}

void Board::handleKeyPress(Keyboard::Key key)
{
	vector<Pair> piecePartsLocations = getPieceParts();

	switch (key)
	{
		case Keyboard::Left:
			if (this->canMove(-1, 0))
			{
				currentPieceX--;
			}
			break;
		case Keyboard::Right:
			if (this->canMove(1, 0))
			{
				currentPieceX++;
			}
			break;
		case Keyboard::Down:
			if (this->canMove(0, 1))
			{
				currentPieceY++;
			}
			break;
	}
}

void Board::updateBoard()
{
	for (int x = 0; x < cells.size(); x++)
	{
		for (int y = 0; y < cells[x].size(); y++)
		{
			if (cells[x][y] == PiecePart)
			{
				cells[x][y] = Empty;
			}
		}
	}

	const std::vector<bool> shape = pieces[currentPiece];

	for (int i = 0; i < 8; i++)
	{ //first line
		if (shape[i])
		{
			int xPos = i % 4 + currentPieceX;
			int yPos = i / 4 + currentPieceY;

			cells[xPos][yPos] = PiecePart;
		}
	}
}

vector<Pair> Board::getPieceParts()
{
	vector<Pair> piecePartsLocations;
	for (int x = 0; x < cells.size(); x++)
	{
		for (int y = 0; y < cells[x].size(); y++)
		{
			if (cells[x][y] == PiecePart)
			{
				piecePartsLocations.push_back(Pair(x, y));
			}
		}
	}
	return piecePartsLocations;
}

bool Board::canMove(int relativeX, int relativeY)
{
	bool canMove = true;
	vector<Pair> piecePartsLocations = getPieceParts();
	//find all piece parts and check if there is no end of screen or brigh on the left of it
	for (int i = 0; i < piecePartsLocations.size(); ++i)
	{
		//x
		if (piecePartsLocations[i].x + relativeX > this->x)
		{
			canMove = false;
		} else if (piecePartsLocations[i].x + relativeX < 0)
		{
			canMove = false;
		} else if (cells[piecePartsLocations[i].x + relativeX][piecePartsLocations[i].y] == Filled)
		{
			canMove = false;
		} else if (piecePartsLocations[i].y + relativeY >= this->y) //y
		{
			canMove = false;
		} else if (piecePartsLocations[i].y + relativeY < 0)
		{
			canMove = false;
		} else if (cells[piecePartsLocations[i].x + relativeX][piecePartsLocations[i].y + relativeY] == Filled)
		{
			canMove = false;
		}
	}

	return canMove;
}


std::map<PieceType, std::vector<bool>> pieces = {
		{
				PieceType::I, {1, 1, 1, 1, 0, 0, 0, 0}
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

Pair::Pair(int x, int y)
{
	this->x = x;
	this->y = y;
}
