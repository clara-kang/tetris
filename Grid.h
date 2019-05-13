#pragma once
#ifndef _GRID_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "block.h"
#define _GRID_H

array<int, 2> operator+(const array<int, 2>& lhs, const array<int, 2>& rhs);
bool operator>(const vector<int>& lhs, const vector<int>& rhs);
typedef std::vector<std::vector<int>> grid_t;

class Grid {
public:
	Grid(int width, int height);
	const int width;
	const int height;
	bool collide(const Block& block);
	void fillGrid(const Block& block, int block_type);
	const grid_t(&getGrid() const);
	int getGroundY(const Block& block);
	int clearRow();
	void clearGrid();
private:
	bool collide(const cell_t cells);
	void resetGrid();
	grid_t grid;
};

#endif 