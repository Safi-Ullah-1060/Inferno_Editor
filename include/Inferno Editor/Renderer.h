#ifndef RENDERER
#define RENDERER

#include <iostream>
#include <ncurses.h>
#include "./MyStr.h"
#include "./TextBuffer.h"
#include "./Cursor.h"

class Renderer
{
public:
    Renderer();
    void draw(TextBuffer &, Cursor &, const MyStr &);
    ~Renderer();
};

#endif
