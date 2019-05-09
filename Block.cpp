#include "block.h"

Block::Block() {

}

Block::Block(int x, int y, int boundX, int boundY) : 
	angle(0), 
	pos({ {x, y} }),
	boundX(boundX),
	boundY(boundY) {

}

void Block::setPos(int x, int y) {
	array<int, 2> pot_pos = { {x, y} };
	if (boundCheck(pot_pos)) {
		pos = pot_pos;
	}
}

void Block::moveLeft() {
	setPos(pos[0] - 1, pos[1]);
}

void Block::moveRight() {
	setPos(pos[0] + 1, pos[1]);
}

void Block::moveDown() {
	setPos(pos[0], pos[1] + 1);
}

array<int, 2> (&Block::getPos() const){
	auto res_pos = const_cast<array<int, 2>&>(pos);
	return res_pos;
}

unique_ptr<array<array<int, 2>, 4 >> Block::getCells() const{
	decltype(cells) abs_cells;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			abs_cells[i][j] = cells[i][j] + pos[j];
		}
	}
	auto cells_ptr = make_unique<array<array<int, 2>, 4 >>(abs_cells);
	return cells_ptr;
}

bool Block::boundCheck(array<int, 2> pot_pos) {
	for (int i = 0; i < 4; i++) {
		array<int, 2> cell = { {cells[i][0] + pot_pos[0], cells[i][1] + pot_pos[1]} };
		if (cell[0] >= boundX || cell[0] < 0) {
			return false;
		}
	}
	return true;
}

const array<array<int, 2>, 4> BlockType1::cell_0 = { { {{ 0, 0 }}, {{ 0, 1 }}, {{ 0, 2 }}, {{ 0, 3 }} } };
const array<array<int, 2>, 4> BlockType1::cell_90 = { { { { 1, 0 } },{ { 0, 0 } },{ { -1, 0 } },{ { -2, 0 } } } };

BlockType1::BlockType1(int x, int y, int boundX, int boundY) : Block(x, y, boundX, boundY) {
	cells = cell_0;
}

void BlockType1::rotate() {
	angle = (angle + 90) % 360;
	if (angle == 0 || angle == 180) {
		cells = cell_0;
	}
	else {
		cells = cell_90;
	}
}

