//
// Created by Krzysiek on 26/01/2022.
//

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Pair.hpp"
#include <iostream>
#include "observer/EventType.hpp"

using namespace sf;
using namespace std;

Board::Board(const int columns, const int y, const int cellWidth, int cellHeight, float& moveTime) :
		moveTime(moveTime),
		cell(Vector2f(cellWidth, cellHeight)),
		currentPiecePos(columns / 2, 0),
		currentPiece(pieces[0]),
		nextPiece(pieces[0]),
		startingMoveTime(moveTime)
{
	this->columns = columns;
	this->rows = y;
	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;
	cells.resize(columns);
	for (int i = 0; i < columns; ++i)
	{
		cells[i].resize(y);
	}
	cell.setOutlineColor(Color::Green);
	cell.setOutlineThickness(cellWidth / 20);

	startNewGame();
}

void Board::startNewGame()
{
	moveTime = startingMoveTime;
	lost = false;

	rowsToClearDelta = 0;
	sinceLastBoardTick = 0;

	this->rotation = 0; //value 0, 1, 2, 3
	for (int i = 0; i < columns; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			cells[i][j] = Empty;
		}
	}

	nextPiece = pieces[rand() % pieces.size()];
	this->createNewPiece();

	this->notify(GameStarted, 0);
}

void Board::createNewPiece()
{
	currentPiece = nextPiece;
	this->rotation = 0;

	int nextPieceIndex = rand() % pieces.size();
	nextPiece = pieces[nextPieceIndex];
	this->notify(EventType::NextPieceFiguredOut, nextPieceIndex);
	currentPiecePos.x = columns / 2 - currentPiece.GetLength() / 2;
	currentPiecePos.y = 0;

	std::vector<Pair> shapeAfterRotation = currentPiece.GetShapeAfterRotation(this->rotation);
	for (int i = 0; i < shapeAfterRotation.size(); i++)
	{
		int xPos = this->currentPiecePos.x + shapeAfterRotation[i].x;
		int yPos = this->currentPiecePos.y + shapeAfterRotation[i].y;

		if (xPos > 0 && yPos > 0 && cells[xPos][yPos] == Filled)
		{
			this->lost = true;
			this->notify(EventType::Lost, 0);
		}
	}

}

void Board::draw(RenderTarget *window)
{
	cell.setOutlineColor(Color::Black);
	for (int y = 0; y < this->rows; y++)
	{
		for (int x = 0; x < this->columns; x++)
		{
			switch (cells[x][y])
			{
				case Empty:
					cell.setFillColor(Color::White);
					break;
				case Filled:
					cell.setFillColor(Color::Blue);
					break;
				case PiecePart:
					cell.setFillColor(currentPiece.color);
					break;
				case MarkedToClear:
					cell.setFillColor(Color::Yellow);
					break;
			}

			cell.setPosition(Vector2f(x * cellWidth, y * cellHeight));
			window->draw(cell);
		}
	}

}

void Board::tick(const sf::Time& delta)
{
	Int64 microseconds = delta.asMicroseconds();
	sinceLastBoardTick += microseconds;

	if (rowsToClearDelta > 0)
	{
		rowsToClearDelta += microseconds;
	}

	if (sinceLastBoardTick > moveTime * 1000000)
	{
		if (this->canMove(0, 1) == false)
		{
			turnPieceIntoFill();
		} else
		{
			currentPiecePos.y++;

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
				currentPiecePos.x--;
			}
			break;
		case Keyboard::Right:
			if (this->canMove(1, 0))
			{
				currentPiecePos.x++;
			}
			break;
		case Keyboard::Down:
			if (this->canMove(0, 1))
			{
				currentPiecePos.y++;
			} else
			{
				turnPieceIntoFill();
			}
			break;
		case Keyboard::Space:
		case Keyboard::Up:
			if (this->lost)
			{
				this->startNewGame();
			}
			this->rotateIfPossible();
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

	std::vector<Pair> shapeAfterRotation = currentPiece.GetShapeAfterRotation(this->rotation);
	for (int i = 0; i < shapeAfterRotation.size(); i++)
	{
		int xPos = this->currentPiecePos.x + shapeAfterRotation[i].x;
		int yPos = this->currentPiecePos.y + shapeAfterRotation[i].y;
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
	}
	createNewPiece();
}

void Board::clearLines()
{
	this->rowsToClearDelta = 0;

	vector<int> rowsToClear = getRowsToClear();
	for (int i = 0; i < rowsToClear.size(); i++)
	{
		clearRow(rowsToClear[i]);
		moveRowsDownUntil(rowsToClear[i]);
	}

	if (rowsToClear.size() > 0)
	{
		this->notify(EventType::RowsCleared, rowsToClear.size());
	}
}

void Board::clearRow(int& rowIndex)
{
	for (int x = 0; x < cells.size(); x++)
	{
		cells[x][rowIndex] = Empty;
	}
}

void Board::moveRowsDownUntil(int& rowIndex)
{
	for (int y = rowIndex; y > 0; y--)
	{
		for (int x = 0; x < cells.size(); x++)
		{
			FillType fillType = cells[x][y - 1];
			if (fillType == PiecePart || fillType == MarkedToClear)
			{
				fillType = Empty;
			}

			cells[x][y] = fillType;
		}
	}
}

bool Board::anyLinesToClear()
{
	return rowsToClearDelta == 0 && getRowsToClear().size() > 0;
}

vector<int> Board::getRowsToClear()
{
	vector<int> rowsToClear;
	for (int y = 0; y < this->rows; y++)
	{
		bool allFilled = true;
		for (int x = 0; x < this->columns; x++)
		{
			if (cells[x][y] == Empty || cells[x][y] == PiecePart)
			{
				allFilled = false;
				break;
			}
		}
		if (allFilled)
		{
			rowsToClear.push_back(y);
		}
	}
	return rowsToClear;
}

void Board::markLinesToClear()
{
	vector<int> rowsToClear = getRowsToClear();
	for (int y: rowsToClear)
	{
		rowsToClearDelta = 1;
		for (int x = 0; x < this->columns; x++)
		{
			cells[x][y] = MarkedToClear;
		}
	}
}

bool Board::markedLinesReadyToClear()
{
	return this->rowsToClearDelta > moveTime * 1000000;
}

bool Board::stillPlaying()
{
	return this->lost == false;
}

Piece& Board::getNextPiece()
{
	return this->nextPiece;
}

void Board::rotateIfPossible()
{
	if (currentPiece.howManyRotations == 1)
	{
		return;
	}

	int moveToTheLeft = 0;
	int moveToTheRight = 0;
	int moveDown = 0;
	std::vector<Pair> afterRotation = currentPiece.GetShapeAfterRotation((this->rotation + 1) % currentPiece.howManyRotations);
	for (int i = 0; i < afterRotation.size(); i++)
	{
		int x = afterRotation[i].x + currentPiecePos.x;
		int y = afterRotation[i].y + currentPiecePos.y;

		if (x < 0)
		{
			int moveTmp = -x;
			moveToTheRight = moveTmp > moveToTheRight ? moveTmp : moveToTheRight;
		}
		if (x >= this->columns)
		{
			int moveTmp = x + 1 - this->columns;
			moveToTheLeft = moveTmp > moveToTheLeft ? moveTmp : moveToTheLeft;
		}
		if (y >= this->rows)
		{
			int moveTmp = y - 1 - this->rows;
			moveDown = moveTmp > moveDown ? moveTmp : moveDown;
		}
	}

	bool collidesWithFilled = false;
	for (int i = 0; i < afterRotation.size(); i++)
	{
		int x = afterRotation[i].x + currentPiecePos.x + moveToTheRight - moveToTheLeft;
		int y = afterRotation[i].y + currentPiecePos.y + moveDown;

		if (cells[x][y] == Filled)
		{
			collidesWithFilled = true;
		}
	}

	//actual rotation happening here
	if ( collidesWithFilled == false){
		this->rotation++;
		this->currentPiecePos.x += moveToTheRight - moveToTheLeft;
		this->currentPiecePos.y += moveDown;
		this->rotation %= currentPiece.howManyRotations;
	}
}

std::vector<Piece> pieces = {
		Piece(I, {Pair(0, 0), Pair(1, 0), Pair(2, 0), Pair(3, 0)}, Pair(2, 0), 2, Color(36, 36, 85)),
		Piece(J, {Pair(0, 0), Pair(0, 1), Pair(1, 1), Pair(2, 1)}, Pair(1, 1), 4, Color(0, 219, 255)),
		Piece(L, {Pair(2, 0), Pair(0, 1), Pair(1, 1), Pair(2, 1)}, Pair(1, 1), 4, Color(73, 73, 85)),
		Piece(O, {Pair(1, 0), Pair(2, 0), Pair(1, 1), Pair(2, 1)}, Pair(0, 0), 1, Color(255, 146, 0)),
		Piece(S, {Pair(1, 0), Pair(2, 0), Pair(0, 1), Pair(1, 1)}, Pair(1, 1), 2, Color(255, 219, 0)),
		Piece(T, {Pair(1, 0), Pair(0, 1), Pair(1, 1), Pair(2, 1)}, Pair(1, 1), 4, Color(146, 0, 255)),
		Piece(Z, {Pair(0, 0), Pair(1, 0), Pair(1, 1), Pair(2, 1)}, Pair(1, 1), 2, Color(219, 0, 0))
};