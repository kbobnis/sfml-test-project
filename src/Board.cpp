//
// Created by Krzysiek on 26/01/2022.
//

#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>

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
	sinceLastBoardTick += delta.asMicroseconds();

	if (sinceLastBoardTick > moveTime * 1000000)
	{
		if (this->canMove(0, 1) == false)
		{
			turnPieceIntoFill();
		} else
		{
			currentPieceY++;
		}
		sinceLastBoardTick -= moveTime * 1000000;
	}
	updateBoard();
}

void Board::handleKeyPress(Keyboard::Key key)
{
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
			} else
			{
				turnPieceIntoFill();
			}
			break;
		case Keyboard::Up:
		case Keyboard::Space:
			if (this->canRotate())
			{
				this->rotate();
			}
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

	const std::vector<Pair> currentPieceShape = pieces[currentPiece];
	for (int i = 0; i < currentPieceShape.size(); i++)
	{
		int xPos = currentPieceX - 2 + currentPieceShape[i].x;
		int yPos = currentPieceY + currentPieceShape[i].y;

		cells[xPos][yPos] = PiecePart;
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
		if (piecePartsLocations[i].x + relativeX >= this->x)
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

void Board::turnPieceIntoFill()
{
	vector<Pair> pieceParts = getPieceParts();
	for (int i = 0; i < pieceParts.size(); ++i)
	{
		cells[pieceParts[i].x][pieceParts[i].y] = Filled;
		createNewPiece();
	}
}

bool Board::canRotate()
{
	return true;
}

void Board::rotate()
{
	this->rotation++;
	this->rotation %= 4;
}


std::map<PieceType, std::vector<Pair>> pieces = {
		{
				PieceType::I, {Pair(0, 0), Pair(1, 0), Pair(2, 0), Pair(3, 0)}
		},
		{
				PieceType::J, {Pair(0, 0), Pair(0, 1), Pair(1, 1), Pair(2, 1)}
		},
		{
				PieceType::L, {Pair(3, 0), Pair(1, 1), Pair(2, 1), Pair(3, 1)}
		},
		{
				PieceType::O, {Pair(1, 0), Pair(2, 0), Pair(1, 1), Pair(2, 1)}
		},
		{
				PieceType::S, {Pair(1, 0), Pair(2, 0), Pair(0, 1), Pair(1, 1)}
		},
		{
				PieceType::T, {Pair(1, 0), Pair(0, 1), Pair(1, 1), Pair(2, 1)}
		},
		{
				PieceType::Z, {Pair(0, 0), Pair(1, 0), Pair(1, 1), Pair(2, 1)}
		},
};

Pair::Pair(int x, int y)
{
	this->x = x;
	this->y = y;
}
