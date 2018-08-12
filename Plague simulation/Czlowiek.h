#ifndef Czlowiek_h
#define Czlowiek_h

#include <iostream>

using namespace std;

class Czlowiek
{
private:
    int stan; // 1 - Zdrowy, 2 - Chory, 3 - Chory z Objawami, 4 - Martwy
    int oczekiwanie;
    static int wszyscyMieszkancy, wszyscyZdrowi, wszyscyChorzy, wszyscyZObjawami, wszyscyMartwi; // w calym miescie

public:
    void zmienStan(double szansaWyzdrowienia, double szansaZachorowania, double szansaZgonu);

    Czlowiek();
    ~Czlowiek();
    int getStan(); // zwraca wartosc stan

    static int getWszyscyMieszkancy(); // zwraca wartosc
    static int getWszyscyZdrowi();
    static int getWszyscyChorzy();
    static int getWszyscyZObjawami();
    static int getWszyscyMartwi();

    static void incWszyscyMieszkancy(); // inkrementuje
    static void incWszyscyZdrowi();
    static void incWszyscyChorzy();
    static void incWszyscyZObjawami();
    static void incWszyscyMartwi();

    static void decWszyscyZdrowi(); // dekrementuje
    static void decWszyscyChorzy();
    static void decWszyscyZObjawami();
};

#endif // Czlowiek_h

