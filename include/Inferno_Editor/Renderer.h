#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <ncurses.h>
#include "./MyStr.h"
#include "./TextBuffer.h"
#include "./Cursor.h"

class Renderer
{
private:
    int prevCsrRow;
    int prevCsrCol;
    int prevBfrLen;
    void drawFull(TextBuffer &, Cursor &, const MyStr &, bool, const Cursor &, const MyStr &,const bool&);
    void drawMode(const MyStr &);
    void drawLine(int, const MyStr &, int, int, bool, int, int, int, int);
    bool isCharInSelection(int, int, int, int, int, int);
    bool prevHadSel;

public:
    Renderer();
    void draw(TextBuffer &, Cursor &, bool, const Cursor &, const MyStr &, const MyStr &,const bool&);
    ~Renderer();
};

#endif
