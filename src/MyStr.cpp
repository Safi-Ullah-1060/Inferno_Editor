#include "../include/Inferno_Editor/MyStr.h"

MyStr::MyStr() : len{0}, cap{1}, Cs{nullptr} {};
MyStr::MyStr(const MyStr &b) : len{0}, cap{0}, Cs{nullptr}
{
	if (b.Cs != nullptr && b.len > 0)
	{
		len = b.len, cap = b.cap;
		Cs = new char[cap]{};
		for (int i = 0; i < len; i++)
			Cs[i] = b.Cs[i];
	}
}
MyStr::MyStr(const char *c) : len{0}, cap{1}
{
	if (c == nullptr)
	{
		cap = 1;
		Cs = new char[cap]{};
		return;
	}
	while (c[len] != '\0')
		len++;
	cap = len * 2 + 1;
	Cs = new char[cap]{};
	for (int i = 0; i < len; i++)
		Cs[i] = c[i];
}
MyStr::MyStr(int a, char c) : len{0}, cap{a * 2 + 1}
{
	Cs = new (std::nothrow) char[cap + 1]{};
	if (!Cs)
		throw std::runtime_error("Failed to allocate memory");
	for (int i = 0; i < len; i++)
		Cs[i] = c;
	Cs[len] = '\0';
}
MyStr::MyStr(int a) : len{0}, cap{0}, Cs{nullptr}
{
	*this = itos(a);
}
MyStr &MyStr::operator=(const MyStr &b)
{
	if (this == &b)
		return *this;
	if (Cs != nullptr)
		delete[] Cs;
	len = b.len, cap = b.cap;
	Cs = new char[cap]{};
	if (b.Cs != nullptr && b.len > 0)
		for (int i = 0; i < len; i++)
			Cs[i] = b.Cs[i];
	Cs[len] = '\0';
	return *this;
}
MyStr MyStr::operator+(const MyStr &b)
{
	MyStr temp;
	temp.len = len + b.len;
	temp.cap = temp.len * 2 + 1;
	temp.Cs = new char[temp.cap]{};
	for (int i = 0; i < len; i++)
		temp.Cs[i] = Cs[i];
	for (int i = 0; i < b.len; i++)
		temp.Cs[i + len] = b.Cs[i];
	return temp;
}
MyStr &MyStr::operator+=(const MyStr &b)
{
	MyStr temp;
	temp.len = len + b.len, temp.cap = temp.len * 2 + 1;
	temp.Cs = new char[cap]{};
	for (int i = 0; i < len; i++)
		temp.Cs[i] = Cs[i];
	for (int i = 0; i < b.len; i++)
		temp.Cs[i + len] = b.Cs[i];
	*this = temp;
	return *this;
}

void MyStr::print()
{
	for (int i = 0; i < len; i++)
		cout << Cs[i];
}
void MyStr::replace_first(char c)
{
	if (len > 0)
		Cs[0] = c;
}
int MyStr::stoi()
{
	int n = 0, m = 1;
	for (int i = len - 1; i >= 0; i--)
	{
		n += (Cs[i] - '0') * m;
		m *= 10;
	}
	return n;
}
MyStr MyStr::itos(int a)
{
	MyStr temp;
	int v = a;
	if (a == 0)
	{
		temp.len = 1, temp.cap = 3;
		temp.Cs = new char[temp.cap]{};
		temp.Cs[0] = '0';
		temp.Cs[1] = '\0';
		return temp;
	}
	do
	{
		v /= 10, temp.len++;
	} while (v > 0);
	temp.cap = temp.len * 2 + 1;
	temp.Cs = new char[++temp.cap]{};
	for (int i = temp.len - 1; i >= 0; i--)
	{
		temp.Cs[i] = '0' + (a % 10);
		a /= 10;
	}
	return temp;
}
MyStr MyStr::trim()
{
	if (len == 0)
		return MyStr();
	int end{len}, beg{};
	for (int i = 0; Cs[i] == '\n' || Cs[i] == '\t' || Cs[i] == ' '; i++)
		beg++;
	for (int i = len - 1; Cs[i] == '\n' || Cs[i] == '\t' || Cs[i] == ' '; i--)
		end--;
	MyStr temp(end, 'a');
	for (int i = 0; i < temp.len; i++)
		temp.Cs[i] = Cs[beg + i];
	return temp;
}
bool MyStr::is_equal(const MyStr &a)
{
	if (len != a.len)
		return 0;
	for (int i = 0; Cs[i] != '\0' && a.Cs[i] != '\0'; i++)
		if (Cs[i] != a.Cs[i])
			return 0;
	return 1;
}
bool MyStr::is_less(const MyStr &a)
{
	for (int i = 0; Cs[i] != '\0' && a.Cs[i] != '\0'; i++)
		if (Cs[i] > a.Cs[i])
			return 0;
		else if (Cs[i] == a.Cs[i])
		{
		}
	return 1;
}
bool MyStr::is_greater(const MyStr &a)
{
	for (int i = 0; Cs[i] != '\0' && a.Cs[i] != '\0'; i++)
		if (Cs[i] < a.Cs[i])
			return 0;
		else if (Cs[i] == a.Cs[i])
		{
		}
	return 1;
}
MyStr *MyStr::Tokenize(const char *breaker, int &count)
{
	count = 0;
	int i = 0;
	bool is_delimiter;
	MyStr *spS = new MyStr[len];
	while (i <= len)
	{
		if (spS[count].len > 1 || count >= 0)
		{
			spS[count].Cs = new char[len]{};
			spS[count].cap = cap;
			spS[count].len = 0;
		}
		for (int j = 0; i < len; i++, j++)
		{
			is_delimiter = is_delim(Cs[i], breaker);
			if (!is_delimiter)
			{
				spS[count].Cs[j] = Cs[i];
				spS[count].len++;
			}
			else
			{
				if (spS[count].len > 0)
				{
					count++;
					spS[count].Cs = new char[len]{};
					spS[count].cap = cap;
					spS[count].len = 0;
				}
				j = -1;
			}
		}
		i++;
		if (spS[count].len > 0)
			count++;
	}
	MyStr *result = new MyStr[count];
	for (int i = 0; i < count; i++)
	{
		result[i] = spS[i];
		delete[] spS[i].Cs;
	}
	delete[] spS;
	return result;
}
MyStr *MyStr::split(char breaker, int &count)
{
	int i = 0;
	MyStr *spS = new MyStr[len];
	while (i <= len)
	{
		if (spS[count].len > 1 || count >= 0)
		{
			spS[count].Cs = new char[len]{};
			spS[count].cap = cap;
			spS[count].len = 1;
		}
		for (int j = 0; Cs[i] != breaker && i < len; i++, j++)
		{
			spS[count].Cs[j] = Cs[i];
			spS[count].len++;
		}
		i++;
		if (spS[count].len > 1)
			count++;
	}
	MyStr *result = new MyStr[count];
	for (int i = 0; i < count; i++)
	{
		result[i] = spS[i];
		delete[] spS[i].Cs;
	}
	delete[] spS;
	return result;
}
MyStr *MyStr::split_at(int index)
{
	MyStr *split_Str = new MyStr[2]{};
	split_Str[0] = MyStr(index, '\0');
	split_Str[1] = MyStr(len - index, '\0');
	for (int i = 0; i < index; i++)
	{
		split_Str[0][i] = Cs[i];
		split_Str[0].len++;
	}

	for (int i = index; i < len; i++)
	{
		split_Str[1][i - index] = Cs[i];
		split_Str[1].len++;
	}
	return split_Str;
}
bool MyStr::is_delim(char tested, const char *breaker)
{
	for (int i = 0; breaker[i] != '\0'; i++)
		if (tested == breaker[i])
			return 1;
	return 0;
}
int *MyStr::All_sub_str(const char *target, int &count)
{
	bool found = 0;
	int *indexes = new int[len], n = 0;
	for (int i = 0; i < len; i++)
		indexes[i] = -1;
	for (int i = 0, k = 0; i < len; i++)
	{
		found = 0;
		for (int j = 0; target[j] != '\0'; j++)
		{
			if (Cs[i] == target[j])
			{
				if (!found)
					n = i;
				i++;
				found = 1;
			}
			else
			{
				found = 0;
				break;
			}
		}
		if (found)
		{
			indexes[k++] = n;
			count++;
		}
	}
	return indexes;
}
int MyStr::find_first(char a)
{
	for (int i = 0; i < len; i++)
		if (Cs[i] == a)
			return i;
	return -1;
}
int MyStr::find_last(char a)
{
	for (int i = len - 1; i >= 0; i--)
		if (Cs[i] == a)
			return i;
	return -1;
}
int *MyStr::find_all(char a, int &count)
{
	int *indexes = new int[len], j = 0;
	for (int i = 0; i < len; i++)
		indexes[i] = -1;
	for (int i = 0; i < len; i++)
	{
		if (Cs[i] == a)
			indexes[j++] = i;
	}
	count = j;
	if (count == 0)
	{
		delete[] indexes;
		return nullptr;
	}
	return indexes;
}
void MyStr::remove_at(int i)
{
	for (int a = i; a < len - 1; a++)
		Cs[a] = Cs[a + 1];
	Cs[len - 1] = ' ';
	if (len > 0)
		len--;
}
void MyStr::insert_at(int i, char c)
{
	if (i <= len)
	{
		if (cap - len == 0)
			regrow();
		for (int a = len; a >= i; a--)
			Cs[a] = Cs[a - 1];
		Cs[i] = c;
		len++;
	}
}
void MyStr::insert_at(int i, const MyStr Sub)
{
	MyStr res(*this + Sub);
	for (int k = 0; k < i; k++)
		res.Cs[k] = Cs[k];
	for (int k = i; k < len; k++)
		res.Cs[k + Sub.len] = Cs[k];
	for (int k = 0; k < Sub.len; k++)
		res.Cs[k + i] = Sub.Cs[k];
	*this = res;
}
void MyStr::rem_first(char c)
{
	int k = find_first(c);
	if (k != -1)
	{
		for (int i = k; i < len - 1; i++)
			Cs[i] = Cs[i + 1];
		len--;
	}
}
void MyStr::rem_last(char c)
{
	int k = find_last(c);
	if (k != -1)
	{
		for (int i = k; i < len - 1; i++)
			Cs[i] = Cs[i + 1];
		len--;
	}
}
void MyStr::rem_all(char c)
{
	int x = 0;
	int *k = nullptr;
	k = find_all(c, x);
	if (k == nullptr || x == 0)
	{
		if (k != nullptr)
			delete[] k;
		return;
	}
	else
	{
		for (int i = x - 1; i >= 0; i--)
		{
			for (int j = k[i]; j < len - 1; j++)
				Cs[j] = Cs[j + 1];
			Cs[len] = '\0';
			len--;
		}
		delete[] k;
	}
}
void MyStr::clear()
{
	for (int i = 0; i < len; i++)
		Cs[i] = '\0';
	len = 0;
}
void MyStr::ToUpper()
{
	for (int i = 0; i < len; i++)
		if ((Cs[i] > 64 && Cs[i] < 91) || (Cs[i] > 96 && Cs[i] < 123))
			if (!(Cs[i] > 64 && Cs[i] < 91))
				Cs[i] -= 32;
}
void MyStr::ToLower()
{
	for (int i = 0; i < len; i++)
		if ((Cs[i] > 64 && Cs[i] < 91) || (Cs[i] > 96 && Cs[i] < 123))
			if (Cs[i] > 64 && Cs[i] < 91)
				Cs[i] += 32;
}
char MyStr::operator[](int i) const
{
	if (i < 0 || i > len - 1)
		throw std::runtime_error("Out of bounds\n");
	return Cs[i];
}
char &MyStr::operator[](int i)
{
	if (i < 0 || i > len)
		throw std::runtime_error("Out of bounds\n");
	return Cs[i];
}
void MyStr::regrow()
{
	MyStr temp(cap, '\0'); // create temp of capacity = cap*2+1 with all '\0' s
	for (int i = 0; i < len; i++)
		temp.Cs[i] = Cs[i];
	*this = temp;
}
ostream &operator<<(ostream &out, const MyStr &a)
{
	for (int i = 0; i < a.len; i++)
		out << a[i];
	return out;
}
istream &operator>>(istream &in, const MyStr &a)
{
	for (int i = 0; i < a.len; i++)
		in.getline(a.Cs, a.len);
	return in;
}

void MyStr::get(char *dest, int destSize) const
{
	int copyLen = (len < destSize - 1) ? len : destSize - 1;
	for (int i = 0; i < copyLen; i++)
	{
		dest[i] = Cs[i];
	}
	dest[copyLen] = '\0';
}
int MyStr::get_len() const
{
	return len;
}

MyStr::~MyStr()
{
	if (Cs != nullptr)
		delete[] Cs;
	Cs = nullptr;
	len = 0, cap = 0;
}