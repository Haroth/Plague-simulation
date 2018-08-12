#include <iostream>
#include <vector>
#include "Czlowiek.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  PARAMETRY
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// kwarantannaParam
// skazonaParam
// otoczenie

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  KLASY
////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Budynek
{
public:
    Budynek();
    ~Budynek();
    virtual void iteracja()=0; // metoda wykonujaca sie na budynku w kazdej iteracji
    virtual void ustawKwarantanne();
    virtual int getLiczbaMieszkancow();
    virtual int getLiczbaZdrowych();
    virtual int getLiczbaChorych();
    virtual int getLiczbaZObjawami();
    virtual bool getKwarantanna();
    virtual void ustawSkazenie();
    virtual bool getSkazona();
    virtual bool getStanPobliskiejStudni();
    virtual void setStanPobliskiejStudni( bool stan );
    virtual void setSzansaWyzdrowienia( double szansa );
    virtual void setSzansaZachorowania( double szansa );
    virtual void setSzansaZgonu( double szansa );
};

class Dom : public Budynek
{
private:
    int liczbaMieszkancow; // tylko w domu
    int liczbaZdrowych;
    int liczbaChorych;
    int liczbaZObjawami;
    vector <Czlowiek> mieszkancy;
    bool kwarantanna;
    bool stanPobliskiejStudni;
    double szansaWyzdrowienia;
    double szansaZachorowania;
    double szansaZgonu;

public:
    void iteracja ();
    void ustawKwarantanne();


    Dom(int liczbaMieszkancow_=0);
    ~Dom();
    int getLiczbaMieszkancow();
    int getLiczbaZdrowych();
    int getLiczbaChorych();
    int getLiczbaZObjawami();
    bool getKwarantanna();
    bool getStanPobliskiejStudni();
    void setStanPobliskiejStudni(bool stan);
    void setSzansaWyzdrowienia(double szansa);
    void setSzansaZachorowania(double szansa);
    void setSzansaZgonu(double szansa);
};

class Studnia : public Budynek
{
private:
    bool skazona;
public:
    void iteracja();
    void ustawSkazenie();

    Studnia(bool skazona_=false);
    ~Studnia();
    bool getSkazona();
};

class Miasto
{
private:
    int liczbaRzedow;
    int liczbaKolumn;
public:
    Budynek*** budynki;

public:
    void rysuj();
    void iteracja();
    void obliczPrawdopodobienstwo ();
    void zapisDoPliku(string nazwa);

    Miasto(int liczbaRzedow_=18, int liczbaKolumn_=13);
    ~Miasto();

};
