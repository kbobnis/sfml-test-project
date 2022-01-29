//
// Created by Krzysiek on 26/01/2022.
//

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pair.h"
#include <iostream>

using namespace sf;
using namespace std;

Board::Board(const int columns, const int y, const int cellWidth, int cellHeight, float moveTime) :
		moveTime(moveTime),
		cell(Vector2f(cellWidth, cellHeight))
{
	this->columns = columns;
	this->rows = y;
	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;

	this->createNewPiece();

	cells.resize(columns);
	for (int i = 0; i < columns; ++i)
	{
		cells[i].resize(y);
	}

	for (int i = 0; i < columns; ++i)
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
	currentPieceX = columns / 2;
	currentPieceY = 0;
}

void Board::draw(RenderTarget *window)
{
	for (int y = 0; y < this->rows; y++)
	{
		for (int x = 0; x < this->columns; x++)
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

void Board::movePieceDown(const sf::Time &delta)
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
	updateCells();
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

void Board::updateCells()
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

	const std::vector<Pair> shape = pieces[currentPiece];
	for (int i = 0; i < shape.size(); i++)
	{
		int rotatedX = shape[i].x;
		int rotatedY = shape[i].y;

		///rotate 90' point
		//columns' = -(rows - py) + px
		//rows' = (columns - px) + py
		Pair rotationPoint(1, 0);

		for (int j = 0; j < rotation; ++j)
		{
			int tmp = rotatedX;
			rotatedX = -(rotatedY - rotationPoint.y) + rotationPoint.x;
			rotatedY = (tmp - rotationPoint.x) + rotationPoint.y;

			//rotate rotation point
			//int tmpRP = rotationPoint.columns;
			//rotationPoint.columns = - rotationPoint.rows;
			//rotationPoint.rows = tmpRP;
		}

		int xPos = currentPieceX - 2 + rotatedX;
		int yPos = currentPieceY + rotatedY;

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
		if (piecePartsLocations[i].x + relativeX >= this->columns)
		{
			canMove = false;
		} else if (piecePartsLocations[i].x + relativeX < 0)
		{
			canMove = false;
		} else if (cells[piecePartsLocations[i].x + relativeX][piecePartsLocations[i].y] == Filled)
		{
			canMove = false;
		} else if (piecePartsLocations[i].y + relativeY >= this->rows) //rows
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

void Board::clearLines()
{
	vector<Pair> pieceParts = getPieceParts();

	vector<bool> rowsToClear;
	for (int y = 0; y < this->rows; y++)
	{
		rowsToClear.push_back(true);
		for (int x = 0; x < this->columns; x++)
		{
			if (cells[x][y] == Empty || cells[x][y] == PiecePart)
			{
				rowsToClear[y] = false;
				break;
			}
		}
	}

	for (int y = 0; y < this->rows; y++)
	{
		if (rowsToClear[y])
		{
			for (int x = 0; x < cells.size(); x++)
			{
				cells[x][y] = Empty;
			}
		}
	}

	for (int y = this->rows - 1; y >= 0; y--)
	{
		if (rowsToClear[y])
		{
			for (int y2 = y; y2 > 0; y2--)
			{
				for(int x=0; x < this->columns; x++){
					cells[x][y2] = cells[x][y2-1];
				}
			}
		}
	}
}


std::map<PieceType, std::vector<Pair>> pieces = {
		{
				I, {Pair(0, 0), Pair(1, 0), Pair(2, 0), Pair(3, 0)}
		},
		{
				J, {Pair(0, 0), Pair(0, 1), Pair(1, 1), Pair(2, 1)}
		},
		{
				L, {Pair(3, 0), Pair(1, 1), Pair(2, 1), Pair(3, 1)}
		},
		{
				O, {Pair(1, 0), Pair(2, 0), Pair(1, 1), Pair(2, 1)}
		},
		{
				S, {Pair(1, 0), Pair(2, 0), Pair(0, 1), Pair(1, 1)}
		},
		{
				T, {Pair(1, 0), Pair(0, 1), Pair(1, 1), Pair(2, 1)}
		},
		{
				Z, {Pair(0, 0), Pair(1, 0), Pair(1, 1), Pair(2, 1)}
		},
};


