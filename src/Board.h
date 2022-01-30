//
// Created by Krzysiek on 27/01/2022.
//
#pragma once

#include <SFML/Graphics.hpp>
#include "Pair.h"
#include "Piece.h"

using namespace sf;
using namespace std;

enum FillType
{
	Empty, Filled, PiecePart
};

std::vector<Piece> extern pieces;

class Board
{
private:
	const float moveTime;
	int columns, rows;
	int cellWidth, cellHeight;
	vector<vector<FillType>> cells;
	RectangleShape cell;

	long sinceLastBoardTick = 0;
	Piece currentPiece;
	Pair currentPiecePos;
	int rotation = 0; //value 0, 1, 2, 3

public:
	Board(const int columns, const int y, const int cellWidth, int cellHeight, float moveTime);

	void createNewPiece();

	void draw(RenderTarget *window);

	void movePieceDown(const sf::Time& delta);

	void handleKeyPress(Keyboard::Key key);

	void updateCells();

	vector<Pair> getPieceParts();

	bool canMove(int relativeX, int relativeY);

	void turnPieceIntoFill();

	bool canRotate();

	void rotate();

	void clearLines();
};

