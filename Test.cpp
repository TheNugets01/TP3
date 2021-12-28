#include <iostream>
#include <fstream>
#include "Catalogue.h"
#include "TrajetSimple.h"
#include "Trajet.h"


#include <typeinfo>

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
    int papa;
    Trajet * T = new TrajetSimple( "a" ,"a","a");
    cout << typeid(papa).name() << endl;

    return 0;
}


