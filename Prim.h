#ifndef PRIM_HH_INCLUDED
#define PRIM_HH_INCLUDED

#include "grafMacierz.h"
#include <vector>
#include "lista.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// wezel
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// lista
struct AdjList {
    struct AdjListNode* head; // pointer to head node of list
};

//V to ilosc wierzcholkow
struct Graph {
    int V;
    struct AdjList* array;
};

template <typename typ>
class prim
{
lista<typ> krawedzie;
int rozmiar;
int iloscwezlow;
int ilekrawedzi;
int* wdrzewie;
grafMacierz<typ>* tmp;
grafMacierz<typ>* drzewo;

public:

   void zbudujDrzewo()
    {
        while(czyKompletne()==0)
        {
        dodajKrawedz(*wybierzKrawedz()); //dodanie krawedzi
        iloscwezlow++;
        }
    }

    int czyKompletne()
    {
        int ilosc=1;
        for(int i=0; i<rozmiar; i++)
        {
            ilosc=ilosc*wdrzewie[i];
        }
        return ilosc;
    }

    void dodajKrawedz(krawedz<typ> nowa)
    {
        wdrzewie[nowa.zwrocKoniec()]=1;  //drzewo jest polaczone z tym wezlem
        dodajKrawedzieWezla(nowa.zwrocKoniec());  //pokazuje nowa ilosc krawedzi dostepnych
        drzewo->dodajKrawedz(nowa.zwrocPoczatek(), nowa.zwrocKoniec(), nowa.zwrocWartosc());
    }

    void dodajKrawedzieWezla(int wezel)
    {
        for(int i=0; i<rozmiar; i++)
        {
            if(tmp->sprawdzPolaczenie(wezel, i)==1)  //sprawdz czy jest nowa krawedz do dodania
            {
                if(!czyGraf(tmp->zwrocKrawedz(wezel, i)))   //czy krawedz nie prowadzi do wezla już bedacego w grafie
                {
                    dodajKrawedzListy(tmp->zwrocKrawedz(wezel, i));
                }
            }
        }
        krawedzie.skrocListe(wezel);
    }


    void wyswietl()
    {
       drzewo->wyswietl();
    }


    int czyGraf(krawedz<typ> nowy)
    {
      if(wdrzewie[nowy.zwrocKoniec()])
        return 1;
      else return 0;
    }


    void dodajKrawedzListy(krawedz<typ> nowy)
    {
        krawedz<typ>* temp=new krawedz<typ>;
        krawedz<typ>* pom=&nowy;
        temp->kopiuj(pom);
        krawedzie.dodajKrawedz(temp);
        delete temp;
    }

    krawedz<typ>* wybierzKrawedz()
    {
    return krawedzie.pokazPierwszy();   //zwraca pierwsza krawedz listy priorytetowej
    }

    prim(grafMacierz<typ>* Graf)
    {
        iloscwezlow=0;
            tmp=new grafMacierz<typ>;
            Graf->kopiujGraf(tmp); //kopiowanie tablicy i zapisywanie rozmiarow
            drzewo=new grafMacierz<typ>;
            rozmiar=tmp->zwrocRozmiar();
            drzewo->generujPusty(rozmiar);    //generowanie pustego drzewa
            ilekrawedzi=0;  //brak zapisanych krawedzi
            wdrzewie=new int[rozmiar];
            for(int i=0; i<rozmiar; i++)
            {
                wdrzewie[i]=0;
            }
                        //rozpoczecie drzewa od wezla 0
            wdrzewie[0]=1;
            dodajKrawedzieWezla(0); //dodaje jego krawedzie jako poczatkowy zbior dostepnych
    }

    ~prim()
    {
        delete tmp;
        delete drzewo;
        delete wdrzewie;
        ilekrawedzi=0;
        rozmiar=0;
        iloscwezlow=0;
    }
};

struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}


struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Tworzy kolejke dodwanych list o rozmiarze V
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Inicjuje kazda liste dodwania jako pusta
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}


void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    // Dodaje kwrawedz z src do dest na poczatek
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Dopoki graf jest nieskierowany, dodaje krawedz z dest do src
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// minimalny kopiec wezlow
struct MinHeapNode {
    int v;
    int key;
};

// minimalny kopiec
struct MinHeap {
    int size; // ilosc kopcow
    int capacity; //ilosc w kopcu
    int* pos; // pomocnicza do decrasekey
    struct MinHeapNode** array;
};


struct MinHeapNode* newMinHeapNode(int v, int key)
{
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key = key;
    return minHeapNode;
}


struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// podmiana wezlow
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        // zmiana wezlow
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        // zmiana pozycji
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // zmaiana wezlow
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// sprawdza czy jest pusty
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

// wyciaga kopiec z najnizsza wartoscia
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    // przechowywanie rootu
    struct MinHeapNode* root = minHeap->array[0];

    // zamiana rootu z ostatnim wezlem
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // pokazujee pozycje ostatniego wezla
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // zmniejsza wielkosc kopca
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}


void decreaseKey(struct MinHeap* minHeap, int v, int key)
{

    int i = minHeap->pos[v];


    minHeap->array[i]->key = key;

    //  a O(Logn)
    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {

        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);


        i = (i - 1) / 2;
    }
}

//sprawdza czy najmniejszy
bool isInMinHeap(struct MinHeap* minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

//do pokazywania polaczen wezlow
void printArr(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
        printf("%d - %d\n", arr[i], i);
}


void PrimMST(struct Graph* graph)
{
    int V = graph->V;
    int parent[V];
    int key[V];

    struct MinHeap* minHeap = createMinHeap(V);


    for (int v = 1; v < V; ++v) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }


    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0] = 0;

    minHeap->size = V;

    while (!isEmpty(minHeap)) {

        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;


        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;


            if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) {
                key[v] = pCrawl->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

}


#endif
