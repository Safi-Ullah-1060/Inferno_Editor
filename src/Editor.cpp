#include "../include/Inferno_Editor/Editor.h"

Editor::Editor() : md{new Normal_Mode(this)}, running{0}, in_visual_sel{0}, isSaved{1}, filename{MyStr("Untitled.txt")}
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
		rndr.draw(buffer, csr, in_visual_sel, sel_start, md->getName(), filename, isSaved);
		c = getch();
		md->handleInput(c);
	}
}
void Editor::askToSave()
{
	clear();
	move(0, 0);
	char c = '\0', s = '\0';
	bool plzSave = 0;
	printw("Would you like to save this file?\n");
	printw("Yes(Y/y) or No(N/n): ");
	bool hasExt = 0;
	MyStr temp(".txt");
	MyStr unsaved("Untitled.txt");
	char *fileName = new char[filename.get_len() + 1];
	while (s != 'Y' && s != 'y' && s != 'N' && s != 'n')
	{
		s = getch();
		if (s == 'Y' || s == 'y')
		{
			plzSave = 1;
			if (filename.is_equal(unsaved))
			{
				filename.clear();
				printw("\nEnter the name of file: ");
				while (c != '\n')
				{
					c = getch();
					if (c >= 32 && c <= 126)
					{
						filename.insert_at(filename.get_len(), c);
						addch(c);
						refresh();
					}
				}
			}
			for (int i = filename.get_len() - 1; i >= 0; i--)
			{
				if (filename[i] == '.' || filename[i] == '/')
				{
					if (filename[i] == '.')
						hasExt = 1;
					break;
				}
			}
			if (!hasExt)
				filename += temp;
		}
		if (plzSave)
		{
			filename.get(fileName, filename.get_len() + 1);
			fileName[filename.get_len()] = '\0';
			ofstream write(fileName);
			char *line;
			for (int i = 0; i < getBuffer().getLen(); i++)
			{
				for (int j = 0; j < getBuffer().buffer[i].get_len(); j++)
					write << getBuffer().getLines()[i][j];
				write << '\n';
			}
			isSaved = 1;
		}
		else if (s == 'N' || s == 'n')
		{
		}
		delete[] fileName;
	}
}
void Editor::open()
{
	if (!isSaved)
		askToSave();
	clear();
	printw("Use relative path to locate the file you want to open\n : ");
	refresh();
	char c = '\0';
	filename.clear();
	while (c != '\n')
	{
		c = getch();
		if (c >= 32 && c <= 126 && c != '\n')
		{
			filename.insert_at(filename.get_len(), c);
			addch(c);
			refresh();
		}
	}
	char *file = new char[filename.get_len() + 1];
	filename.get(file, filename.get_len() + 1);
	file[filename.get_len()] = '\0';
	ifstream open(file);
	if (open)
	{
		int bfrCap = buffer.getCap();
		TextBuffer Data = buffer;
		buffer.setBuffer(nullptr, 0);
		int i = 0, j = 0;
		Data.getLines()[i].clear();
		char x = '\0';
		while (open.get(x) && !open.eof())
		{
			if (x == 10 || x == '\n')
			{
				i++;
				if (i >= Data.getCap())
					Data.regrowBuffer();
				Data.getLines()[i].clear();
				Data.getLines()[i - 1].insert_at(j, '\0');
				j = 0;
			}
			else
			{
				Data.getLines()[i].insert_at(j, x);
				j++;
			}
		}
		buffer.setBuffer(Data.getLines(), i + 1);
		isSaved = 1;
		move(0, 0);
	}
	else
	{
		clear();
		printw("File not found\nWould you like to try again (Y/y) yes, (N/n) no : ");
		refresh();
		char c = getch();
		bool tryAgain = 0;
		if (c == 'Y' || c == 'y')
		{
			tryAgain = 1;
			this->open();
		}
	}
	delete[] file;
}
void Editor::exit()
{
	running = 0;
	clear();
	if (!isSaved)
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