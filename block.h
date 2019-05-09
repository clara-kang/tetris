#pragma once
#include <array>
#include <memory>

using namespace std;

class Block {
public:
	Block();
	Block(int x, int y, int boundX, int boundY);
	void setPos(int x, int y);
	void moveLeft();
	void moveRight();
	void moveDown();
	array<int, 2> (&getPos() const);
	unique_ptr<array<array<int, 2>, 4 >>getCells() const;
	virtual void rotate() = 0;
	
protected:
	int angle;
	int boundX, boundY;
	array<int, 2> pos;
	array<array<int, 2>, 4> cells;

private:
	bool boundCheck(array<int, 2> pot_pos);
};


class BlockType1 : public Block {
public:
	BlockType1(int x, int y, int boundX, int boundY);
	void rotate();
private:
	static const array<array<int, 2>, 4> cell_0;
	static const array<array<int, 2>, 4> cell_90;
};
