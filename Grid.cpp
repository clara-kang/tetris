#include "Grid.h"

Grid::Grid(int w, int h) : width (w), height (h) {
	resetGrid();
}

array<int, 2> operator+(const array<int, 2>& lhs, const array<int, 2>& rhs) {
	return{ { lhs[0] + rhs[0], lhs[1] + rhs[1] } };
}

void Grid::resetGrid() {
	std::vector<bool> row(width, false);
	for (int i = 0; i < height; i++) {
		grid.push_back(row);
	}
}

const std::vector<std::vector<bool>>(&Grid::getGrid() const) {
	return grid;
}

int Grid::getGroundY(const Block& block) {
	auto cells = block.getCells();
	int ground_y = height - 1;
	int free_col = 0;
	int fall_dist = 0;
	while (!collide(*cells)) {
		for (int i = 0; i < 4; i++) {
			(*cells)[i][1] += 1;
		}
		fall_dist += 1;
	}
	return block.getY() + fall_dist - 1;
}

bool Grid::collide(const Block& block) {
	auto cells = block.getCells();
	return collide(*cells);
}

bool Grid::collide(const array<array<int, 2>, 4> cells) {
	for (int i = 0; i < 4; i++) {
		array<int, 2> cell = cells[i];
		if (cell[1] >= height || cell[1] < 0 || cell[0] >= width || cell[0] < 0) {
			return true;
		}
		else if (grid[cell[1]][cell[0]]) {
			return true;
		}
	}
	return false;
}

void Grid::fillGrid(const Block& block) {
	auto cells = block.getCells();
	for (array<int, 2> cell : *cells) {
		grid[cell[1]][cell[0]] = true;
	}
}

void Grid::clearRow() {
	vector<bool> true_v = vector<bool>(width, true);
	vector<bool> false_v = vector<bool>(width, false);
	for (int i = 0; i < height; i++) {
		if (grid[i] == true_v) {
			cout << "clear row : " << i << endl;
			grid.erase(grid.begin() + i);
			grid.insert(grid.begin(), false_v);
		}
	}
}

void Grid::clearGrid() {
	grid = std::vector<std::vector<bool>>();
	resetGrid();
}