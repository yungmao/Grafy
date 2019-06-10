#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <algorithm>
#include <conio.h>

#include "element.h"
#include "elemListy.h"
#include "grafLista.h"
#include "grafMacierz.h"
#include "kolejka.h"
#include "krawedz.h"
#include "lista.h"
#include "Prim.h"
#include "kruskal.h"
#include <ctime>
using namespace std;

bool SortByW(krawedz<int> &e1, krawedz<int> &e2 )
{ return(e1.wartosc<e2.wartosc);}

int main()
{
    srand( time( NULL ) );

    //generowanie grafu
    double Czasy[100];
    LARGE_INTEGER frequency;
    LARGE_INTEGER t1, t2;
    double wynik=0;
    double Czas=0;
    int ilosc=100;
    grafMacierz<int>** Graf=new grafMacierz<int>*[ilosc];
    int s;
    //menu
    cout <<"Wybierz tryb pracy: "<<endl;
    cout <<"1-Algorytm Prima i Kruskala macierz"<<endl;
    cout <<"2-Algorytm Kruskala lista"<<endl;
    cout <<"3-Alorytm Prima lista"<<endl;
    cout <<"4-sprawdzenie implementacji generacji i zapisu"<<endl<<endl;
    cin >> s;
    cout<<endl;
    switch(s)
    {

      case 1:
    {
        int Wi;
        double Pr;
        cout << "Wprowadz liczbe wierzcholkow"<< endl;
        cin >> Wi;
        cout << endl << "Wprowadz wypelnienie w %" << endl;
        cin >> Pr;
        double Wy=Pr/100;
    for(int i=0; i<ilosc; i++)
    {   //generuje graf
        Graf[i]=new grafMacierz<int>;
        Graf[i]->generujGraf(Wi, Wy);
    }

    QueryPerformanceFrequency(&frequency);
    double srednia=0;

    for(int i=0; i<ilosc; i++)
    {
    prim<int>* DrzewoPrim=new prim<int>(Graf[i]);
    QueryPerformanceCounter(&t1);
    DrzewoPrim->zbudujDrzewo();     //budowanie drzewa
    QueryPerformanceCounter(&t2);
    //DrzewoPrim->debug_wyswietl();
    delete DrzewoPrim;
    //czas dla Prima
    Czas = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    Czasy[i]=Czas;
    cout <<endl<<"Algorytm Prima: "<< Czas << " ms.\n";
    }

    //sredni czas dla Prima
    for(int i=0; i<ilosc; i++)
    {
        wynik=wynik+Czasy[i];
    }
    srednia=wynik/ilosc;
    cout<<"\nSredni czas wykonywania dla Prima: " <<srednia<<endl;

    //kopiowanie grafu do Kruskala
    grafMacierz<int>* Kopia=new grafMacierz<int>;

    for(int i=0; i<ilosc; i++)
    {
        Graf[i]->kopiujGraf(Kopia);
        kruskal<int>* Drzewo=new kruskal<int>(Kopia);
        QueryPerformanceCounter(&t1);
        Drzewo->budujDrzewo();
        //czas dla Kruskala
        QueryPerformanceCounter(&t2);
        delete Drzewo;
        Czas = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
        Czasy[i]=Czas;
        cout <<endl<<"Algorytm Kruskala: "<< Czas << " ms.\n";
    }
    wynik=0;
    srednia=0;
    //Sredni czas dla Kruskala
    for(int i=0; i<ilosc; i++)
    {
        wynik=wynik+Czasy[i];
    }
    srednia=wynik/ilosc;
    cout<<"\nSredni czas wykonywania dla Kruskala: "<<srednia;

    for(int i=0; i<ilosc; i++)
    {
        delete Graf[i];
    }
    }
     break;

     case 2:

    {   //wybor parametrow
        int Wi;
        double Pr;
        cout << "Wprowadz liczbe wierzcholkow"<< endl;
        cin >> Wi;
        cout << endl << "Wprowadz wypelnienie w %" << endl;
        cin >> Pr;
        double Wy=Pr/100;
    for(int i=0; i<ilosc; i++)
    {
    int V, E;
    //wybor wierzcholkow i gestosci
	int poczatek, koniec, wartosc;
    V=Wi;
    E=(Wy*V*(V-1))/2;
 QueryPerformanceFrequency(&frequency);
	A k(V);
	krawedz<int>*e;
	e = new krawedz<int>[E];
    double Czas;

int p=1;
	for(int i=1; i<E; i++)
	{
	    if(p=V)
            p=1;
		e[i].poczatek=(( std::rand() % V ) + 1 );
		e[i].koniec=(( std::rand() % V ) + 1 );
		e[i].wartosc=(( std::rand() % E ) + 1 );
		p++;
	}


	sort(e, e+E, SortByW);
 QueryPerformanceCounter(&t1);
	for(int i=1; i<E; i++){

		poczatek= e[i].poczatek;
		koniec= e[i].koniec;
		if(k.FindSet(poczatek)!=k.FindSet(koniec)){
			e[i].AddToMST();
			k.Union(poczatek, koniec);
		}

	}
	//zliczanie czasu i wypisywanie
			 QueryPerformanceCounter(&t2);
		Czas = (t2.QuadPart - t1.QuadPart) * 10000.0 / frequency.QuadPart;
		cout <<endl<<"Algorytm Kruskala: "<< Czas << " ms.\n";
		wynik=Czas+wynik;
/*
   //pocztek i koniec galezi
	cout<<"Resulting MST: u  v\n";
	for(int i=0; i<E; i++){
		if(e[i].IsAdded)
		cout<<"("<<e[i].poczatek<<","<<e[i].koniec<<")"<<endl;
	}
*/

    }
     cout<<endl<<"Sredni czas dla Kruksala: "<<wynik/ilosc<<" ms.\n";
 }
    break;

    case 3:
{       //wybor parametrow
        int Wi;
        double Pr;
        cout << "Wprowadz liczbe wierzcholkow"<< endl;
        cin >> Wi;
        cout << endl << "Wprowadz wypelnienie w %" << endl;
        cin >> Pr;
        double Wy=Pr/100;

    //Prim lista
 double Czas;
 int V = Wi;
 int E=(Wy*V*(V-1))/2;        //dobór parametrów
 QueryPerformanceFrequency(&frequency);
    //tworzenie grafu
    struct Graph* graph = createGraph(V);
    double wynik=0;
  for(int i=0; i<ilosc; i++)
    {

 for(int z=1;z<E;z++)
 {

addEdge(graph, (( std::rand() % (V-1) )  ), (( std::rand() % (V-1) )  ) , (( std::rand() % E ) ));
 }

    QueryPerformanceCounter(&t1);
    PrimMST(graph);
    QueryPerformanceCounter(&t2);
     Czas = (t2.QuadPart - t1.QuadPart) * 10000.0 / frequency.QuadPart;

     cout <<endl<<"Algorytm Prima: "<< Czas << " ms.\n";
     wynik=Czas+wynik;  //zliczanie ca³kowitego czasu

}
    cout<<endl<<"Sredni czas dla Prima: "<<wynik/ilosc<<" ms.\n";
} break;
    case 4:{

    //Sprawdzanie implementacji, generowanie grafu i wyswietlanie w 2 postaciach
    grafLista<int>* GrafL=new grafLista<int>;
    GrafL->generujGraf(10, 0.5);
    const char* Nazwa="Graf.txt";
    GrafL->zapiszGraf(Nazwa);
    grafMacierz<int>* Graf=new grafMacierz<int>(Nazwa);
    Graf->wyswietl();
    grafLista<int>* GrafWczytany=new grafLista<int>(Nazwa);
    GrafWczytany->wyswietlGraf();

   }break;
return 0;

}
}

