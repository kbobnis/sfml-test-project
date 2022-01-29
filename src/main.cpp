#include <SFML/Graphics.hpp>
#include "Board.h"

using namespace sf;

//https://www.youtube.com/watch?v=4oh-tmxtIrA&ab_channel=IntMain
//https://dev.to/giovannicodes/sfml-2-5-1-setup-on-macos-with-clion-505m

int main()
{
	int width = 480;
	int height = 640;
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Application");
	window.setFramerateLimit(60);

	const int CellsCountVertical = 20;
	const int CellsCountHorizontal = 10;

	float cellHeight = height / CellsCountVertical;
	float cellWidth = width / CellsCountHorizontal;

	Board board(CellsCountHorizontal, CellsCountVertical, cellWidth, cellHeight, 1);
	Clock clock;

	while (window.isOpen())
	{
		sf::Event e;

		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			// keyboard interrupt
			if (e.type == Event::KeyPressed)
			{
				switch (e.key.code)
				{
					case Keyboard::Escape:
						window.close();
						break;
				}
				board.handleKeyPress(e.key.code);
			}
		}

		board.movePieceDown(clock.restart());
		board.clearLines();


		window.clear();
		board.draw(&window);
		window.display();
	}
}