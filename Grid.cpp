#include "Grid.h"

Grid::Grid(int w, int h) : width (w), height (h) {
	resetGrid();
}

array<int, 2> operator+(const array<int, 2>& lhs, const array<int, 2>& rhs) {
	return{ { lhs[0] + rhs[0], lhs[1] + rhs[1] } };
}

void Grid::resetGrid() {
	std::vector<bool> col(height, false);
	for (int i = 0; i < width; i++) {
		grid.push_back(col);
	}
}

const std::vector<std::vector<bool>>(&Grid::getGrid() const) {
	return grid;
}

bool Grid::reachedBottom(const Block &block) {
	auto cells = block.getCells();
	array<array<int, 2>, 4> cells_n = *cells;

	for (int i = 0; i < 4; i++) {
		cells_n[i][1] += 1;
	}
	for_each(cells->begin(), cells->end(), [](array<int, 2> c) {cout << c[0] << ", " << c[1] << endl; });
	cout << endl;
	for_each(cells_n.begin(), cells_n.end(), [](array<int, 2> c) {cout << c[0] << ", " << c[1] << endl; });
	for (int i = 0; i < 4; i++) {
		array<int, 2> cell = { { (*cells)[i][0], (*cells)[i][1] + 1} };
		if (cell[1] >= height) {
			return true;
		} else if (grid[cell[0]][cell[1]]) {
			return true;
		}
	}
	return false;
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
		else if (grid[cell[0]][cell[1]]) {
			return true;
		}
	}
	return false;
}

void Grid::fillGrid(const Block& block) {
	auto cells = block.getCells();
	for (array<int, 2> cell : *cells) {
		grid[cell[0]][cell[1]] = true;
	}
}