#ifndef DEQUE_HH_INCLUDED
#define DEQUE_HH_INCLUDED

#include <iostream>
#include "krawedz.h"
#include "elemListy.h"
using namespace std;

template <typename typ>
class lista
{
    int rozmiar;
    elementListy<typ> *poczatek;
    elementListy<typ> *koniec;

public:


        lista()
        {
            poczatek=NULL;
            koniec=NULL;
            rozmiar=0;
        }
        ~lista()
        {
            delete poczatek;
        }

     void dodajKrawedz(krawedz<typ>* dodawany)
    {
    elementListy<typ> *nowy=new elementListy<typ>;
    nowy->zwrocZawartosc()->kopiuj(dodawany);
    int wstawiono=0;
    if(poczatek==NULL)  //poczatek wskazuje na null
    {

        poczatek=nowy;
        koniec=nowy;

    }
    else
        {

        int i=0;
        elementListy<typ> *temp=poczatek;  //szukanie pierwszego elementu
        while(temp->zwrocNastepny()!=NULL) //Dopoki nie wskazuje na  NULL
        {
            if(nowy->zwrocZawartosc()->zwrocWartosc() < temp->zwrocZawartosc()->zwrocWartosc())
            {

                nowy->zmienNastepny(temp);
                nowy->zmienPoprzedni(temp->zwrocPoprzedni());
                if(i<1)
                {
                    poczatek=nowy;
                }
                else
                {
                temp->zwrocPoprzedni()->zmienNastepny(nowy);
                }
                temp->zmienPoprzedni(nowy);
                wstawiono=1;
                break;
            }
            temp=temp->zwrocNastepny();
            i++;
        }
        if(wstawiono==0)
            {
        if(nowy->zwrocZawartosc()->zwrocWartosc() < temp->zwrocZawartosc()->zwrocWartosc())
        {
            nowy->zmienNastepny(temp);
            nowy->zmienPoprzedni(temp->zwrocPoprzedni());
                if(i<1)
                {
                    poczatek=nowy;
                } else
                {
                temp->zwrocPoprzedni()->zmienNastepny(nowy);
                }
                temp->zmienPoprzedni(nowy);

        }
        else
        {

        temp->zmienNastepny(nowy);  //jesli koniec to dawny ostatni element zmienia wskaznik
        nowy->zmienPoprzedni(temp); //zapamietuje poprzednika
        nowy->zmienNastepny(NULL);  //nowy ustawia przechowywany w sobie wskaznik na NULL(bo koniec)
        koniec=nowy;  //ustawiam koniec na nowy
        }
        }

    }
    rozmiar++;
    }

     krawedz<typ>* zwrocKrawedz(int nr)
    {
        elementListy<typ>* temp;
        if(nr>rozmiar)
        {
            std::cout<<"\n Nie ma tego w liscie";
            return  NULL;

        }

        if(nr<(rozmiar/2+1))
            {
        temp=poczatek;

        for(int i=1; i<nr; i++)
        {
            temp=temp->zwrocNastepny();
        }
        }
        else
            {
        temp=koniec;
        for(int i=rozmiar; i>nr; i--)
        {
            temp=temp->zwrocPoprzedni();
        }
        }
    return temp->zwrocZawartosc();
    }



krawedz<typ>* pokazPierwszy()
{
    if(rozmiar!=0)
    {
        krawedz<typ>* dozwrotu=new krawedz<typ>;
        if(rozmiar==1)
        {
            dozwrotu->kopiuj(poczatek->zwrocZawartosc());
            delete poczatek;
            poczatek=NULL;
            koniec=NULL;
            rozmiar=0;
            return dozwrotu;
        }
    elementListy<typ>* temp=poczatek;
    poczatek=temp->zwrocNastepny();

    poczatek->zmienPoprzedni(NULL);
    dozwrotu->kopiuj(temp->zwrocZawartosc());
    rozmiar--;
    delete temp;
    return dozwrotu;
    }

}

    void wyswietlListe()
    {
    if(poczatek==NULL)
    {
        cout<<"\n Lista jest pusta";
    }
    else
    {
    cout<<"Lista zawiera nastepujace elementy: \n";
    elementListy<typ> *temp=poczatek;    //Pomocniczy wskaznik to przechodzenia listy
    while(temp!=NULL)
    {
        cout<<temp->zwrocZawartosc()->zwrocPocz()<<">"<<temp->zwrocZawartosc()->zwrocKoniec()<<" "; //Wyswietlanie wartosci elementu na ktory wskazuje temp
        temp=temp->zwrocNastepny();
    }
    }
    cout<<"Rozmiar "<<rozmiar<<endl;
    }


    void skrocListe(int ktory)  //usuwa element listy
{
        elementListy<typ>* temp=poczatek;
        elementListy<typ>* pom;
        int pocz=0;
        if(rozmiar>1)
        {
        while(temp!=NULL)
        {
            if(ktory==temp->zwrocZawartosc()->zwrocKoniec())
            {
                if(rozmiar==1)  //usuniecie ostatenigo
                {

            delete temp;
            koniec=NULL;
            poczatek=NULL;
            rozmiar=0;

                }
                else
                if(temp->zwrocNastepny()==NULL)   //czy ostatni
                {

                pom=temp->zwrocPoprzedni();
                pom->zmienNastepny(temp->zwrocNastepny());
                delete temp;
                koniec=pom;      //ustawiam nowy koniec
                temp=koniec;
                rozmiar--;
                }
                else
                {
                pom=temp->zwrocNastepny();
                pom->zmienPoprzedni(temp->zwrocPoprzedni());
                if(temp->zwrocPoprzedni()==NULL)    //czy pierwszy
                {
                    delete temp;
                    poczatek=pom;   //ustawiam nowy poczatek
                    temp=poczatek;
                    pocz=1;
                    rozmiar--;
                }
                else
                {
                pom=temp->zwrocPoprzedni();
                pom->zmienNastepny(temp->zwrocNastepny());
                delete temp;
                temp=pom;
                rozmiar--;
                }
                }
            }
                if(pocz==1)
                {
                    pocz=0;
                }
                else
                    {
                    temp=temp->zwrocNastepny();
                }
        }
    }
    else   //jesli ostatni element lub nie ma na nic
    {
        if(temp!=NULL)
        {
        if(ktory==temp->zwrocZawartosc()->zwrocKoniec())
        {
            delete temp;
            koniec=NULL;
            poczatek=NULL;
            rozmiar=0;
        }
        }
    }
}

};

#endif
