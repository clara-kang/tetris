#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "block.h"
#include "Grid.h"

const int grid_w = 10;
const int grid_h = 20;
const int win_w = 300;
const int win_h = 600;
const int cell_w = win_w / grid_w;
const int cell_h = win_h / grid_h;
const int button_x = 115;
const int button_y = 300;
const int button_w = 70;
const int button_h = 30;
const int score_w = 100;
const int score_h = 50;
const int level_time = 60; // time in secs in one level

using namespace std;

int level = 1;
int block_type = 0;
int ground_y = 0;
int rows_cleared = 0;
float rate = 0; // time between block check
bool gameover = true;
array<sf::Color, 7> block_colors;
Block *newBlock;
Block *shadowBlock;
Grid grid(grid_w, grid_h);
sf::Font font;

float getLevelRate(int level) {
	return 0.5f / level;
}

void drawGridLines(sf::RenderWindow &window) {
	int cell_w = win_w / grid_w;
	int cell_h = win_h / grid_h;

	for (int i = 0; i < grid_w + 1; i++) {
		sf::Vertex vertical_line[] = { 
			sf::Vertex(sf::Vector2f(cell_w * i, 0.f)), 
			sf::Vertex(sf::Vector2f(cell_w * i, win_h))
		};
		window.draw(vertical_line, 2, sf::Lines);
	}
	for (int i = 0; i < grid_h; i++) {
		sf::Vertex horizontal_line[] = {
			sf::Vertex(sf::Vector2f(0.f, cell_h * i)),
			sf::Vertex(sf::Vector2f(win_w, cell_h * i))
		};
		window.draw(horizontal_line, 2, sf::Lines);
	}
}

void drawShadowCell(sf::RenderWindow &window, int x, int y, const sf::Color &color) {
	float l_thckns = 2.f;
	sf::RectangleShape shape(sf::Vector2f(cell_w - 2.f * l_thckns - 1.f, cell_h - 2.f * l_thckns - 1.f));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(color);
	shape.setOutlineThickness(l_thckns);
	shape.setPosition(x * cell_w + l_thckns, y * cell_h + l_thckns + 1);
	window.draw(shape);
}

void drawCell(sf::RenderWindow &window, int x, int y, const sf::Color &color) {
	sf::RectangleShape shape(sf::Vector2f(cell_w, cell_h));
	shape.setFillColor(color);
	shape.setPosition(x * cell_w, y * cell_h);
	window.draw(shape);
}

void drawBlock(sf::RenderWindow &window, Block &block) {
	auto cells = block.getCells();
	array<int, 2> block_pos = block.getPos();
	for (int i = 0; i < 4; i++) {
		array<int, 2> cell = (*cells)[i];
		drawCell(window, cell[0], cell[1], block_colors[block_type-1]);
	}
}

void drawShadowBlock(sf::RenderWindow &window, Block &block) {
	auto cells = block.getCells();
	array<int, 2> block_pos = block.getPos();
	for (int i = 0; i < 4; i++) {
		array<int, 2> cell = (*cells)[i];
		drawShadowCell(window, cell[0], cell[1], block_colors[block_type - 1]);
	}
}

void drawGrid(sf::RenderWindow &window, Grid &grid) {
	auto &grid_fills = grid.getGrid();
	for (int i = 0; i < grid_w; i++) {
		for (int j = 0; j < grid_h; j++) {
			if (grid_fills[j][i]) {
				drawCell(window, i, j, block_colors[grid_fills[j][i] - 1]);
			}
		}
	}
}

void drawButton(sf::RenderWindow &window, string words) {
	sf::Text text("PLAY", font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(button_x, button_y);

	sf::RectangleShape shape(sf::Vector2f(button_w, button_h));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2.f);
	shape.setPosition(button_x, button_y);
	window.draw(shape);
	window.draw(text);
}

void drawScoreBoard(sf::RenderWindow &window) {
	sf::Text text("Score:" + to_string(rows_cleared), font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(win_w + 55.f, win_h / 2. - 50.f);

	sf::RectangleShape shape(sf::Vector2f(score_w, score_h));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2.f);
	shape.setPosition(win_w + 50.f, win_h / 2. - 50.f);
	window.draw(shape);
	window.draw(text);
}
void drawLevelBoard(sf::RenderWindow &window) {
	sf::Text text("Level:" + to_string(level), font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(win_w + 55.f, win_h / 2. - 50.f - score_h * 2.f);

	sf::RectangleShape shape(sf::Vector2f(score_w, score_h));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2.f);
	shape.setPosition(win_w + 50.f, win_h / 2. - 50.f - score_h * 2.f);
	window.draw(shape);
	window.draw(text);
}

void generateNewBlock() {
	block_type = 1 + rand() % 7;
	cout << "block_type: " << block_type << endl;
	switch (block_type)
	{
	case 1:
		newBlock = new BlockType1(grid.width / 2, 0);
		shadowBlock = new BlockType1(grid.width / 2, 0);
		break;
	case 2:
		newBlock = new BlockType2(grid.width / 2, 0);
		shadowBlock = new BlockType2(grid.width / 2, 0);
		break;
	case 3:
		newBlock = new BlockType3(grid.width / 2, 0);
		shadowBlock = new BlockType3(grid.width / 2, 0);
		break;
	case 4:
		newBlock = new BlockType4(grid.width / 2, 0);
		shadowBlock = new BlockType4(grid.width / 2, 0);
		break;
	case 5:
		newBlock = new BlockType5(grid.width / 2, 0);
		shadowBlock = new BlockType5(grid.width / 2, 0);
		break;
	case 6:
		newBlock = new BlockType6(grid.width / 2, 0);
		shadowBlock = new BlockType6(grid.width / 2, 0);
		break;
	case 7:
		newBlock = new BlockType7(grid.width / 2, 0);
		shadowBlock = new BlockType7(grid.width / 2, 0);
		break;
	default:
		break;
	}
	ground_y = grid.getGroundY(*newBlock);
	shadowBlock->setPos(newBlock->getX(), ground_y);
}

void resetStats() {
	level = 1;
	rate = getLevelRate(level);
	rows_cleared = 0;
}

// transfer block cells positions to grid, remove block, create new block
void blockToGrid() {
	grid.fillGrid(*newBlock, block_type);
	rows_cleared += grid.clearRow();
	delete newBlock;
	delete shadowBlock;
	generateNewBlock();
	rate = getLevelRate(level);
	// grid overflow, game over
	if (grid.collide(*newBlock)) {
 		cout << "game over!" << endl;
		gameover = true;
		resetStats();
	}
}

void pollStandbyEvent(sf::RenderWindow &window) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i position = sf::Mouse::getPosition(window);
			cout << "position.x: " << position.x << ", position.y: " << position.y << endl;

			if (position.x >= button_x && position.x <= button_x + button_w &&
				position.y >= button_y && position.y <= button_y + button_h) {
				grid.clearGrid();
				generateNewBlock();
				gameover = false;
			}
		}
	}
}
void pollEvent(sf::RenderWindow &window) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::R) {
				newBlock->rotateCw();
				if (grid.collide(*newBlock)) {
					newBlock->rotateCcw();
				}
				else {
					shadowBlock->rotateCw();
				}
			}
			else if (event.key.code == sf::Keyboard::Left) {
				newBlock->moveLeft();
				if (grid.collide(*newBlock)) {
					newBlock->moveRight();
				}
			}
			else if (event.key.code == sf::Keyboard::Right) {
				newBlock->moveRight();
				if (grid.collide(*newBlock)) {
					newBlock->moveLeft();
				}
			}
			else if (event.key.code == sf::Keyboard::Space) {
				swap(newBlock, shadowBlock);
				blockToGrid();
			}
			else if (event.key.code == sf::Keyboard::Down) {
				rate = getLevelRate(level) / 2.f;
			}
			ground_y = grid.getGroundY(*newBlock);
			shadowBlock->setPos(newBlock->getX(), ground_y);
		}
		else if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Down) {
				cout << "down key released" << endl;
				rate = getLevelRate(level);
			}
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(win_w + 200, win_h), "SFML works!");
	
	sf::Clock block_clock;
	sf::Clock level_clock;
	sf::Time block_elapsed;
	sf::Time level_elapsed;

	if (!font.loadFromFile("../fonts/Gula_FREE.ttf")) {
		throw exception("cannot read font");
	}

	generateNewBlock();
	rate = getLevelRate(level);
	ground_y = grid.getGroundY(*newBlock);
	shadowBlock->setPos(newBlock->getX(), ground_y);

	block_colors = { {sf::Color(244, 161, 66), sf::Color(119, 171, 255), sf::Color(255, 124, 119),
		sf::Color(244, 236, 78), sf::Color(167, 231, 239), sf::Color(188, 155, 255), sf::Color(255, 181, 237)} };

	while (window.isOpen()) {
		if (!gameover) {
			pollEvent(window);
			block_elapsed = block_clock.getElapsedTime();
			level_elapsed = level_clock.getElapsedTime();
			if (block_elapsed.asSeconds() >= rate) {
				newBlock->moveDown();
				// reach ground
				if (grid.collide(*newBlock)) {
 					newBlock->moveUp();
					blockToGrid();
				};
				block_clock.restart();
			}
			if (level_elapsed.asSeconds() >= level_time) {
				level += 1;
				rate = getLevelRate(level);
				level_clock.restart();
			}
			window.clear();
			drawBlock(window, *newBlock);
			drawShadowBlock(window, *shadowBlock);
			drawGrid(window, grid);
			drawGridLines(window);
			drawScoreBoard(window);
			drawLevelBoard(window);
			window.display();
		}
		else {
 			pollStandbyEvent(window);
			window.clear();
			drawButton(window, "PLAY AGAIN");
			window.display();
		}
	}

	return 0;
}