#include "../include/Inferno_Editor/Renderer.h"

Renderer::Renderer()
{
    initscr();
    start_color();
    curs_set(0);
    raw();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_YELLOW, 982, 631, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(1)); // changes color profile
    noecho();
    curs_set(1);
    keypad(stdscr, 1);

    prevCsrRow = -1;
    prevCsrCol = -1;
    prevBfrLen = 0;
    prevHadSel = 0;
}

void Renderer::drawFull(TextBuffer &txtbfr, Cursor &csr, const MyStr &currMode, bool has_sel, const Cursor &sel_start)
{
    MyStr *currBfr = txtbfr.getLines();
    int lineLen = txtbfr.getLen();

    drawMode(currMode);
    addch('\n');
    printw("Ln %d, Col %d\n", csr.getRow() + 1, csr.getCol() + 1);

    for (int i = 0; i < lineLen; i++)
    {
        drawLine(i, currBfr[i], csr.getRow(), csr.getCol(), has_sel, sel_start.getRow(), sel_start.getCol(), csr.getRow(), csr.getCol());
    }
    refresh();
}

void Renderer::drawMode(const MyStr &currMode)
{
    move(0, 0);
    clrtoeol(); // clears only the mode line
    int modeLen = currMode.get_len();
    for (int i = 0; i < modeLen; i++)
        addch(currMode[i]);
}

void Renderer::drawLine(int lineNum, const MyStr &line, int cursorRow, int cursorCol, bool hasSel, int selStartRow, int selStartCol, int selEndRow, int selEndCol)
{
    move(lineNum + 2, 0);
    clrtoeol();
    printw("%4d  ", lineNum + 1);
    for (int j = 0; j <= line.get_len(); j++)
    {
        bool should_highlight = 0;
        bool is_csr = (lineNum == cursorRow && j == cursorCol);
        if (hasSel)
            should_highlight = isCharInSelection(lineNum, j, selStartRow, selStartCol, selEndRow, selEndCol);
        if (should_highlight)
            attron(A_REVERSE);
        if (is_csr)
        {
            attron(A_REVERSE);
            attron(A_BOLD);
        }
        if (j < line.get_len())
            if (line[j] == '\0')
                addch(' ');
            else
                addch(line[j]);
        else if (is_csr)
            addch(' ');
        if (should_highlight)
            attroff(A_REVERSE);
        if (is_csr)
        {
            attroff(A_BOLD);
            attroff(A_REVERSE);
        }
    }
}

bool Renderer::isCharInSelection(int row, int col, int startRow, int startCol, int endRow, int endCol)
{
    // if going back, this swaps start and end
    if (startRow > endRow || (startRow == endRow && startCol > endCol))
    {
        std::swap(startRow, endRow);
        std::swap(startCol, endCol);
    }

    if (row < startRow || row > endRow)
        return false;
    if (row == startRow && row == endRow)
        return col >= startCol && col < endCol;
    if (row == startRow)
        return col >= startCol;
    if (row == endRow)
        return col < endCol;
    return true; // Middle rows have all chars selected
}

void Renderer::draw(TextBuffer &txtbfr, Cursor &csr, bool has_sel, const Cursor &sel_start, const MyStr &currMode)
{
    MyStr *currBfr = txtbfr.getLines();
    int lineLen = txtbfr.getLen();
    bool justExitedVisual = prevHadSel && !has_sel;
    if (justExitedVisual || prevBfrLen != lineLen || prevCsrRow == -1)
    {
        clear();
        drawFull(txtbfr, csr, currMode, has_sel, sel_start);
        prevBfrLen = lineLen;
        prevCsrRow = csr.getRow();
        prevCsrCol = csr.getCol();
        prevHadSel = has_sel;
        return;
    }
    drawMode(currMode);
    addch('\n');
    printw("Ln %d, Col %d\n", csr.getRow() + 1, csr.getCol() + 1);
    if (has_sel)
    {
        int minRow = std::min(prevCsrRow, csr.getRow());
        minRow = std::min(minRow, sel_start.getRow());
        int maxRow = std::max(prevCsrRow, csr.getRow());
        maxRow = std::max(maxRow, sel_start.getRow());

        // Redraw all lines that might be affected by selection
        for (int i = minRow; i <= maxRow && i < lineLen; i++)
            drawLine(i, currBfr[i], csr.getRow(), csr.getCol(), has_sel, sel_start.getRow(), sel_start.getCol(), csr.getRow(), csr.getCol());
    }
    if (!has_sel)
    {
        if (prevCsrRow != csr.getRow() || prevCsrCol != csr.getCol())
        {
            drawLine(prevCsrRow, currBfr[prevCsrRow], -1, -1, 0, 0, 0, 0, 0);
            drawLine(csr.getRow(), currBfr[csr.getRow()], csr.getRow(), csr.getCol(), 0, 0, 0, 0, 0);
            prevCsrRow = csr.getRow();
            prevCsrCol = csr.getCol();
        }
        else
        {
            drawLine(csr.getRow(), currBfr[csr.getRow()], csr.getRow(), csr.getCol(), 0, 0, 0, 0, 0);
        }
    }
    else
    {
        prevCsrRow = csr.getRow();
        prevCsrCol = csr.getCol();
    }
    prevHadSel = has_sel;
    refresh();
}

Renderer::~Renderer()
{
    endwin();
}
