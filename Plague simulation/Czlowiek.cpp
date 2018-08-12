#include "Czlowiek.h"
#include <cstdlib>

//=======================================================================================================================================================
//=============================================== VARIABLES =============================================================================================
//=======================================================================================================================================================

extern int czasWyklucia;

int Czlowiek::wszyscyMieszkancy = 0;
int Czlowiek::wszyscyZdrowi = 0;
int Czlowiek::wszyscyChorzy = 0;
int Czlowiek::wszyscyZObjawami = 0;
int Czlowiek::wszyscyMartwi = 0;


Czlowiek::Czlowiek() : stan(1), oczekiwanie(0) {}
Czlowiek::~Czlowiek() {}

//=======================================================================================================================================================
//=============================================== ZMIEN STAN ============================================================================================
//=======================================================================================================================================================

void Czlowiek::zmienStan(double szansaWyzdrowienia, double szansaZachorowania, double szansaZgonu)
{
    int losowa = rand() % 100;

    if (szansaWyzdrowienia > 100)
        szansaWyzdrowienia = 100;
    else if (szansaWyzdrowienia < 0)
        szansaWyzdrowienia = 0;

    if(szansaZgonu > 100)
        szansaZgonu = 100;
    else if(szansaZgonu < 0)
        szansaZgonu = 0;

    if (stan == 2) // chory
    {
        if (oczekiwanie == czasWyklucia)
        {
            wszyscyZObjawami++;
            wszyscyChorzy--;
            stan = 3;
            oczekiwanie = 0;
        }
        oczekiwanie++;
    }
    if (stan == 1 && losowa < szansaZachorowania) // zdrowy
    {
        wszyscyChorzy++;
        wszyscyZdrowi--;
        stan = 2;
    }

    if (stan == 3 && !(szansaWyzdrowienia == 0 && szansaZgonu == 0)) // z objawami i co najmniej jedna z szans jest rozna od 0
    {
        double sumaSzans = szansaWyzdrowienia + szansaZgonu * (1 - szansaWyzdrowienia / 100);
        if(losowa < szansaWyzdrowienia / (szansaWyzdrowienia + szansaZgonu) * sumaSzans)
        {
            wszyscyZdrowi++;
            wszyscyZObjawami--;
            stan = 1;
        }
        else if (losowa < sumaSzans)
        {
            wszyscyMartwi++;
            wszyscyZObjawami--;
            stan = 4;
        }
    }
}


//=======================================================================================================================================================
//=============================================== GET ===================================================================================================
//=======================================================================================================================================================


int Czlowiek::getStan() { return stan; }

int Czlowiek::getWszyscyMieszkancy() { return Czlowiek::wszyscyMieszkancy; }
int Czlowiek::getWszyscyZdrowi() { return Czlowiek::wszyscyZdrowi; }
int Czlowiek::getWszyscyChorzy() { return Czlowiek::wszyscyChorzy; }
int Czlowiek::getWszyscyZObjawami() { return Czlowiek::wszyscyZObjawami; }
int Czlowiek::getWszyscyMartwi() { return Czlowiek::wszyscyMartwi; }


//=======================================================================================================================================================
//=============================================== INC ===================================================================================================
//=======================================================================================================================================================


void Czlowiek::incWszyscyMieszkancy() { Czlowiek::wszyscyMieszkancy++; }
void Czlowiek::incWszyscyZdrowi() { Czlowiek::wszyscyZdrowi++; }
void Czlowiek::incWszyscyChorzy() { Czlowiek::wszyscyChorzy++; }
void Czlowiek::incWszyscyZObjawami() { Czlowiek::wszyscyZObjawami++; }
void Czlowiek::incWszyscyMartwi() { Czlowiek::wszyscyMartwi++; }


//=======================================================================================================================================================
//=============================================== DEC ===================================================================================================
//=======================================================================================================================================================


void Czlowiek::decWszyscyZdrowi() { Czlowiek::wszyscyZdrowi--; }
void Czlowiek::decWszyscyChorzy() { Czlowiek::wszyscyChorzy--; }
void Czlowiek::decWszyscyZObjawami() { Czlowiek::wszyscyZObjawami--; }
