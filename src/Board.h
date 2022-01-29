//
// Created by Krzysiek on 27/01/2022.
//
#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

enum PieceType
{
	I, J, L, O, S, T, Z
};

enum FillType
{
	Empty, Filled, PiecePart
};

struct Pair
{
public:
	Pair(int x, int y);

	int x;
	int y;
};

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

	void updateBoard();

	vector<Pair> getPieceParts();

	bool canMove(int relativeX, int relativeY);

	void turnPieceIntoFill();

	bool canRotate();

	void rotate();

};

std::map<PieceType, std::vector<Pair>> extern pieces;