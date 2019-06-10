#ifndef KRUSKAL_HH_INCLUDED
#define KRUSKAL_HH_INCLUDED

#include "grafMacierz.h"
#include "krawedz.h"

template <typename typ>
class kruskal
{
grafLista<typ>* drzewoo;
grafMacierz<typ>* drzewo;
krawedz<typ> *krawedzie;
int wdrzewie;
int rozmiar;
int ilekrawedzi;



public:


    kruskal(grafMacierz<typ>* nowy)
        {
    drzewo=new grafMacierz<typ>;
    ilekrawedzi=nowy->kopiujGraf(drzewo); //kopiowanie tablicy i okreslenia rozmiarow tablic
    rozmiar=drzewo->zwrocRozmiar();
    wdrzewie=0;
    krawedzie=new krawedz<typ>[ilekrawedzi]; //zapisywanie krawedzi
    int k=0;
    for(int i=0; i<rozmiar; i++)         //czyszczenie drzewa
            {
            for(int j=i; j<rozmiar; j++)
                {
                if(drzewo->sprawdzPolaczenie(i, j)==1)
                    {
                krawedzie[k].zmienPolaczenie(i, j);    //zapisywanie krawedzi do tablicy dostepnych
                krawedzie[k].zmienWartosc(drzewo->sprawdzWartosc(i,j));
                krawedzie[k].zmienTyp(1);
                k++;
                drzewo->usunKrawedz(i,j); //usuwanie krawedzi z drzewa/czyszczenie drzewa
                    }
                }
            }

        }

    void budujDrzewo()
        {
        sortowanieKrawedzi(0, ilekrawedzi-1);  //sortuje za pomoca quicksort
        for(int i=0; i<ilekrawedzi; i++)
                {
        if(znajdzPolaczenie(krawedzie[i].zwrocPoczatek(), krawedzie[i].zwrocKoniec(), krawedzie[i].zwrocPoczatek(), i)==0)
            {
            drzewo->dodajKrawedz(krawedzie[i].zwrocPoczatek(), krawedzie[i].zwrocKoniec(), krawedzie[i].zwrocWartosc());
            wdrzewie++;
            }
        if(wdrzewie==rozmiar-1)
            {
                break;
            }
            }
        }

    void wyswietl()
    {
    drzewo->wyswietl();
    }

    int znajdzPolaczenie(int poczatek, int koniec, int poprzednie,int krawedz)
       {
           for(int i=0; i<rozmiar; i++)  //sprawdzanie polaczen
           {
               if(i!=poprzednie)  //sprawdza czy to nie jest z poprzedniego wezla
               {
               if(drzewo->sprawdzPolaczenie(poczatek, i)==1)
               {
                   if(i==koniec)
                    return 1;
                   else {
                        if(znajdzPolaczenie(i, koniec, poczatek, krawedz)) //rekurenycjnie szukanie slepego punktu
                    {
                        return 1;}
                   }
               }
               }
           }
           return 0;   //jesli nie ma polaczenia
       }


void sortowanieKrawedzi(int poczatek,int koniec) //quicksort
        {
    int i = poczatek;
    int j = koniec;
    typ podzial = krawedzie[( poczatek + koniec ) / 2 ].zwrocWartosc();
    krawedz<typ> pom;
    do
    {
        while( krawedzie[ i ].zwrocWartosc() < podzial )
             i++;
        while( krawedzie[ j ].zwrocWartosc() > podzial )
             j--;

        if( i <= j )
        {
            pom.zmienPolaczenie(krawedzie[i].zwrocPoczatek(), krawedzie[i].zwrocKoniec());
            pom.zmienWartosc(krawedzie[i].zwrocWartosc());
            krawedzie[i].zmienPolaczenie(krawedzie[j].zwrocPoczatek(), krawedzie[j].zwrocKoniec());
            krawedzie[i].zmienWartosc(krawedzie[j].zwrocWartosc());
            krawedzie[j].zmienPolaczenie(pom.zwrocPoczatek(), pom.zwrocKoniec());
            krawedzie[j].zmienWartosc(pom.zwrocWartosc());
            i++;
            j--;
        }
    } while( i <= j );
    if( poczatek < j )
    sortowanieKrawedzi(poczatek, j );

    if( koniec > i )
    sortowanieKrawedzi(i, koniec );

        }

};
//klasa wezel
class Node{
public:
    int n;
    Node *p;
    Node()
    {n=0;
    p=this;
    }
    ~Node(){}
};
//lista
class A
{
public:
    Node *node;
    int V;
    A(int V)
    {
    this->V = V;
    node = new Node[V+1];
    for(int i=0; i<=V; i++)
        node[i].n = i;
    }

	int FindSet(int u)
	{
	int x = node[u].p->n;
	if(x==u)
        return x;
	else
	return FindSet(x);

}
	void Union(int u, int v)
	{
	int x = FindSet(u);
	int y = FindSet(v);
	node[x].p = &node[y];
}
	~A()
	{
    delete []node;
	for(int i=0; i<=V; i++)
        node[i].p = NULL;
    }

};


#endif
