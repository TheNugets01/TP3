#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

string convertToString(char* a)
{
    int size;
    for (int size = 0; a[size]!= '\0' ; ++size){}
    string s = "";
    for (int i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int main ( )
{   
    char * mou = new char(5);
    mou = "yo";
    string s = convertToString(mou);
    cout << s+s << endl;

    return 0;
}


