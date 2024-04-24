#ifndef LUCKYHIT_H
#define LUCKY_HIT


#include <iostream>
#include <cstring>                // Potrebne pre funkciu strcpy
#include <string>                // Potrebne pre funkciu strcpy

using namespace std;

//** Zaciatok triedy TPlayer **
class TPlayer 
{
private:
    int zasobnik_pocet;            //pocet cisel v zasobniku
    int* zasobnik;                //zasobnik cisel
public:
    TPlayer()                     //konstruktor triedy
    {
        zasobnik = NULL;         // inicializuje zasobnik
        prehra = false;
    }
    string meno_hraca;            //meno hraca
    int pocet_zivotov;            //pocet zivotov hraca
    int dolne;                    //najnizsie mozne cislo v zasobniku
    int horne;                    //najvyssie mozne cislo v zasobniku
    bool prehra;                //indikator prehry
    ~TPlayer()                     //destruktor tiedy
    {
        delete[] zasobnik;         //uvolnenie pamate po skonceni pouzivania
    }

    void ulozZasobnikPocet(int zasobnik_pocet)    //ulozi velkosti zasobnika, ak je NULL tak mu prideli pamat
    {
        this->zasobnik_pocet = zasobnik_pocet;
        if(this->zasobnik==NULL) this->zasobnik=new int[this->zasobnik_pocet];
    }
bool naplnZasobnik(int index, int hodnota) //naplni hodnotu zasobnika, kontroluje interval cisel
    {
        if (hodnota >= dolne && hodnota <= horne) 
        {
            zasobnik[index] = hodnota;
            return true;
        } 
        else 
        {
            return false;            //vrati chybu
        }
    }

    void zobrazZasobnik(void)         //zobrazi vsetky hodnoty zasobnika
    {
        int i=0;
        for(i=0;i<zasobnik_pocet;i++)
           cout<<i+1<<".cislo: "<<zasobnik[i]<<endl;
    }

    int vratHodnotuZasobnika(int pozicia)         //vrati hodnotu zo zasobnika z prislusnej pozicie
    {
        return zasobnik[pozicia];
    }

    int vratPocet(void)             //vrati aktualnu hodnotu zasobnika
    {
        return zasobnik_pocet;
    }
};
//** Koniec triedy TPlayer **

#endif