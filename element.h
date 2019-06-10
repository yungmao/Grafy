#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include <cstddef>
#include <iostream>
#include <cstdlib>
#include "krawedz.h"
using namespace std;

template <typename typ>
class element{  //element kolejki (dwukierunkowej)
    element<typ> *nastepny;
    element<typ> *poprzedni; //wskazniki na kolejne elementy kolejki
    int ilosc;
    int numerWezla;
    krawedz<typ>* kraw;
public:

    void dodajKrawedz(int z, int wartosc) //dodaje krawedz do wezla
    {
        krawedz<typ>* bufor=new krawedz<typ>[ilosc+1];
        for(int i=0;i<ilosc;i++) //usuwanie rozlaczonych polaczen z pamieci
        {
            bufor[i].ZmienPolaczenie(numerWezla,kraw[i].ZwrocKoniec());
            bufor[i].ZmienWartosc(kraw[i].ZwrocWartosc());
        }
        bufor[ilosc].ZmienPolaczenie(numerWezla, z);
        bufor[ilosc].ZmienWartosc(wartosc);


        delete[] kraw;
        kraw=bufor;
    }

    void usunKrawedz(int z) //usuwanie krawedzi z elementu
        {
            int nilosc=ilosc;
            for(int i=0; i<ilosc; i++)   //znajdywanie polaczen do usuniecia
            {
                if(z==kraw[i].ZwrocKoniec())
                {
                    kraw[i].ZmienPolaczenie(-1, -1);  //rozlaczanie polaczen
                    nilosc--;
                }
            }
            krawedz<typ>* bufor=new krawedz<typ>[nilosc];
            int j=0;
             for(int i=0; i<ilosc; i++)    //usuwanie rozlaczonych polaczen z pamieci
            {
                if(kraw[i].ZwrocKoniec()!=-1)
                {
                    bufor[j].ZmienPolaczenie(numerWezla, kraw[i].ZwrocKoniec());
                    bufor[j].ZmienWartosc(kraw[i].ZwrocWartosc());
                    j++;
                }
                if(j>nilosc)
                    cout<<"\n przekroczono zakres pamieci";
            }
        delete[] kraw; //zwalnianie pamieci
        kraw=bufor;   //zmiana tablicy krawedzi
        ilosc=nilosc;    //zredukowanie ilosci pamietanych krawedzi
        }


        element()
        {
            nastepny=NULL;
            poprzedni=NULL;
            ilosc=0;
            kraw=NULL;
            numerWezla=-1;
        }
        ~element()
        {
            delete[] kraw;
        }

        element<typ>* zwrocNastepny()
        {
            return nastepny;
        }

        void zmienNastepny(element<typ>* nowy)
        {
            nastepny=nowy;
        }

        element<typ>* zwrocPoprzedni()
        {
            return poprzedni;
        }

           void zmienPoprzedni(element<typ>* nowy)
        {
            poprzedni=nowy;
        }

        void zmienKrawedzie(krawedz<typ> *nowe, int ile)    //zmiana krawedzi
        {
            krawedz<typ>* bufor=new krawedz<typ>[ile];
            for(int i=0; i<ile; i++)
            {
                bufor[i].zmienPolaczenie(nowe[i].zwrocPoczatek(), nowe[i].zwrocKoniec());
                bufor[i].zmienWartosc(nowe[i].zwrocWartosc());
            }
            kraw=bufor;
            ilosc=ile;
        }

         krawedz<typ>* zwrocWkraw()
        {
            return kraw;
        }

        void zmienNumer(int nowy)
        {
            numerWezla=nowy;
        }

        int zwrocNumer()
        {
            return numerWezla;
        }

        int zwrocIlosc()
        {
            return ilosc;
        }

        krawedz<typ> zwrocKrawedz(int i)
        {
            if(i<ilosc&&i>=0)
            return kraw[i];

            }

};


#endif // ELEMENT_H_INCLUDED
