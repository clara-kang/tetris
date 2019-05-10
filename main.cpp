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
using namespace std;

int level = 1;
int ground_y = 0;
bool gameover = true;
Block *newBlock;
Block *shadowBlock;
Grid grid(grid_w, grid_h);

float getLevelRate(int level) {
	return 0.5f * level;
}

void drawGridLines(sf::RenderWindow &window) {
	const int win_w = window.getSize().x;
	const int win_h = window.getSize().y;
	int cell_w = win_w / grid_w;
	int cell_h = win_h / grid_h;

	for (int i = 0; i < grid_w; i++) {
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

void drawShadowCell(sf::RenderWindow &window, int x, int y) {
	float l_thckns = 2.f;
	sf::RectangleShape shape(sf::Vector2f(cell_w - 2.f * l_thckns, cell_h - 2.f * l_thckns));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(l_thckns);
	shape.setPosition(x * cell_w + l_thckns, y * cell_h + l_thckns);
	window.draw(shape);
}

void drawCell(sf::RenderWindow &window, int x, int y) {
	sf::RectangleShape shape(sf::Vector2f(cell_w, cell_h));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(x * cell_w, y * cell_h);
	window.draw(shape);
}

void drawBlock(sf::RenderWindow &window, Block &block) {
	auto cells = block.getCells();
	array<int, 2> block_pos = block.getPos();
	for (int i = 0; i < 4; i++) {
		array<int, 2> cell = (*cells)[i];
		drawCell(window, cell[0], cell[1]);
	}
}

void drawShadowBlock(sf::RenderWindow &window, Block &block) {
	auto cells = block.getCells();
	array<int, 2> block_pos = block.getPos();
	for (int i = 0; i < 4; i++) {
		array<int, 2> cell = (*cells)[i];
		drawShadowCell(window, cell[0], cell[1]);
	}
}

void drawGrid(sf::RenderWindow &window, Grid &grid) {
	auto &grid_fills = grid.getGrid();
	for (int i = 0; i < grid_w; i++) {
		for (int j = 0; j < grid_h; j++) {
			if (grid_fills[j][i]) {
				drawCell(window, i, j);
			}
		}
	}
}

void drawButton(sf::RenderWindow &window, string words) {
	sf::Text text;
	text.setString("PLAYAGAIN");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	sf::RectangleShape shape(sf::Vector2f(button_w, button_h));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2.f);
	shape.setPosition(button_x, button_y);
	window.draw(shape);
	window.draw(text);

}

void generateNewBlock() {
	int block_type = 1 + rand() % 2;
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
	default:
		break;
	}
}

// transfer block cells positions to grid, remove block, create new block
void blockToGrid() {
	grid.fillGrid(*newBlock);
	grid.clearRow();
	delete newBlock;
	delete shadowBlock;
	generateNewBlock();
	// grid overflow, game over
	if (grid.collide(*newBlock)) {
 		cout << "game over!" << endl;
		gameover = true;
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
				ground_y = grid.getGroundY(*newBlock);
				shadowBlock->setPos(newBlock->getX(), ground_y);
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
			cout << "key pressed" << endl;
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
			ground_y = grid.getGroundY(*newBlock);
			shadowBlock->setPos(newBlock->getX(), ground_y);
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(win_w, win_h), "SFML works!");
	
	sf::Clock clock;
	sf::Time elapsed;
	
	generateNewBlock();

	ground_y = grid.getGroundY(*newBlock);
	shadowBlock->setPos(newBlock->getX(), ground_y);

	while (window.isOpen()) {
		if (!gameover) {
			pollEvent(window);
			elapsed = clock.getElapsedTime();
			if (elapsed.asSeconds() >= getLevelRate(level)) {
				newBlock->moveDown();
				// reach ground
				if (grid.collide(*newBlock)) {
					newBlock->moveUp();
					blockToGrid();
				};
				clock.restart();
			}
			window.clear();
			drawBlock(window, *newBlock);
			drawShadowBlock(window, *shadowBlock);
			drawGrid(window, grid);
			drawGridLines(window);
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