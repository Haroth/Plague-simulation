#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include <fstream>

#include "Czlowiek.h"
#include "Budynek.h"
#include "Miasto.h"

using namespace std;

double skazenieParam = 0.5;
double kwarantannaParam = 5;
int czasWyklucia = 10;
double wyzdrowienieParam = 4;
double zachorowanieParam = 5;
double zgonParam = 1;
double wplywStudni = 2;


int main()
{
    srand(time(NULL));
    fstream plik;
    plik.open( "wszyscy.txt", ios::out); plik.close();
    plik.open( "zdrowi.txt", ios::out); plik.close();
    plik.open( "chorzy.txt", ios::out); plik.close();
    plik.open( "chorzyZObjawami.txt", ios::out); plik.close();
    plik.open( "martwi.txt", ios::out); plik.close();
    int czas = 500;
    Miasto miasto(10, 10);

    for (int i = 0; i < czas; i++)
    {
        miasto.iteracja();
        miasto.zapisDoPliku("wszyscy");
        miasto.zapisDoPliku("zdrowi");
        miasto.zapisDoPliku("chorzy");
        miasto.zapisDoPliku("chorzyZObjawami");
        miasto.zapisDoPliku("martwi");
        Sleep(300);
        system("CLS");
    }
    return 0;
}

