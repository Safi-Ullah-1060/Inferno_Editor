#ifndef TEXTBUFFER
#define TEXTBUFFER

#include <iostream>
#include "../Headers/MyStr.h"
using namespace std;

class TextBuffer
{
private:
    MyStr *buffer;

public:
    TextBuffer();
    void insert(int, int, char);
    MyStr *getLines();
};

#endif
