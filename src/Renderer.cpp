#include "../Headers/Renderer.h"

Renderer::Renderer()
{
    initscr();
    noecho();
    curs_set(1);
    keypad(stdscr, 1);
}

void Renderer::draw(TextBuffer &txtbfr, Cursor &csr, const MyStr &currMode)
{
    clear();
    MyStr *currBfr = txtbfr.getLines();
    int bfrLen = txtbfr.getLines()->get_len();
    for (int i = 0; i < currMode.get_len(); i++)
        printw("%c", currMode[i]);
    printw("\n");
    for (int i = 0; i < bfrLen; i++)
    {
        printf("%4d  ", i + 1);
        for (int j = 0; j <= currBfr[i].get_len(); j++)
        {
            if (i == csr.getRow() and j == csr.getCol())
            {
                attron(A_REVERSE);
                if (j < currBfr[i].get_len())
                    printw("%c", currBfr[i][j]);
                else
                    printw(" ");

                attroff(A_REVERSE);
            }
            else if (j < currBfr[i].get_len())
                printw("%c", currBfr[i][j]);
        }
        printw("\n");
    }
    refresh();
}

Renderer::~Renderer()
{
    endwin();
}
