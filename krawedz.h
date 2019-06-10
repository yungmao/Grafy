#ifndef KRAWEDZ_H_INCLUDED
#define KRAWEDZ_H_INCLUDED
using namespace std;

template <typename typ>
class krawedz
{
    public:
    int poczatek; //poczatek polaczenia
    int koniec; //koniec polaczenia
    int typpolaczenia; //do macierzy sasiedztwa
    int wartosc;
    bool IsAdded;
    krawedz()
    {
        poczatek=-1;
        koniec=-1;
        typpolaczenia=0;
        wartosc=-1;
        IsAdded=false;
    }

    ~krawedz(){}

    int zwrocTyp()
    {
        return typpolaczenia;
    }
    void zmienTyp(int nowy)
    {
        typpolaczenia=nowy;
    }
    void zmienWartosc(typ nowa)
    {
        wartosc=nowa;
    }

    int zwrocKoniec()
    {
        return koniec;
    }
    int zwrocPoczatek()
    {
        return poczatek;
    }
    int zwrocWartosc()
    {
        return wartosc;
    }
    void zmienPolaczenie(int pocz, int kon)
    {
        poczatek=pocz;
        koniec=kon;
    }
    void kopiuj(krawedz<typ>* p)
    {
        poczatek= p->zwrocPoczatek();
        koniec= p->zwrocKoniec();
        wartosc= p->zwrocWartosc();
        typpolaczenia=p->zwrocTyp();
    }
    void ShowEdge()
    {cout<<"("<<poczatek<<","<<koniec<<endl;}
    void AddToMST(){IsAdded=true;};
};


#endif
