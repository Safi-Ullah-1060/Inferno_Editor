#include "../include/Inferno_Editor/Editor.h"

Editor::Editor() : md{new Normal_Mode(this)}, running{0}, in_visual_sel{0}, isSaved{0}
{
	sel_start.setPos(-1, -1);
}
TextBuffer &Editor::getBuffer()
{
	return buffer;
}
Cursor *Editor::getCursor()
{
	return &csr;
}
Cursor *Editor::getSelStart()
{
	return &sel_start;
}
void Editor::changeMode(Mode *m)
{
	clearCurrMode();
	if (m)
		md = m;
	m = nullptr;
}
void Editor::clearCurrMode()
{
	if (md != nullptr)
	{
		md->editor = nullptr;
		delete md;
		md = nullptr;
	}
}
void Editor::run()
{
	running = 1;
	int c = '\0'; // null to ascii
	while (running)
	{
		rndr.draw(buffer, csr, in_visual_sel, sel_start, md->getName());
		c = getch();
		md->handleInput(c);
	}
}
void Editor::askToSave()
{
	move(0, 0);
	char c;
	printw("Would you like to save this file?\n");
	printw("Yes(Y/y) or No(N/n): ");
	c = getch();
	if (c == 'Y' || c == 'y')
	{
		MyStr filename(20, '\0'), temp(".txt ");
		printw("\nEnter the name of file: ");
		while (c != '\n')
		{
			c = getch();
			if (c >= 32 && c <= 126)
			{
				addch(c);
				refresh();
				filename.insert_at(filename.get_len(), c);
			}
		}
		filename += temp;
		char *fileName = new char[filename.get_len()];
		filename.get(fileName, filename.get_len());
		ofstream write(fileName);
		char *line;
		for (int i = 0; i < getBuffer().getLen(); i++)
		{
			for (int j = 0; j < getBuffer().buffer[i].get_len(); j++)
				write << getBuffer().getLines()[i][j];
			write << std::endl;
		}
	}
	else if (c == 'N' || c == 'n')
	{
	}
}
void Editor::exit()
{
	running = 0;
	clear();
	askToSave();
}
void Editor::startVisualSel()
{
	sel_start = csr;
	in_visual_sel = 1;
}
bool Editor::isInVisualSel()
{
	return in_visual_sel;
}
void Editor::endVisualSel()
{
	in_visual_sel = 0;
	sel_start.setPos(-1, -1);
}
Editor::~Editor()
{
	clearCurrMode();
}