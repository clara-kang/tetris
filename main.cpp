#include <SFML/Graphics.hpp>
#include <iostream>
#include "block.h"
#include "Grid.h"

const int grid_w = 10;
const int grid_h = 20;
const int win_w = 300;
const int win_h = 600;
const int cell_w = win_w / grid_w;
const int cell_h = win_h / grid_h;

using namespace std;

int level = 1;
BlockType2 *newBlock = new BlockType2(grid_w / 2, 0);
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

void pollEvent(sf::RenderWindow &window) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed) {
			cout << "key pressed" << endl;
			if (event.key.code == sf::Keyboard::R) {
				newBlock->rotateCw();
				if (grid.collide(*newBlock)) {
					newBlock->rotateCcw();
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
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(win_w, win_h), "SFML works!");
	
	sf::Clock clock;
	sf::Time elapsed;

	bool reachedBottom = false;
	while (window.isOpen()) {
		pollEvent(window);
		elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() >= getLevelRate(level)) {
			newBlock->moveDown();
			if (grid.collide(*newBlock)) {
				newBlock->moveUp();
				grid.fillGrid(*newBlock);
				grid.clearRow();
				delete newBlock;
				newBlock = new BlockType2(grid.width / 2, 0);
			};
			clock.restart();
		}
		window.clear();
		drawBlock(window, *newBlock);
		drawGrid(window, grid);
		drawGridLines(window);
		window.display();
	}

	return 0;
}