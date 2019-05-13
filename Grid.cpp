#include "Grid.h"

Grid::Grid(int w, int h) : width (w), height (h) {
	resetGrid();
}

array<int, 2> operator+(const array<int, 2>& lhs, const array<int, 2>& rhs) {
	return{ { lhs[0] + rhs[0], lhs[1] + rhs[1] } };
}

bool operator>(const vector<int>& lhs, const vector<int>& rhs) {
	bool result = true;
	if (lhs.size() != rhs.size()) {
		return false;
	}
	vector<int>::const_iterator lit = lhs.begin();
	vector<int>::const_iterator rit = rhs.begin();
	for (; lit != lhs.end(); ++lit, ++rit) {
		result = result && (*lit) > (*rit);
	}
	return result;
}

void Grid::resetGrid() {
	std::vector<int> row(width, 0);
	for (int i = 0; i < height; i++) {
		grid.push_back(row);
	}
}

const grid_t (&Grid::getGrid() const) {
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

bool Grid::collide(const cell_t cells) {
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

void Grid::fillGrid(const Block& block, int block_type) {
	auto cells = block.getCells();
	for (array<int, 2> cell : *cells) {
		grid[cell[1]][cell[0]] = block_type;
	}
}

int Grid::clearRow() {
	vector<int> false_v = vector<int>(width, 0);
	int rows_cleared = 0;
	for (int i = 0; i < height; i++) {
		if (grid[i] > false_v) {
			cout << "clear row : " << i << endl;
			rows_cleared++;
			grid.erase(grid.begin() + i);
			grid.insert(grid.begin(), false_v);
		}
	}
	return rows_cleared;
}

void Grid::clearGrid() {
	grid = grid_t();
	resetGrid();
}