#ifndef MODES_H
#define MODES_H

#include "./MyStr.h"
class Editor;

class Mode
{
public:
    Editor *editor;
    Mode();
    Mode(Editor *);
    virtual ~Mode() = 0;
    virtual void handleInput(int) = 0;
    virtual MyStr getName() = 0;
};

class Normal_Mode : public Mode
{
public:
    Normal_Mode(Editor *);
    void handleInput(int);
    MyStr getName();
    ~Normal_Mode();
};

class Insert_Mode : public Mode
{
public:
    Insert_Mode(Editor *);
    void handleInput(int);
    MyStr getName();
    ~Insert_Mode();
};

class Visual_Mode : public Mode
{
public:
    Visual_Mode(Editor *);
    void handleInput(int);
    MyStr getName();
    ~Visual_Mode();
};

#endif