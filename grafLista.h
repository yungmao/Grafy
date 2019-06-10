#ifndef GRAFMLISTA_H_INCLUDED
#define GRAFMLISTA_H_INCLUDED

#include <fstream>
#include <iostream>
#include "grafMacierz.h"
#include "kolejka.h"
#include "element.h"

template <typename typ>
class grafLista
{
    int ilosc;
    kolejka<typ> *graf;

public:

    grafLista()
    {
        graf=new kolejka<int>;
        ilosc=0;
    }
    //wczytywanie grafu lista
   grafLista(const char* NazwaPliku)
    {
        graf=new kolejka<int>;
        wczytajGraf(NazwaPliku);
    }

    ~grafLista()
    {
        delete graf;
    }

    //usuwa wezel
    void usunWezel(int nr)
{
    graf->usunWezel(nr);
    ilosc--;
}

    int zwrocIlosc()
{
    return ilosc;
}
    //odwanie wezla
    void dodajWezel(krawedz<typ>* bufor, int ile, int numer)
{
    graf->dodajKoniec(bufor, ile, numer);

}
//Dodawanie krawedzi
    void dodajKrawedz(int poczatek, int koniec, int wartosc)
{
    graf->dodajKrawedz(poczatek, koniec, wartosc);
}

//Usuwanie krawedzi
    void usunKrawedz(int poczatek, int koniec)
{
    graf->usunKrawedz(poczatek, koniec);
}

//Szukanie wezla
    element<typ>* znajdzWezel(int nr)
{
       return graf->znajdzWezel(nr);
}

//Pokaz graf
    void wyswietlGraf()
{
    graf->wyswietlKolejke();
}
    //generowanie grafu lista
    void generujGraf(int rozmiar, double gestosc)
{
    ilosc=rozmiar;
    grafMacierz<typ>* grafPomocniczy=new grafMacierz<typ>;
    grafPomocniczy->generujGraf(rozmiar, gestosc);

    int ilosck=0;
    krawedz<typ>* noweKrawedzie=new krawedz<typ>[rozmiar];
    krawedz<typ>* pomWskaznik;

    for(int i=0; i<rozmiar; i++)
    {
        for(int j=0; j<rozmiar; j++)
        {
            if(grafPomocniczy->sprawdzPolaczenie(i,j))
            {
                pomWskaznik=grafPomocniczy->zwrocWskKrawedz(i,j);

                noweKrawedzie[ilosck].kopiuj(pomWskaznik);
                ilosck++;
            }
        }

        dodajWezel(noweKrawedzie, ilosck, i);
        ilosck=0;
    }

}
    //wczytuje graf
    int wczytajGraf(const char* NazwaPliku)
{
       ifstream Plik;
            Plik.open(NazwaPliku, std::ios::out);
             if(Plik.good()!=true)
             {
            return 0;
             }

             if(Plik>>ilosc) {
                krawedz<typ>* bufor=new krawedz<typ>[ilosc];// tablica pomocnicza na krawedzie
                int ilosck=0;
                int pocz=0;
                int koniec=0;
                typ dlugosc=0;
                int i=0;
                int konieclinii=0; //flaga wykrywajaca koniec linii;

            while(i<ilosc)
            {
                Plik>>pocz;
                if(pocz!=-10)
                {
            while(!konieclinii)
            {
                if(Plik>>koniec) //czy udalo sie wczytac liczbe
                {
                    if(koniec==-10)   //czy jest to koniec linii (-10)
                        konieclinii=1;
                        else {
                            if(Plik>>dlugosc)    //czy udalo sie wczytac druga liczbe
                            {
                                if(dlugosc<0) {

                                    return 0;
                                }
                                else
                                    {
                                        bufor[ilosck].zmienPolaczenie(pocz, koniec);
                                        bufor[ilosck].zmienWartosc(dlugosc);
                                        ilosck++;
                                }
                            }
                        }
                } else {
                    cout<<"Blad! Nie udalo sie wczytac danych polaczenia wezla "<< i;
                        konieclinii=1;
                        }
            }
            dodajWezel(bufor, ilosck, pocz);
                }

            i++;
            if(i==10)
                break;
            konieclinii=0;
            ilosck=0;
            }
            Plik.close();
            return 1;
            } else {cout<<"\n Plik jest pusty!!!";
            Plik.close();
            return 0;}
}

    //zapis grafu
    int zapiszGraf(const char* NazwaPliku)
{
    if(ilosc!=0)
            {
            ofstream Plik;
            Plik.open(NazwaPliku, std::ios::in|std::ios::trunc);
             if(Plik.good()!=true)
             {
            cout<<"\nError: Nie udalo sie otworzyc pliku!!!\n";
            return 0;
             }
             element<typ>* temp;
                    Plik<<ilosc<<endl;  //zapisywanie ilosci wezlow grafu
                    for(int i=0; i<ilosc; i++)
                    {
                        temp=znajdzWezel(i);
                        if(temp!=NULL)  //jesli nie zostanie zwrocony null
                        {
                        Plik<<temp->zwrocNumer()<<" ";   //to znaczy ze taki wezel jest na liscie, zapisujemy jego numer

                        for(int j=0; j<temp->zwrocIlosc(); j++)
                        {
                            Plik<<temp->zwrocKrawedz(j).zwrocKoniec()<<" "<<temp->zwrocKrawedz(j).zwrocWartosc()<<" ";
                        }

                            }
                         else
                        {
                            Plik<<i;
                        }
                        Plik<<-10<<endl;
                    }

            return 1;
            } else {
            cout<<"\nNie ma czego zapisywac!!!";
            return 0;
            }
        }

};

#endif // GRAFMLISTA_H_INCLUDED
