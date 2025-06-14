#include "../include/Inferno_Editor/Cursor.h"

Cursor::Cursor() : row{0}, col{0} {};

int Cursor::getRow() const { return row; }

int Cursor::getCol() const { return col; }

void Cursor::setPos(int r, int c)
{
    row = r, col = c;
}

void Cursor::moveDown()
{
    row++;
}

void Cursor::moveUp()
{
    if (row > 0)
        row--;
}

void Cursor::moveRight()
{
    col++;
}

void Cursor::moveLeft()
{
        if (col > 0)
        col--;
}
