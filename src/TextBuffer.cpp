#include "../include/Inferno_Editor/TextBuffer.h"

TextBuffer::TextBuffer() : bfrCap{10}, bfrLen{1}, buffer{new MyStr[bfrCap]}
{
	try
	{
		for (int i = 0; i < bfrCap; i++)
			buffer[i] = MyStr(50, '\0');
	}
	catch (const std::exception &a)
	{
		delete[] buffer;
		throw;
	}
};

void TextBuffer::setBuffer(MyStr *lines, int len)
{
	bfrLen = 0;
	for (int i = 0; i < len; i++)
	{
		if(bfrLen == bfrCap)
			regrowBuffer();
		buffer[i] = lines[i];
		bfrLen++;
	}
}

TextBuffer::TextBuffer(const TextBuffer &tb) : bfrLen{0}, bfrCap{tb.bfrCap}, buffer{new MyStr[bfrCap]}
{
	for (int i = 0; i < bfrCap; i++)
		buffer[i] = tb.buffer[i];
}

int TextBuffer::getCap()
{
	return bfrCap;
}

int TextBuffer::getLen()
{
	return bfrLen;
}

TextBuffer &TextBuffer::operator=(const TextBuffer &tb)
{
	if (this != &tb)
	{
		if (buffer != nullptr)
			delete[] buffer;
		bfrCap = tb.bfrCap;
		bfrLen = tb.bfrLen;
		buffer = new MyStr[bfrCap];
		for (int i = 0; i < bfrCap; i++)
			buffer[i] = tb.buffer[i];
	}
	return *this;
}

void TextBuffer::insert(int row, int col, char c)
{
	if (c == '\n')
	{
		insertNewLine(row, col);
	}
	buffer[row].insert_at(col, c);
};

void TextBuffer::del(int row, int col)
{
	if (col != 0)
		buffer[row].remove_at(col - 1);
	else if (row > 0)
	{
		buffer[row - 1] += buffer[row];
		buffer[row - 1].insert_at(buffer[row - 1].get_len(), 0);
		buffer[row].clear();
		bfrLen--;
	}
}

void TextBuffer::deleteLine(int row)
{
	buffer[row].clear();
	for (int i = row; i < bfrLen - 1; i++)
		buffer[i] = buffer[i + 1];
	buffer[bfrLen--].clear();
	if (bfrLen == 0)
	{
		bfrLen++;
	}
}

void TextBuffer::insertNewLine(int row, int col)
{
	if (bfrLen == bfrCap)
		regrowBuffer();
	for (int i = bfrLen; i > row + 1; i--)
		buffer[i] = buffer[i - 1];
	buffer[row + 1].clear();
	if (col < buffer[row].get_len())
	{
		MyStr *splits = buffer[row].split_at(col);
		buffer[row] = splits[0];
		buffer[row + 1] = splits[1];
		delete[] splits;
	}
	bfrLen++;
}

void TextBuffer::regrowBuffer()
{
	MyStr *tempBfr = new MyStr[bfrCap * 2]{};
	for (int i = 0; i < bfrCap; i++)
		tempBfr[i] = buffer[i];
	for (int i = bfrCap; i < bfrCap * 2; i++)
		tempBfr[i] = MyStr(50, '\0');
	delete[] buffer;
	buffer = tempBfr;
	bfrCap *= 2;
}

MyStr *TextBuffer::getLines()
{
	return buffer;
}
TextBuffer::~TextBuffer()
{
	if (buffer)
	{
		delete[] buffer;
		buffer = nullptr;
	}
}
