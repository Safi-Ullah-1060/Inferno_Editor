#include <iostream>
using namespace std;

#include "./include/Inferno_Editor/MyStr.h"

int main()
{
    MyStr str1("Mataa-e-Baybaha");
    cout << str1 << endl;
    str1.rem_all('a');
    cout << str1;
    /*
     *   Used this to clear a warning regrading assigning to uninitialized memory in rem_all(char) method
     *   then test the correct function
     */
    return 0;
}