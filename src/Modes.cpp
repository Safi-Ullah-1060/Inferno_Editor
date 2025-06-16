#include "../include/Inferno_Editor/Modes.h"
#include "../include/Inferno_Editor/Editor.h"

// Abstract class Mode
Mode::Mode() {}
Mode::Mode(Editor *e) : editor{e} {}
Mode::~Mode()
{
	editor = nullptr;
}

// Insert Mode
Insert_Mode::Insert_Mode(Editor *e)
{
	editor = e;
}
void Insert_Mode::handleInput(int a)
{
	Cursor *csr = editor->getCursor();
	int crRow = csr->getRow();
	int crCol = csr->getCol();
	if (a == 27) // ESC
		editor->changeMode(new Normal_Mode(editor));
	else if (a == '\n') // RETURN Pressted
	{
		editor->getBuffer().insertNewLine(csr->getRow(), csr->getCol());
		csr->setPos(csr->getRow() + 1, 0);
		editor->isSaved = 0;
	}
	else if (a >= 32 and a <= 126) // PRINTABLE CHARS
	{
		if (editor->getBuffer().getLen() == editor->getBuffer().getCap())
		{
			editor->getBuffer().regrowBuffer();
		}
		editor->getBuffer().insert(csr->getRow(), csr->getCol(), a);
		if (crCol < editor->getBuffer().buffer[crRow].get_len())
			csr->moveRight();
		editor->isSaved = 0;
	}
	else if (a == KEY_LEFT) // left arrow pressed
		csr->moveLeft();
	else if (a == KEY_RIGHT) // right arrow pressed
	{
		if (crCol < editor->getBuffer().buffer[crRow].get_len())
			csr->moveRight();
	}
	else if (a == KEY_UP) // up arrow pressed
	{
		if (crCol <= editor->getBuffer().buffer[crRow - 1].get_len())
			csr->moveUp();
		else
			csr->setPos(crRow - 1, editor->getBuffer().buffer[crRow - 1].get_len());
	}
	else if (a == KEY_DOWN) // down arrow pressed
	{
		if (crRow + 1 < editor->getBuffer().getLen())
		{
			if (crCol <= editor->getBuffer().buffer[crRow + 1].get_len())
				csr->moveDown();
			else
				csr->setPos(crRow + 1, editor->getBuffer().buffer[crRow + 1].get_len());
		}
	}
	else if (a == KEY_BACKSPACE) // BACKSPACE
	{
		int row = csr->getRow();
		int col = editor->getBuffer().buffer[row - 1].get_len();
		editor->getBuffer().del(row, csr->getCol());
		if (csr->getCol() != 0)
			csr->moveLeft();
		else if (row > 0)
			csr->setPos(row - 1, col);
		editor->isSaved = 0;
	}
}
MyStr Insert_Mode::getName()
{
	return "--INSERT--";
}
Insert_Mode::~Insert_Mode() {};

// Normal Mode
Normal_Mode::Normal_Mode(Editor *e)
{
	editor = e;
	if (editor->isInVisualSel() == 1)
	{
		editor->endVisualSel();
	}
}
void Normal_Mode::handleInput(int a)
{
	Cursor *csr = editor->getCursor();
	int crRow = csr->getRow();
	int crCol = csr->getCol();
	if (a == 118) // v Pressed
	{
		editor->startVisualSel();
		editor->changeMode(new Visual_Mode(editor));
	}
	else if (a == 105) // i Pressed
		editor->changeMode(new Insert_Mode(editor));
	else if (a == 120) // x Pressed
	{
		int row = csr->getRow();
		int col = editor->getBuffer().buffer[row - 1].get_len();
		editor->getBuffer().del(row, csr->getCol());
		if (csr->getCol() > 0)
			csr->moveLeft();
		else if (row > 0)
			csr->setPos(row - 1, col);
		editor->isSaved = 0;
	}
	else if (a == 'q') // q Pressed
		editor->exit();
	else if (a == 's') // s pressed
		editor->askToSave();
	else if (a == 'o') // o pressed
		editor->open();
	else if (a == 'd') // d Pressed
	{
		a = getch();
		if (a == 'd') // d pressed again
		{
			editor->getBuffer().deleteLine(crRow); // remove current line
			if (crRow == 0)
				csr->setPos(0, 0);
			else if (crRow == editor->getBuffer().getLen())
				csr->setPos(crRow - 1, 0);
			else
				csr->setPos(crRow, 0);
			editor->isSaved = 0;
		}
		else
		{
			delete csr;
			handleInput(a);
		}
	}
	else if (a == 'h') // left arrow pressed
		csr->moveLeft();
	else if (a == 'l') // right arrow pressed
	{
		if (crCol < editor->getBuffer().buffer[crRow].get_len())
			csr->moveRight();
	}
	else if (a == 'k') // up arrow pressed
	{
		if (crCol <= editor->getBuffer().buffer[crRow - 1].get_len())
			csr->moveUp();
		else
			csr->setPos(crRow - 1, editor->getBuffer().buffer[crRow - 1].get_len());
	}
	else if (a == 'j') // down arrow pressed
	{
		if (crRow + 1 < editor->getBuffer().getLen())
		{
			if (crCol <= editor->getBuffer().buffer[crRow + 1].get_len())
				csr->moveDown();
			else
				csr->setPos(crRow + 1, editor->getBuffer().buffer[crRow + 1].get_len());
		}
	}
}
MyStr Normal_Mode::getName()
{
	return "--NORMAL--";
}
Normal_Mode::~Normal_Mode() {};

// Visual Mode
Visual_Mode::Visual_Mode(Editor *e)
{
	editor = e;
}
void Visual_Mode::handleInput(int a)
{
	Cursor *csr = editor->getCursor();
	Cursor *old_csr = editor->getSelStart();
	int crRow = csr->getRow();
	int crCol = csr->getCol();
	if (a == 27) // ESC Pressed
		editor->changeMode(new Normal_Mode(editor));
	else if (a == 120) // x Pressed
	{
		int endRow = csr->getRow();
		int endCol = csr->getCol();
		int startRow = old_csr->getRow();
		int startCol = old_csr->getCol();
		if (endCol < editor->getBuffer().buffer[startRow].get_len())
		{
			if (startRow > endRow || (startRow == endRow && startCol > endCol))
			{
				std::swap(startRow, endRow);
				std::swap(startCol, endCol);
			}
			for (int i = startRow; i <= endRow; i++)
			{
				for (int j = startCol; j <= endCol; j++)
					editor->getBuffer().del(i, startCol + 1);
			}
			csr->setPos(std::min(startRow, endRow), std::min(startCol, endCol));
			old_csr->setPos(csr->getRow(), csr->getCol());
		}
		editor->isSaved = 0;
	}
	else if (a == KEY_LEFT)
	{
		csr->moveLeft();
	}
	else if (a == KEY_RIGHT)
	{
		if (crCol < editor->getBuffer().buffer[crRow].get_len())
			csr->moveRight();
	}
	else if (a == KEY_UP)
	{
		if (crCol <= editor->getBuffer().buffer[crRow - 1].get_len())
			csr->moveUp();
		else
			csr->setPos(crRow - 1, editor->getBuffer().buffer[crRow - 1].get_len());
	}
	else if (a == KEY_DOWN)
	{
		if (crRow + 1 < editor->getBuffer().getLen())
		{
			if (crCol <= editor->getBuffer().buffer[crRow + 1].get_len())
				csr->moveDown();
			else
				csr->setPos(crRow + 1, editor->getBuffer().buffer[crRow + 1].get_len());
		}
	}
}
MyStr Visual_Mode::getName()
{
	return "--VISUAL--";
}
Visual_Mode::~Visual_Mode() {};
