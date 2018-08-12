#ifndef Budynek_h
#define Budynek_h

#include "Budynek.h"
#include <iomanip>
#include <typeinfo>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include <fstream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GLOBALNE PARAMETRY - wartosci podaje sie w main
////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern double skazenieParam;
extern double kwarantannaParam;
extern double wyzdrowienieParam;
extern double zachorowanieParam;
extern double zgonParam;
extern double wplywStudni;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  BUDYNEK
////////////////////////////////////////////////////////////////////////////////////////////////////////////

Budynek::Budynek() {}
Budynek::~Budynek() {}
int Budynek::getLiczbaMieszkancow() {}
int Budynek::getLiczbaZdrowych() {}
int Budynek::getLiczbaChorych() {}
int Budynek::getLiczbaZObjawami() {}
bool Budynek::getKwarantanna() {}
void Budynek::ustawKwarantanne() {}
void Budynek::ustawSkazenie() {}
bool Budynek::getSkazona() {}
bool Budynek::getStanPobliskiejStudni(){}
void Budynek::setStanPobliskiejStudni( bool stan ){}
void Budynek::setSzansaWyzdrowienia( double szansa ){}
void Budynek::setSzansaZachorowania( double szansa ){}
void Budynek::setSzansaZgonu( double szansa ){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOM
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Dom::iteracja() // tu beda zawarte wszystkie funkcje domu
{
    vector <int> indeksy;
    ustawKwarantanne();
    liczbaZdrowych = liczbaChorych = liczbaZObjawami = 0;
    for (int i = 0; i < liczbaMieszkancow; i++)
    {
        mieszkancy[i].zmienStan(szansaWyzdrowienia, szansaZachorowania, szansaZgonu);
        switch (mieszkancy[i].getStan())
        {
        case 1:
            liczbaZdrowych++;
            break;
        case 2:
            liczbaChorych++;
            break;
        case 3:
            liczbaZObjawami++;
            break;
        case 4:
            indeksy.push_back(i);
            break;
        }
    }
    for (int i = 0; i < indeksy.size(); i++)
    {
        mieszkancy.erase(mieszkancy.begin() + indeksy[i]);
        for (int j = i+1; j < indeksy.size(); j++)
            indeksy[j]--;
    }
    liczbaMieszkancow = liczbaZdrowych + liczbaChorych + liczbaZObjawami;
}



void Dom::ustawKwarantanne()
{
    int losowa=rand() % 100;
    if(kwarantanna == 0)
    {
        if (losowa < kwarantannaParam * liczbaZObjawami)
            kwarantanna = 1;
    }
    else if (kwarantanna == 1 && liczbaZObjawami != 0)
    {
        if (losowa < ((kwarantannaParam / liczbaZObjawami) * 3))
            kwarantanna = 0;
    }
    else if (kwarantanna == 1 && liczbaZObjawami == 0)
        kwarantanna = 0;
}

Dom::Dom(int liczbaMieszkancow_) : Budynek(), liczbaMieszkancow(liczbaMieszkancow_)
{
    liczbaZdrowych = liczbaMieszkancow;
    liczbaChorych = liczbaZObjawami=0;
    kwarantanna = false;
    stanPobliskiejStudni = false;
    szansaWyzdrowienia = szansaZachorowania = szansaZgonu = 0;
    for (int i = 0; i < liczbaMieszkancow; i++)
    {
        mieszkancy.push_back(Czlowiek());
        Czlowiek::incWszyscyMieszkancy();
        Czlowiek::incWszyscyZdrowi();
    }
}

Dom::~Dom() {}

int Dom::getLiczbaMieszkancow() { return liczbaMieszkancow; };
int Dom::getLiczbaZdrowych() { return liczbaZdrowych; };
int Dom::getLiczbaChorych() { return liczbaChorych; };
int Dom::getLiczbaZObjawami() { return liczbaZObjawami; };
bool Dom::getKwarantanna() { return kwarantanna; };
bool Dom::getStanPobliskiejStudni() { return stanPobliskiejStudni; };
void Dom::setStanPobliskiejStudni(bool stan) { stanPobliskiejStudni = stan; };
void Dom::setSzansaWyzdrowienia(double szansa){ szansaWyzdrowienia = szansa; };
void Dom::setSzansaZachorowania(double szansa){ szansaZachorowania = szansa; };
void Dom::setSzansaZgonu(double szansa){ szansaZgonu = szansa; };


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  STUDNIA
////////////////////////////////////////////////////////////////////////////////////////////////////////////

Studnia::Studnia(bool skazona_) : skazona(skazona_) {}

Studnia::~Studnia() {}

void Studnia::iteracja()
{
    ustawSkazenie();
}

void Studnia::ustawSkazenie()
{
    int losowa = rand() % 100;
    if (skazona == 0 && losowa < skazenieParam)
    {
        skazona = 1;
    }
    else if (skazona == 1 && losowa < skazenieParam)
    {
        skazona = 0;
    }
    // Liczy szanse ustawienia skazenia zalezna od parametru i ustawia wylosowany stan
    // SkazenieParam - tej zmiennej trzeba uzyc
}

bool Studnia::getSkazona() { return skazona; }


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  MIASTO
////////////////////////////////////////////////////////////////////////////////////////////////////////////

Miasto::Miasto(int liczbaRzedow_, int liczbaKolumn_) : liczbaRzedow(liczbaRzedow_), liczbaKolumn(liczbaKolumn_)
{
    budynki = new Budynek** [liczbaRzedow];
    for (int i = 0; i < liczbaRzedow; i++)
    {
        budynki[i] = new Budynek* [liczbaKolumn];
        for (int j = 0; j < liczbaKolumn; j++)
        {
            if (j % 5 == 2 && i % 5 == 2)
                budynki[i][j] = new Studnia();
            else
            {
                budynki[i][j] = new Dom(rand() % 19 + 2);
            }

        }
    }
}

Miasto::~Miasto()
{

}

void Miasto::rysuj()
{
    cout << "Wszyscy: " << Czlowiek::getWszyscyMieszkancy() << ". Zdrowi: " << Czlowiek::getWszyscyZdrowi() << ". Chorzy: " << Czlowiek::getWszyscyChorzy() << ". Chorzy z objawami: " << Czlowiek::getWszyscyZObjawami() << ". Martwi: " << Czlowiek::getWszyscyMartwi() << endl << endl;
    for (int i = 0; i < liczbaRzedow; i++)
    {
        cout << "|";
        for (int j = 0; j < liczbaKolumn; j++)
            cout  << "-----|";
        cout << endl << "|";
        for (int j = 0; j < liczbaKolumn; j++)
        {
            if (typeid(*budynki[i][j]) == typeid(Dom))
            {
                if (budynki[i][j]->getLiczbaMieszkancow( )== 0)
                    cout << "     ";
                else
                {
                    if (budynki[i][j]->getKwarantanna() == false)
                        cout << setw(2) << (budynki[i][j]->getLiczbaChorych()) + (budynki[i][j]->getLiczbaZObjawami()) << "/" << setw(2) << budynki[i][j]->getLiczbaMieszkancow();
                    else if (budynki[i][j]->getKwarantanna()==true)
                    {
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << setw(2) << (budynki[i][j]->getLiczbaChorych()) + (budynki[i][j]->getLiczbaZObjawami()) << "|" << setw(2) << budynki[i][j]->getLiczbaMieszkancow();
                    }
                }
            }
            else if (typeid(*budynki[i][j]) == typeid(Studnia))
            {
                if (budynki[i][j]->getSkazona() == false)
                {
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "  O  ";
                }
                else if (budynki[i][j]->getSkazona()==true)
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "  " << char(31) << "  ";
                }

            }
            SetConsoleTextAttribute(hConsole, 15);
            cout << "|";
        }
        cout << endl;
    }
    cout << "|";
    for (int j=0; j<liczbaKolumn; j++)
        cout  << "-----|";
}

void Miasto::iteracja()
{
    rysuj();

    for (int i = 0; i < liczbaRzedow; i++)
    {
        for (int j = 0; j < liczbaKolumn; j++)
        {
            if (!(i % 5 == 2 && j % 5 == 2))
            {
                if ((5 * (i / 5) + 2) <= liczbaRzedow && (5 * (j / 5) + 2) <= liczbaKolumn) // studnia miesci sie w miescie
                    budynki[i][j]->setStanPobliskiejStudni(budynki[5 * (i / 5 ) + 2][5 * (j / 5) + 2]->getSkazona());
                else
                {
                    if ((5 * (i / 5) + 2) > liczbaRzedow && (5 * (j / 5) + 2) > liczbaKolumn) // nie miesci sie w rzedach i kolumnach
                        budynki[i][j]->setStanPobliskiejStudni(budynki[5 * (i / 5) - 3][5 * (j / 5) - 3]->getSkazona());
                    else if ((5 * (i / 5) + 2)>liczbaRzedow) // nie miescie sie w rzedach
                        budynki[i][j]->setStanPobliskiejStudni(budynki[5 * (i / 5) - 3][5 * (j / 5) + 2]->getSkazona());
                    else if ((5 * (j / 5) + 2)>liczbaKolumn) // nie miesci sie w kolumnach
                        budynki[i][j]->setStanPobliskiejStudni(budynki[5 * (i / 5) + 2][5 * (j / 5) - 3]->getSkazona());
                }
            }
        }
    }

    obliczPrawdopodobienstwo();
    for (int i = 0; i < liczbaRzedow; i++)
        for (int j = 0; j < liczbaKolumn; j++)
            budynki[i][j]->iteracja();
}

void Miasto::obliczPrawdopodobienstwo()
{
    int liczbaZdrowych_, liczbaChorych_, liczbaZObjawami_;
    for (int i = 0; i < liczbaRzedow; i++)
    {
        for (int j = 0; j < liczbaKolumn; j++)
        {
            if (budynki[i][j]->getKwarantanna()) // jesli budynek jest w kwarantannie
            {
                if (budynki[i][j]->getLiczbaChorych() + budynki[i][j]->getLiczbaZObjawami() != 0)
                    budynki[i][j]->setSzansaWyzdrowienia(wyzdrowienieParam * (budynki[i][j]->getLiczbaZdrowych() / (budynki[i][j]->getLiczbaChorych() + budynki[i][j]->getLiczbaZObjawami())) + (!budynki[i][j]->getStanPobliskiejStudni() * wplywStudni));
                else
                    budynki[i][j]->setSzansaWyzdrowienia(100);
                if (budynki[i][j]->getLiczbaZdrowych() != 0)
                {
                    budynki[i][j]->setSzansaZachorowania(zachorowanieParam * ((budynki[i][j]->getLiczbaChorych() + budynki[i][j]->getLiczbaZObjawami()) / budynki[i][j]->getLiczbaZdrowych()) + budynki[i][j]->getStanPobliskiejStudni() * wplywStudni);
                    budynki[i][j]->setSzansaZgonu(zgonParam * ((budynki[i][j]->getLiczbaChorych() + budynki[i][j]->getLiczbaZObjawami()) / budynki[i][j]->getLiczbaZdrowych()) + budynki[i][j]->getStanPobliskiejStudni() * wplywStudni);
                }
                else
                {
                    budynki[i][j]->setSzansaZachorowania(100);
                    budynki[i][j]->setSzansaZgonu(zgonParam * (liczbaChorych_ + liczbaZObjawami_) + budynki[i][j]->getStanPobliskiejStudni() * wplywStudni);
                }
            }
            else // jesli nie jest w kwarantannie
            {
                liczbaZdrowych_ = liczbaChorych_ = liczbaZObjawami_ = 0;
                for (int n = i - 1; n <= i + 1; n++)
                {
                    for (int m = j - 1; m <= j + 1; m++)
                    {

                        if (n >= 0 && n < liczbaRzedow && m >= 0 && m < liczbaKolumn && !(n % 5 == 2 && m % 5 == 2))
                        {
                            liczbaZdrowych_ += budynki[n][m]->getLiczbaZdrowych();
                            liczbaChorych_ += budynki[n][m]->getLiczbaChorych();
                            liczbaZObjawami_ += budynki[n][m]->getLiczbaZObjawami();
                        }
                    }
                }
                if (liczbaChorych_ + liczbaZObjawami_ != 0)
                    budynki[i][j]->setSzansaWyzdrowienia(wyzdrowienieParam * (liczbaZdrowych_ / (double(liczbaChorych_ + liczbaZObjawami_))) + !budynki[i][j]->getStanPobliskiejStudni() * wplywStudni);
                else
                    budynki[i][j]->setSzansaWyzdrowienia(100);
                if (liczbaZdrowych_ != 0)
                {
                    budynki[i][j]->setSzansaZachorowania(zachorowanieParam * ((double(liczbaChorych_ + liczbaZObjawami_)) / liczbaZdrowych_) + budynki[i][j]->getStanPobliskiejStudni() * wplywStudni);
                    budynki[i][j]->setSzansaZgonu(zgonParam * ((double(liczbaChorych_ + liczbaZObjawami_)) / liczbaZdrowych_) + budynki[i][j]->getStanPobliskiejStudni() * wplywStudni);
                }
                else
                {
                    budynki[i][j]->setSzansaZachorowania(100);
                    budynki[i][j]->setSzansaZgonu(zgonParam * (liczbaChorych_ + liczbaZObjawami_) + budynki[i][j]->getStanPobliskiejStudni() * wplywStudni);
                }
            }
        }
    }
}

void Miasto::zapisDoPliku(string nazwa)
{
    fstream plik;
    nazwa=nazwa+".txt";
    plik.open( nazwa.c_str(), ios::out | ios::app );
    if ( plik.good() == true )
    {
        if (nazwa=="wszyscy.txt")
            plik << Czlowiek::getWszyscyMieszkancy() << endl;
        else if (nazwa=="zdrowi.txt")
            plik << Czlowiek::getWszyscyZdrowi() << endl;
        else if (nazwa=="chorzy.txt")
            plik << Czlowiek::getWszyscyChorzy() << endl;
        else if (nazwa=="chorzyZObjawami.txt")
            plik << Czlowiek::getWszyscyZObjawami() << endl;
        else if (nazwa=="martwi.txt")
            plik << Czlowiek::getWszyscyMartwi() << endl;
        plik.close();
    }
}

#endif // Budynek_h
