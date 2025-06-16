#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <iostream>
#include "./MyStr.h"
using namespace std;

class TextBuffer
{
protected:
    int bfrLen;
    int bfrCap;

public:
    MyStr *buffer;
    TextBuffer();
    TextBuffer(const TextBuffer &);
    TextBuffer &operator=(const TextBuffer &);
    void insert(int, int, char);
    void del(int, int);
    void deleteLine(int);
    void insertNewLine(int, int);
    void regrowBuffer();
    int getCap();
    int getLen();
    void setBuffer(MyStr *, int);
    MyStr *getLines();
    ~TextBuffer();
};

#endif
