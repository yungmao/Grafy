#ifndef GRAFMACIERZ_H_INCLUDED
#define GRAFMACIERZ_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include "krawedz.h"

template <typename typ>
class grafMacierz
{
    krawedz<typ>** graf;
    int rozmiar;

public:

  void dodajKrawedz(int w1, int w2, typ wartosc)
    {
        if(w1<rozmiar&&w2<rozmiar)
        {
            graf[w1][w2].zmienPolaczenie(w1, w2);
            graf[w1][w2].zmienTyp(1);
            graf[w1][w2].zmienWartosc(wartosc);

            graf[w2][w1].zmienPolaczenie(w2, w1);
            graf[w2][w1].zmienTyp(1);
            graf[w2][w1].zmienWartosc(wartosc);
        }

    }


 void usunKrawedz(int w1, int w2)
    {
        if(w1<rozmiar&&w2<rozmiar)
        {
            if(graf[w1][w2].zwrocTyp()==1)
            {
            graf[w1][w2].zmienPolaczenie(w1, -1);
            graf[w1][w2].zmienTyp(0);
            graf[w1][w2].zmienWartosc(-1);

            graf[w2][w1].zmienPolaczenie(w2, -1);
            graf[w2][w1].zmienTyp(0);
            graf[w2][w1].zmienWartosc(-1);
            }
            }
    }


  int sprawdzPolaczenie(int w1, int w2)
    {
        if(w1>=0&&w2>=0&&w1<rozmiar&&w2<rozmiar)
        {
       return graf[w1][w2].zwrocTyp();
        } else return -1;
    }


       typ sprawdzWartosc(int w1, int w2)
    {
        if(w1>=0&&w2>=0&&w1<rozmiar&&w2<rozmiar)
        {
            if(graf[w1][w2].zwrocTyp()==1)
            return graf[w1][w2].zwrocWartosc();
            else return -1;
        } else return -1;
    }


    krawedz<typ> zwrocKrawedz(int w1, int w2)
    {
        return graf[w1][w2];
    }

      krawedz<typ>* zwrocWskKrawedz(int w1, int w2)
    {
        return &graf[w1][w2];
    }

        grafMacierz()
        {
            graf=NULL;
            rozmiar=0;
        }

        grafMacierz(const char* NazwaPliku)
        {
        graf=NULL;
        if(!wczytajGraf(NazwaPliku))
            cout<<"\nNie udalo sie wczytac grafu z pliku!";
        }

        ~grafMacierz()
        {
            for(int i=0; i<rozmiar; i++)
            delete[] graf[i];

            delete[] graf;
            rozmiar=0;
        }
    //wyswietlanie grafu
 void wyswietl()
    {
        cout<<endl;
        for(int i=0; i<rozmiar; i++)
        {
            for(int j=0; j<rozmiar; j++)
            {
                cout<<graf[i][j].zwrocWartosc()<<" ";
            }
            cout<<endl;
        }
    }
 void generujPusty(int ilosc)
    {
         rozmiar=ilosc;
          graf=new krawedz<typ>*[rozmiar];
        for(int i=0; i<rozmiar; i++)
        {
            graf[i]=new krawedz<typ>[rozmiar];
        }

        //Zerowanie tablicy sasiedztwa
        for(int i=0; i<rozmiar; i++)
        {
            for(int j=0; j<rozmiar; j++)
            {
                graf[i][j].zmienPolaczenie(i, -1);
                graf[i][j].zmienWartosc(-1);
                graf[i][j].zmienTyp(0);
            }
        }
    }
        //Wczytywanie grafu z pliku

 int wczytajGraf(const char* NazwaPliku)
        {
            ifstream Plik;
            Plik.open(NazwaPliku, std::ios::out);
             if(Plik.good()!=true)
             {
            cout<<"\nError: Nie udalo sie otworzyc pliku!!!\n";
            return 0;
             }
            if(Plik>>rozmiar) {
            generujPusty(rozmiar); //przygotowywanie macierzy do wypelnienia
            int pocz=0;
            int koniec=0;
            typ dlugosc=0;
            int i=0;
            int konieclinii=0; //flaga wykrywajaca koniec linii;
           // Edge<typ>* bufor=new Edge<typ>;
            while(i<rozmiar)
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
                                if(dlugosc<0)
                                    cout<<"\nBlad wczytywania dlugosci wezla "<<i<<"!!!";
                                else
                                    {
                                    if(sprawdzPolaczenie(i, koniec)==0)
                                    {
                                        //cout<<"\nDodaje :"<<i<<"-"<<dlugosc<<">"<<koniec;
                                        dodajKrawedz(i, koniec, dlugosc);
                                    }
                                }
                            }
                        }
                } else {
                    cout<<"Blad! Nie udalo sie wczytac danych polaczenia wezla "<< i;
                        konieclinii=1;
                        }

            }
                }
            i++;
            konieclinii=0;
            }
            } else {cout<<"\n Plik jest pusty!!!";
            return 0;}
        }


        //Zapisywanie grafu do pliku
 int zapiszGraf(const char* NazwaPliku)
        {
            if(rozmiar!=0)
            {
            ofstream Plik;
            Plik.open(NazwaPliku, std::ios::in|std::ios::trunc);
             if(Plik.good()!=true)
             {
            cout<<"\nError: Nie udalo sie otworzyc pliku!!!\n";
            return 0;
             }
                    Plik<<rozmiar<<endl;
                    for(int i=0; i<rozmiar; i++)
                    {
                        Plik<<i<<" ";
                        for(int j=0; j<rozmiar; j++)
                        {
                            if(sprawdzPolaczenie(i, j)&&sprawdzPolaczenie(i, j)!=-1)
                            {
                                Plik<<zwrocKrawedz(i, j).zwrocKoniec()<<" "<<zwrocKrawedz(i, j).zwrocWartosc()<<" ";
                            }
                        }
                        Plik<<-10<<endl;
                    }
            Plik.close();
            return 1;
            } else {
            cout<<"\nNie ma czego zapisywac!!!";
            return 0;
            }
        }

    //generowanie grafu macierz
 void generujGraf(int ilosc, double gestosc)
 {
     int wartosc=0;
     rozmiar=ilosc;
     srand(time(0));
     graf=new krawedz<typ>*[rozmiar];
     for(int i=0;i<rozmiar;i++)
     {
         graf[i]=new krawedz<typ>[rozmiar];
     }

      for(int i=0; i<rozmiar; i++)
        {
            for(int j=0; j<rozmiar; j++)
            {
                graf[i][j].zmienPolaczenie(i, -1);
                graf[i][j].zmienWartosc(-1);
                graf[i][j].zmienTyp(0);
            }
        }

        for(int i=0; i<rozmiar-1; i++)
        {
            //Ustawianie krawedzi z nastepnym wezlem
            wartosc=1 + (rand() % 200);
           dodajKrawedz(i, i+1, wartosc);
        }

        int limit=gestosc*(rozmiar*(rozmiar-1))/2-rozmiar+1;
        int i=-1;
        int j=-1;
        int k=0;

        while(k<limit)
        {
            do {
            i=rand()%(rozmiar);
            j=rand()%(rozmiar);
            }while(sprawdzPolaczenie(i, j)==1||sprawdzPolaczenie(i, j)==-1||i==j);
            dodajKrawedz(i, j, 1 + (rand() % 200));
            k++;

        }
 }

    //kopiowanie grafu macierz
 int kopiujGraf(grafMacierz<typ>* Kopia)
    {
        if(rozmiar>0)
        {
        int ilekrawedzi=0;
        Kopia->generujPusty(rozmiar);
        for(int i=0; i<rozmiar; i++)
        {
            for(int j=i; j<rozmiar; j++)
            {
                if(sprawdzPolaczenie(i, j)==1)
                {
                    Kopia->dodajKrawedz(i, j, sprawdzWartosc(i,j));
                    ilekrawedzi++;
                }
            }
        }
        return ilekrawedzi;
        } else { cout<<"\nGraf jest pusty, nie ma czego kopiowac!\n";
        return -1;
        }
    }

 int zwrocRozmiar()
 {
     return rozmiar;
 }
};


#endif
