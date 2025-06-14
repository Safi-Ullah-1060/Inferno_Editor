#ifndef MyStr_H
#define MyStr_H

#include <iostream>
using namespace std;

class MyStr
{
private:
    int len = 0;
    int cap = 0;
    char *Cs;

public:
    MyStr();
    MyStr(const MyStr &);
    MyStr(const char *);
    MyStr(int, char);
    MyStr(int);
    MyStr &operator=(const MyStr &);
    MyStr operator+(const MyStr &);
    MyStr &operator+=(const MyStr &);
    void print();
    void replace_first(char);
    int stoi();
    MyStr itos(int);
    MyStr trim();
    bool is_equal(const MyStr &);
    bool is_less(const MyStr &);
    bool is_greater(const MyStr &);
    MyStr *Tokenize(const char *, int &);
    MyStr *split(char, int &);
    MyStr *split_at(int);
    bool is_delim(char, const char *);
    int *All_sub_str(const char *, int &);
    int find_first(char);
    int find_last(char);
    int *find_all(char, int &);
    void remove_at(int);
    void insert_at(int, char);
    void insert_at(int, const MyStr);
    void rem_first(char);
    void rem_last(char);
    void rem_all(char);
    void clear();
    void ToUpper();
    void ToLower();
    char operator[](int) const;
    char &operator[](int);
    void regrow();
    ~MyStr();
    friend ostream &operator<<(ostream &, const MyStr &);
    friend istream &operator>>(istream &, const MyStr &);
    void get(char *, int) const;
    int get_len() const;
};

#endif
