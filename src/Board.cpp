//
// Created by Krzysiek on 26/01/2022.
//
#include <SFML/Graphics.hpp>

#include "FillType.cpp";

using namespace sf;
using namespace std;

class Board
{
private:
	int x, y;
	int cellWidth, cellHeight;
	vector<vector<FillType>> cells;
	RectangleShape cell;

public:

	Board(const int x, const int y, const int cellWidth, int cellHeight) : cell(Vector2f(cellWidth, cellHeight))
	{
		this->x = x;
		this->y = y;
		this->cellWidth = cellWidth;
		this->cellHeight = cellHeight;

		cells.resize(x);
		for (int i = 0; i < x; ++i)
		{
			cells[i].resize(y);
		}

		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				cells[i][j] = FillType::Empty;
			}
		}

		cell.setOutlineColor(Color::Green);
		cell.setOutlineThickness(cellWidth / 20);
	}

	void draw(RenderTarget *window)
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
				}

				cell.setPosition(Vector2f(x * cellWidth, y * cellHeight));
				window->draw(cell);
			}
		}
	}
};