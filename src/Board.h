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

class Board
{
private:
	const float moveTime;
	int x, y;
	int cellWidth, cellHeight;
	vector<vector<bool>> cells;
	RectangleShape cell;

	float sinceLastPieceMove;
	PieceType currentPiece;
	int currentPieceX, currentPieceY;

public:
	Board(const int x, const int y, const int cellWidth, int cellHeight, float moveTime);

	void createNewPiece();

	void drawPiece(RenderTarget *window);

	void draw(RenderTarget *window);

	void tick(const sf::Time &delta);

	void handleKeyPress(Keyboard::Key key);
};

std::map<PieceType, std::vector<bool>> extern pieces;