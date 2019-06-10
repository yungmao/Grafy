#ifndef KOLEJKA_H_INCLUDED
#define KOLEJKA_H_INCLUDED

#include <iostream>
#include "element.h"
#include "krawedz.h"
using namespace std;

template <typename typ>
class kolejka
{
    int rozmiar;
    element <typ>* koniec;
    element <typ>* poczatek;

    public:

    bool czyPuste() //czy kolejka pusta
    {
        if(rozmiar<=0)
            return true;
        else
            return false;
    }

    typ ostatnia()
    {
        return koniec->zwrocWartosc();
    }

    int zwrocRozmiar()
    {
        return rozmiar;
    }

    typ pierwsza()
    {
        return poczatek->zwrocWkraw();
    }

    kolejka()
    {
        poczatek=NULL;
        koniec=NULL;
        rozmiar=0;
    }
    ~kolejka()
    {
        usunKolejke();
        delete poczatek;
        delete koniec;
    }





    void dodajKoniec(krawedz<typ>* krawedzz,int ilosc, int numer)
    {
        element <typ> *nowy =new element <typ>;   //nowy elementu
    nowy->zmienKrawedzie(krawedzz, ilosc);
    nowy->zmienNumer(numer);

    if (czyPuste())           //Jesli pierwszy to ustaw go jako poczatek i koniec
    {
        koniec=nowy;
        poczatek=nowy;
        rozmiar++;              //zwieksz rozmiar
    }
    else
        {
        koniec->zmienNastepny(nowy);     //Ustaw wskaznik ostatniego elementu na  nowy adres
        nowy->zmienNastepny(NULL);   //Ustaw wskaznik nowego elementu nastepny na adres NULL
        nowy->zmienPoprzedni(koniec);   //Ustaw wskaznik ostatniego elementu poprzedni na adres ostatniego elementu kolejki
        koniec=nowy;     //ustawienie nowego jako ostatni element kolejki
        rozmiar++;    //zwieksz rozmiar

    }
    }




    void usunKolejke()
    {
        int pomoc=0;
        int ilosc=rozmiar;
        if(!czyPuste())  //Sprawdz czy kolejka nie jest pusta
    {
    element<typ> *temp=poczatek;
    element<typ> *DoUsun=NULL;
        while(temp!=NULL||pomoc<ilosc)
        {
        DoUsun=temp;
        temp=temp->ZwrocNastepny();
        delete DoUsun;
        pomoc++;
        rozmiar--;
        }

    }

    }


   int usunKoniec()
    {
        element<typ>* pom=koniec->zwrocPoprzedni();
        if(pom!=NULL)
            pom->ZmienNastepny(NULL); //koniec listy na poprzedni element
        if(koniec!=NULL)
            delete koniec;
        koniec=pom; //wskaznik na ostatni element
        rozmiar--;
        return 1;
    }



    void dodajPoczatek(krawedz<typ>* kraw, int ile, int numer)
        {
    element <typ> *nowy =new element <typ>;      //Procedura analogiczna jak w funckji dodaj_koniec()
    nowy->ZmienWKrawedzie(kraw, ile);
    nowy->ZmienNumer(numer);

    if (czyPuste())
    {
        koniec=nowy;
        poczatek=nowy;
        rozmiar++;
    }
    else
        {
        poczatek->ZmienPoprzedni(nowy);
        nowy->ZmienPoprzedni(NULL);
        nowy->ZmienNastepny(poczatek);
        poczatek=nowy;
        rozmiar++;
    }
        }


    int usunPoczatek()
    {
    element <typ>* pom=poczatek->ZwrocNastepny(); //jak usunPoczatek
    if(pom!=NULL)
    pom->ZmienPoprzedni(NULL);
    if(poczatek!=NULL)
    delete poczatek;
    poczatek=pom;
    rozmiar--;
    return 1;
    }



    element<typ>* znajdzWezel(int nr)
    {
    int znaleziono=0;
    element<typ>* temp=NULL;

    if(!czyPuste())  //Sprawdz czy kolejka nie jest pusta
    {
    if(nr<(rozmiar/2)+1)
{
        temp=poczatek; //zaczynaj od poczatku
        while(temp!=NULL)    //rob dopoki temp nie bedzie wskazywal na NULL
        {
        if(temp->zwrocNumer()==nr)
        {
        znaleziono=1;
            break;
        }
        temp=temp->zwrocNastepny();     //wskaznik zostaje przerzucony na kolejny element
        }
} else
    {
        temp=koniec;
        while(temp!=NULL)    //rob dopoki temp nie bedzie wskazywal na NULL
        {
            if(temp->zwrocNumer()==nr)
            {
            znaleziono=1;
            break;
            }
        temp=temp->zwrocPoprzedni();     //wskaznik zostaje przerzucony na kolejny element
        }
    }
    if(znaleziono!=1)
    {

        return NULL;
    }
    else
        {
            return temp;
            }
    }

    }



    void usunKrawedz(int z, int kon)
    {
        element<typ>* pom=znajdzWezel(z);
        if(pom!=NULL)
        {
            pom->usunKrawedz(kon);
        }
    }




    void usunWezel(int nr)
    {
        element<typ>* pom=NULL; //zmienna pomocnicza

       if(!czyPuste())  //Sprawdz czy kolejka nie jest pusta
    {
        pom=znajdzWezel(nr);
        if(pom!=NULL)
        {
        element<typ>* Poprz=pom->zwrocPoprzedni();   //Usuwanie wezla z grafu
        element<typ>* Nast=pom->zwrocNastepny();
        Poprz->zmienNastepny(Nast);   //zachowanie ciaglosci listy
        Nast->zmienPoprzedni(Poprz);
        rozmiar--;
        for(int i=0; i<pom->zwrocIlosc(); i++) //usuwanie krawedzie z grafu polaczonych z usuwanym wierzcholkiem
        {
            usunKrawedz(pom->zwrocKrawedz(i).zwrocKoniec(), nr);
        }

    delete pom; //zwolnienie pamieci po wezle
    } else cout<<"\nBlad";
    }
    }

    void dodajKrawedz(int pocz, int kon, int wartosc)
    {
    element<typ>* pom=NULL;
    pom=znajdzWezel(kon);
    if(pom!=NULL) {
    pom=znajdzWezel(pocz);
    if(pom!=NULL)
    {
        pom->dodajKrawedz(pocz, wartosc);
    } else
    {
        cout<<"\nWezel numer "<<pocz<<" nie nalezy do grafu\n";
    }
    } else cout<<"\nWezel numer "<<kon<<" nie nalezy do grafu\n";
    }



    void wyswietlKolejke()
    {
         if(!czyPuste())
    {
    element<typ>* pom=poczatek;
        while(pom!=NULL)
        {
        cout<<"\nW: "<<pom->zwrocNumer()<<"-> ";  //zwraca wartosc aktualnego elementu
        for(int i=0; i<pom->zwrocIlosc(); i++)
        {
            cout<<" "<<pom->zwrocKrawedz(i).zwrocKoniec()<<" D:"<<pom->zwrocKrawedz(i).zwrocWartosc();
        }
        cout<<endl;
        pom=pom->zwrocNastepny();     //wskaznik zostaje przerzucony na kolejny element
        }
    cout<<endl;
    }
    }


};


#endif
