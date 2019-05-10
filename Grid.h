#pragma once
#ifndef _GRID_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "block.h"
#define _GRID_H

array<int, 2> operator+(const array<int, 2>& lhs, const array<int, 2>& rhs);

class Grid {
public:
	Grid(int width, int height);
	const int width;
	const int height;
	bool collide(const Block& block);
	void fillGrid(const Block& block);
	const std::vector<std::vector<bool>>(&getGrid() const);
	int getGroundY(const Block& block);
	void clearRow();
	void clearGrid();
private:
	bool collide(const array<array<int, 2>, 4> cells);
	void resetGrid();
	std::vector<std::vector<bool>> grid;
};

#endif 