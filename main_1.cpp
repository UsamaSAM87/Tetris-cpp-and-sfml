#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<TGUI/TGUI.hpp>
#include <iostream>
#include "Board.h"

void Back(bool& x1, bool& x2)
{
	if (!x1 && x2)
		x1 = true, x2 = false;
}

int main()
{
	// creates object of board class
	Board GameBoard;
	//object calls piece generate function
	GameBoard.GeneratePiece();
	//sfml libarry creates main window with its resolution specified and frame limit set so graphics memory dont get burn
	sf::RenderWindow window(sf::VideoMode(800, 720), "Tetris");
	window.setFramerateLimit(60);
	//tgui libary loads the theme file
	tgui::Gui gui(window);
	tgui::Theme theme{ "themes/Black.txt" };
	tgui::Theme::setDefault(&theme);
	//background image of game loaded and graphics font file loaded
	sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setPosition(0, 0);
	sf::Texture bgImageTexture = sf::Texture();
	bgImageTexture.setSmooth(true);
	background.setTexture(&bgImageTexture);
	sf::Font loadingFont = sf::Font();
	if (!loadingFont.loadFromFile("Fonts/arlrdbd.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	//score on graphics set with its color
	int Score = 0;
	sf::Text Scores(sf::String(std::to_string(Score)), loadingFont, 30);
	Scores.setPosition(16, 64);
	Scores.setFillColor(sf::Color::Green);

	sf::Text TScores(sf::String("Score: "), loadingFont, 30);
	TScores.setPosition(16, 32);
	TScores.setFillColor(sf::Color::Magenta);

	sf::Clock universalClock;
	bool isLoading = false;
	bool displayBgImage = false;
	bool MainMenuBar = false;
	bool ScorePrint = false;
	int TS = 0;
	bool Home1I, RandomB, Home1O, Home2O, ExitT;
	Home1I = Home1O = Home2O = ExitT = false;

	//tgui library creates exit button on graphics window and its position and its color is loaded from themes file
	sf::Event event = sf::Event();
	auto* button = new tgui::Button::Ptr[15];
	for (int i = 1; i < 2; i++)
		button[i] = tgui::Button::create();

	button[1]->setRenderer(theme.getRenderer("Button"));
	button[1]->setSize(80, 30);
	button[1]->setPosition(window.getSize().x - 115.f + 25, window.getSize().y - 50.f + 11);
	button[1]->setText("Exit");
	button[1]->connect("pressed", [&]() { ExitT = true; });

	//Tile Properties of the board

	sf::RectangleShape** box = new sf::RectangleShape * [30];
	for (int k = 0; k < 30; k++)
	{
		box[k] = new sf::RectangleShape[17];
	}

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			box[i][j].setSize(sf::Vector2f(20, 20));
		}
	}

	double Xv, Yv = 20;
	for (int i = 0; i < 30; i++)
	{
		Xv = 211;
		for (int j = 0; j < 17; j++)
			box[i][j].setPosition(Xv, Yv), Xv += 22.4;
		Yv += 22.7;

	}

	//windows open function  from sfml

	while (window.isOpen())
	{
		//calls the function from board.h and assigns the color to pieces on board
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				if (GameBoard.board[i][j].GetBoxColor() == 1)
				{
					box[i][j].setFillColor(sf::Color::Red);
				}
				else if (GameBoard.board[i][j].GetBoxColor() == 2)
				{
					box[i][j].setFillColor(sf::Color::Red);
				}
				else if (GameBoard.board[i][j].GetBoxColor() == 3)
				{
					box[i][j].setFillColor(sf::Color::Green);
				}
				else if (GameBoard.board[i][j].GetBoxColor() == 4)
				{
					box[i][j].setFillColor(sf::Color::Blue);
				}
				else if (GameBoard.board[i][j].GetBoxColor() == 5)
				{
					box[i][j].setFillColor(sf::Color::Yellow);
				}
				else if (GameBoard.board[i][j].GetBoxColor() == 6)
				{
					box[i][j].setFillColor(sf::Color::Magenta);
				}
				else if (GameBoard.board[i][j].GetBoxColor() == 7)
				{
					box[i][j].setFillColor(sf::Color::Cyan);
				}
				else
				{
					box[i][j].setFillColor(sf::Color::Black);
				}
			}
		}
		//event created sfml
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (universalClock.getElapsedTime() >= sf::seconds(-0.0008f))
			{
				MainMenuBar = true,
					Home1I = true;
			}
			else if (event.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width),
					static_cast<float>(event.size.height)))), gui.setView(window.getView());

			gui.handleEvent(event);
		}

		if (universalClock.getElapsedTime() >= sf::seconds(2.0f))
		{
			isLoading = true;
		}
		if (universalClock.getElapsedTime() >= sf::seconds(2.0f))
		{
			isLoading = false, displayBgImage = false;
		}

		if (universalClock.getElapsedTime() <= sf::seconds(2.0f))
		{
			displayBgImage = true;
		}
		if (isLoading)
		{
			window.draw(background);
			sf::Clock clock1;
			window.display();
			while (universalClock.getElapsedTime() < sf::seconds(3.0f));
		}

		window.clear();

		if (displayBgImage)
		{
			window.draw(background), window.display(); while (universalClock.getElapsedTime() < sf::seconds(3.0f));
		}
		if (Home1O && !ExitT)
		{
			if (Home1I)
			{
				sf::Clock clock1;
				while (clock1.getElapsedTime() < sf::seconds(1.0f))
					window.draw(background), window.display();
				Home1O = false;
			}
		}
		if (Home1I)
		{
			bgImageTexture.loadFromFile("BackA.png"), background.setTexture(&bgImageTexture, true), Home2O = true;
		}
		if (Home2O && !ExitT)
			if (Home2O)
				if (MainMenuBar)
				{
					sf::Clock clock1;
					window.draw(background);
					Scores.setString(std::to_string(Score));
					window.draw(Scores);
					window.draw(TScores);
					gui.add(button[1]);
					gui.draw();
					//keyboard keys check and their respective functions from board.h called
					if (!ScorePrint)
					{
						for (int i = 0; i < 30; i++)
							for (int j = 0; j < 17; j++)
								window.draw(box[i][j]);
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						{
							GameBoard.Rotate();
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							Score += (GameBoard.Gravity() + 0);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						{
							GameBoard.MoveLeft();
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						{
							GameBoard.MoveRight();
						}
					}
					if (!GameBoard.Gravity())
					{
						while (clock1.getElapsedTime() < sf::seconds(0.04f))
							Score += (GameBoard.LineDetected() * 20);
						if (!GameBoard.GeneratePiece())
							TScores.setFillColor(sf::Color::Black), Scores.setFillColor(sf::Color::Black),
							TScores.setString("Your Score : "), TScores.setPosition(static_cast<float>(window.getSize().x) / 2 - 100,
								0.55 * window.getSize().y - 50), Scores.setPosition(static_cast<float>(window.getSize().x) / 2 - 100,
									0.55 * window.getSize().y - 18), ScorePrint = true;
					}
				}

		if (ExitT)
		{
			sf::Clock clock2;
			while (clock2.getElapsedTime() < sf::seconds(1.0f))
				window.draw(background), window.display();
			gui.removeAllWidgets();
			window.close();
			return 0;
		}
		window.display();
	}

	system("pause");
	return 0;
};