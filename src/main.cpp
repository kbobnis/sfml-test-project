#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Scoreboard.hpp"
#include "NextPieceBoard.hpp"
#include "Difficulty.hpp"
#include <SFML/Audio.hpp>

using namespace sf;

//https://www.youtube.com/watch?v=4oh-tmxtIrA&ab_channel=IntMain
//https://dev.to/giovannicodes/sfml-2-5-1-setup-on-macos-with-clion-505m

int main()
{
	int width = 640;
	int height = 640;
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML Application");
	window.setFramerateLimit(60);

	const int CellsCountVertical = 20;
	const int CellsCountHorizontal = 10;

	int boardWidth = 480;
	int boardHeight = 640;

	int cellWidth = boardWidth / CellsCountHorizontal;
	int cellHeight = boardHeight / CellsCountVertical;

	float moveTime = 0.5;
	Board board(CellsCountHorizontal, CellsCountVertical, cellWidth, cellHeight, moveTime);
	Clock clock;

	sf::Font font;
	font.loadFromFile("../fonts/Forwa_font.TTF");
	Scoreboard scoreboard(font, boardWidth, width - boardWidth);
	board.registerObserver(&scoreboard);

	NextPieceBoard nextPieceBoard(board.getNextPiece(), font, boardWidth, width - boardWidth, 100);
	board.registerObserver(&nextPieceBoard);

	Difficulty difficulty(&moveTime);
	board.registerObserver(&difficulty);
	sf::Text difficultyText ;
	difficultyText.setFont(font);
	difficultyText.setFillColor(sf::Color::White);
	difficultyText.setPosition(boardWidth + 10, 250);
	difficultyText.setCharacterSize(10);

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

		if (board.stillPlaying())
		{
			board.tick(clock.restart());

			if (board.anyLinesToClear())
			{
				board.markLinesToClear();
			}

			if (board.markedLinesReadyToClear())
			{
				board.clearLines();
			}
		}

		window.clear();
		board.draw(&window);
		window.draw(scoreboard.getScore());
		nextPieceBoard.draw(&window, cellWidth, cellHeight);

		difficultyText.setString("Difficulty: " + std::to_string(difficulty.getDifficulty()));
		window.draw(difficultyText);

		window.display();
	}
}