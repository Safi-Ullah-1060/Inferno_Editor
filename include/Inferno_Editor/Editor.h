#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include "./Cursor.h"
#include "./TextBuffer.h"
#include "./Renderer.h"
#include "./Modes.h"

class Editor
{
protected:
    TextBuffer buffer;
    Renderer rndr;
    Cursor csr;
    Cursor sel_start;
    bool in_visual_sel;
    Mode *md;
    bool running{0};
    bool isSaved;

public:
    Editor();
    Cursor *getCursor();
    Cursor *getSelStart();
    TextBuffer &getBuffer();
    void run();
    void exit();
    void changeMode(Mode *);
    void clearCurrMode();
    void startVisualSel();
    void endVisualSel();
    bool isInVisualSel();
    void askToSave();
    ~Editor();
};

#endif