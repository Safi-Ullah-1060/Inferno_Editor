#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#ifdef _WIN32

#include <conio.h>
bool OS = 1;

#else

bool OS = 0;
#include <termios.h>
#include <unistd.h>

#endif

char getch()
{
    char buf = 0;
    termios old = {};
    tcgetattr(STDIN_FILENO, &old);
    termios new_ = old;
    // new_.c_lflag &= ~(ICANON);
    // tcsetattr(STDIN_FILENO, TCSANOW, &new_);
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    read(STDIN_FILENO, &buf, 1);
    return buf;
}

void navigate(char nav)
{
    switch (nav)
    {
    case 'A':
        // move up
        break;

    case 'B':
        // move down
        break;

    case 'C':
        // move right
        break;

    case 'D':
        // move left
        break;

    default:
        break;
    }
}

class text
{
public:
    string strbuffer;
    void takeinput()
    {
        char a = 0;
        while (1)
        {
#ifdef _WIN32
            a = _getcv();
            if (a == 27)
                break;
#else
            a = getch();

            if (a == 27)
            {
                char next = getch();
                if (next == '[')
                {
                    navigate(getch());
                    continue;
                }
                else
                    break;
            }

            strbuffer += a;
            cout << a;
#endif
        }
    }
    void savefile()
    {
        string filename = "Untitled.txt";
        cout << filename << endl;
        takeinput();
        if (filename == "Untitled.txt")
        {
            cout << "Enter filename (with extension): ";
            cin >> filename;
        }
        ofstream write(filename);
        write << strbuffer;
    }
};

int main()
{
    text content;
    content.savefile();
    return 0;
}