#ifndef ELEMENTLISTY_H_INCLUDED
#define ELEMENTLISTY_H_INCLUDED

#include "krawedz.h"

template <typename typ>
class elementListy{
krawedz<typ>* kraw;
elementListy<typ>* nastepny;
elementListy<typ>* poprzedni;

public:
    elementListy()
        {
            kraw=new krawedz<typ>;
            nastepny=NULL;
            poprzedni=NULL;
        }
    void zmienNastepny(elementListy<typ>* nowy)
        {
            nastepny=nowy;
        }

    void zmienZawartosc(krawedz<typ>* nowa)
        {
            kraw->Kopiuj(nowa);
        }

    krawedz<typ>* zwrocZawartosc()
        {
            return kraw;
        }

    elementListy<typ>* zwrocNastepny()
        {
            return nastepny;
        }

    elementListy<typ>* zwrocPoprzedni()
        {
            return poprzedni;
        }

    void zmienPoprzedni(elementListy<typ>* nowy)
        {
            poprzedni=nowy;
        }


};

#endif // ELEMENTLISTY_H_INCLUDED
