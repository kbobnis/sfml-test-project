//
// Created by Krzysiek on 27/01/2022.
//
#pragma once

#include <SFML/Graphics.hpp>
#include "Pair.h"

using namespace sf;
using namespace std;

enum FillType
{
	Empty, Filled, PiecePart
};

enum PieceType
{
	I, J, L, O, S, T, Z
};

std::map<PieceType, std::vector<Pair>> extern pieces;

class Board
{
private:
	const float moveTime;
	int x, y;
	int cellWidth, cellHeight;
	vector<vector<FillType>> cells;
	RectangleShape cell;

	long sinceLastBoardTick;
	PieceType currentPiece;
	int currentPieceX = 0, currentPieceY = 0;
	int rotation; //value 0, 1, 2, 3

public:
	Board(const int x, const int y, const int cellWidth, int cellHeight, float moveTime);

	void createNewPiece();

	void draw(RenderTarget *window);

	void tick(const sf::Time &delta);

	void handleKeyPress(Keyboard::Key key);

	void updateCells();

	vector<Pair> getPieceParts();

	bool canMove(int relativeX, int relativeY);

	void turnPieceIntoFill();

	bool canRotate();

	void rotate();

};

