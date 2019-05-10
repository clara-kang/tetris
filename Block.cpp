#include "block.h"

Block::Block() {

}

Block::Block(int x, int y) : 
	angle(0), 
	pos({ {x, y} }) {

}

int Block::getX() const {
	return pos[0];
}

int Block::getY() const{
	return pos[1];
}

void Block::setPos(int x, int y) {
	pos[0] = x;
	pos[1] = y;
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

void Block::moveUp() {
	setPos(pos[0], pos[1] - 1);
}

array<int, 2> (&Block::getPos() const){
	auto res_pos = const_cast<array<int, 2>&>(pos);
	return res_pos;
}

unique_ptr<array<array<int, 2>, 4 >> Block::getCells() const{
	cell_t abs_cells;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			abs_cells[i][j] = (*cells)[i][j] + pos[j];
		}
	}
	auto cells_ptr = make_unique<cell_t>(abs_cells);
	return cells_ptr;
}

const array<array<int, 2>, 4> BlockType1::cell_0 = { { {{ 0, 0 }}, {{ 0, 1 }}, {{ 0, 2 }}, {{ 0, 3 }} } };
const array<array<int, 2>, 4> BlockType1::cell_90 = { { { { 1, 0 } },{ { 0, 0 } },{ { -1, 0 } },{ { -2, 0 } } } };

const array<array<int, 2>, 4> BlockType2::cell_0 = { { { { 0, 0 } },{ { -1, 1 } },{ { 0, 1 } },{ { 1, 1 } } } };
const array<array<int, 2>, 4> BlockType2::cell_90 = { { { { 0, 0 } },{ { 0, -1 } },{ { 1, 0 } },{ { 0, 1 } } } };
const array<array<int, 2>, 4> BlockType2::cell_180 = { { { { 0, 0 } },{ { -1, 0 } },{ { 1, 0 } },{ { 0, 1 } } } };
const array<array<int, 2>, 4> BlockType2::cell_270 = { { { { 0, 0 } },{ { 0, -1 } },{ { -1, 0 } },{ { 0, 1 } } } };

const array<array<int, 2>, 4> BlockType3::cell_0 = { { { { 0, 0 } },{ { 1, 0 } },{ { 0, 1 } },{ { -1, 1 } } } };
const array<array<int, 2>, 4> BlockType3::cell_90 = { { { { 0, 0 } },{ { 0, 1 } },{ { 1, 1 } },{ { 1, 2 } } } };

const array<array<int, 2>, 4> BlockType4::cell_0 = { { { { 0, 0 } },{ { -1, 0 } },{ { 0, 1 } },{ { 1, 1 } } } };
const array<array<int, 2>, 4> BlockType4::cell_90 = { { { { 0, 0 } },{ { 0, 1 } },{ { -1, 1 } },{ { -1, 2 } } } };

const array<array<int, 2>, 4> BlockType5::cell_0 = { { { { 0, 0 } },{ { 1, 0 } },{ { 0, 1 } },{ { 0, 2 } } } };
const array<array<int, 2>, 4> BlockType5::cell_90 = { { { { 0, 0 } },{ { -1, 0 } },{ { -2, 0 } },{ { 0, 1 } } } };
const array<array<int, 2>, 4> BlockType5::cell_180 = { { { { 0, 0 } },{ { 0, 1 } },{ { 0, 2 } },{ { -1, 2 } } } };
const array<array<int, 2>, 4> BlockType5::cell_270 = { { { { 0, 1 } },{ { -1, 1 } },{ { -2, 1 } },{ { -2, 0 } } } };

const array<array<int, 2>, 4> BlockType6::cell_0 = { { { { 0, 0 } },{ { -1, 0 } },{ { 0, 1 } },{ { 0, 2 } } } };
const array<array<int, 2>, 4> BlockType6::cell_90 = { { { { 0, 0 } },{ { 0, 1 } },{ { -1, 1 } },{ { -2, 1 } } } };
const array<array<int, 2>, 4> BlockType6::cell_180 = { { { { 0, 0 } },{ { 0, 1 } },{ { 0, 2 } },{ { 1, 2 } } } };
const array<array<int, 2>, 4> BlockType6::cell_270 = { { { { 0, 0 } },{ { 1, 0 } },{ { 2, 0 } },{ { 0, 1 } } } };

const array<array<int, 2>, 4> BlockType7::cell_0 = { { { { 0, 0 } },{ { 1, 0 } },{ { 1, 1 } },{ { 0, 1 } } } };

BlockType1::BlockType1(int x, int y) : Block(x, y) {
	cells = &cell_0;
}

BlockType2::BlockType2(int x, int y) : Block(x, y) {
	cells = &cell_0;
}

BlockType3::BlockType3(int x, int y) : Block(x, y) {
	cells = &cell_0;
}

BlockType4::BlockType4(int x, int y) : Block(x, y) {
	cells = &cell_0;
}
BlockType5::BlockType5(int x, int y) : Block(x, y) {
	cells = &cell_0;
}
BlockType6::BlockType6(int x, int y) : Block(x, y) {
	cells = &cell_0;
}
BlockType7::BlockType7(int x, int y) : Block(x, y) {
	cells = &cell_0;
}

// take the reference of cells pointer to change what it points to
void rotate_helper(int angle, const cell_t *&cells, const cell_t &cell_0,
	const cell_t &cell_90, const cell_t &cell_180, const cell_t &cell_270) {
	switch (angle)
	{
	case 0:
		cells = &cell_0;
		break;
	case 90:
		cells = &cell_90;
		break;
	case 180:
		cells = &cell_180;
		break;
	case 270:
		cells = &cell_270;
		break;
	default:
		throw "invalid angle";
		break;
	}
}

void rotate_helper(int angle, const cell_t *&cells, const cell_t &cell_0, const cell_t &cell_90) {
	if (angle == 0 || angle == 180) {
		cells = &cell_0;
	}
	else {
		cells = &cell_90;
	}
}

void BlockType1::rotateCw() {
	angle = (angle + 90) % 360;
	rotate_helper(angle, cells, cell_0, cell_90);
}

void BlockType1::rotateCcw() {
	angle = (angle + 270) % 360;
	rotate_helper(angle, cells, cell_0, cell_90);
}

void BlockType3::rotateCw() {
	angle = (angle + 90) % 360;
	rotate_helper(angle, cells, cell_0, cell_90);
}

void BlockType3::rotateCcw() {
	angle = (angle + 270) % 360;
	rotate_helper(angle, cells, cell_0, cell_90);
}

void BlockType4::rotateCw() {
	angle = (angle + 90) % 360;
	rotate_helper(angle, cells, cell_0, cell_90);
}

void BlockType4::rotateCcw() {
	angle = (angle + 270) % 360;
	rotate_helper(angle, cells, cell_0, cell_90);
}

void BlockType2::rotateCw() {
	angle = (angle + 90) % 360;
	rotate_helper(angle, cells, cell_0, cell_90, cell_180, cell_270);
}

void BlockType2::rotateCcw() {
	angle = (angle + 270) % 360;
	rotate_helper(angle, cells, cell_0, cell_90, cell_180, cell_270);
}

void BlockType5::rotateCw() {
	angle = (angle + 90) % 360;
	rotate_helper(angle, cells, cell_0, cell_90, cell_180, cell_270);
}

void BlockType5::rotateCcw() {
	angle = (angle + 270) % 360;
	rotate_helper(angle, cells, cell_0, cell_90, cell_180, cell_270);
}

void BlockType6::rotateCw() {
	angle = (angle + 90) % 360;
	rotate_helper(angle, cells, cell_0, cell_90, cell_180, cell_270);
}

void BlockType6::rotateCcw() {
	angle = (angle + 270) % 360;
	rotate_helper(angle, cells, cell_0, cell_90, cell_180, cell_270);
}

void BlockType7::rotateCw() {
}

void BlockType7::rotateCcw() {
}




