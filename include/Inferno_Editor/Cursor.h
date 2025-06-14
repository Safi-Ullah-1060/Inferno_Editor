#ifndef CURSOR_H
#define CURSOR_H

#include <iostream>
using namespace std;

class Cursor
{
private:
    int row, col;

public:
    Cursor();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    int getRow() const;
    int getCol() const;
    void setPos(int, int);
};

#endif
