#pragma once
#include <array>
#include <memory>

using namespace std;

typedef array<array<int, 2>, 4> cell_t;

class Block {
public:
	Block();
	Block(int x, int y);
	void setPos(int x, int y);
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	array<int, 2> (&getPos() const);
	int getX() const;
	int getY() const;
	unique_ptr<cell_t>getCells() const;
	virtual void rotateCw() = 0;
	virtual void rotateCcw() = 0;
	
protected:
	int angle;
	int boundX, boundY;
	array<int, 2> pos;
	const cell_t *cells;
};

// the long strip
class BlockType1 : public Block {
public:
	BlockType1(int x, int y);
	void rotateCw();
	void rotateCcw();
private:
	static const cell_t cell_0;
	static const cell_t cell_90;
};

// T shape block
class BlockType2 : public Block {
public:
	BlockType2(int x, int y);
	void rotateCw();
	void rotateCcw();
private:
	static const cell_t cell_0;
	static const cell_t cell_90;
	static const cell_t cell_180;
	static const cell_t cell_270;
};

// inverse Z shaped block
class BlockType3 : public Block {
public:
	BlockType3(int x, int y);
	void rotateCw();
	void rotateCcw();
private:
	static const cell_t cell_0;
	static const cell_t cell_90;
};

// Z shaped block
class BlockType4 : public Block {
public:
	BlockType4(int x, int y);
	void rotateCw();
	void rotateCcw();
private:
	static const cell_t cell_0;
	static const cell_t cell_90;
};

// inverse L shaped block
class BlockType5 : public Block {
public:
	BlockType5(int x, int y);
	void rotateCw();
	void rotateCcw();
private:
	static const cell_t cell_0;
	static const cell_t cell_90;
	static const cell_t cell_180;
	static const cell_t cell_270;
};

// L shaped block
class BlockType6 : public Block {
public:
	BlockType6(int x, int y);
	void rotateCw();
	void rotateCcw();
private:
	static const cell_t cell_0;
	static const cell_t cell_90;
	static const cell_t cell_180;
	static const cell_t cell_270;
};

// square block
class BlockType7 : public Block {
public:
	BlockType7(int x, int y);
	void rotateCw();
	void rotateCcw();
private:
	static const cell_t cell_0;
};
