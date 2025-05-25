#include "../Headers/TextBuffer.h"

TextBuffer::TextBuffer() : buffer{new MyStr[100]}
{
    for (int i = 0; i < 100; i++)
    {
        buffer[i] = MyStr(100, '\0');
    }
};

void TextBuffer::insert(int row, int col, char c)
{
    buffer[row].insert_at(col, c);
};

MyStr *TextBuffer::getLines()
{
    return buffer;
}
