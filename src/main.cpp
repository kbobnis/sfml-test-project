#include <SFML/Graphics.hpp>
#include "Board.cpp"

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

	Board board(CellsCountHorizontal, CellsCountVertical, cellWidth, cellHeight);

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
				if (e.key.code == Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		//cell.setPosition(mouse.x - 20, mouse.y - 20);

		window.clear();
		board.draw(&window);
		//window.draw(cell);
		window.display();
	}
}