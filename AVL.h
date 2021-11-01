#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

template <typename T>
class NodoAVL
{
public:
    T mp_dato;
    NodoAVL<T> *mp_son[3];
    short int FE;
    template <typename U>
    friend class AVL_Tree;

public:
    NodoAVL()
    {
        mp_dato = 0;
        mp_son[0] = NULL;
        mp_son[1] = NULL;
        mp_son[2] = NULL;
        FE = 0;
    }
    NodoAVL(T d)
    {
        mp_dato = d;
        mp_son[0] = NULL;
        mp_son[1] = NULL;
        mp_son[2] = NULL;
        FE = 0;
    }
};

template <typename T>
class AVL_Tree
{
public:
    NodoAVL<T> *mp_root;
    void printHelper(NodoAVL<T> *p)
    {
        if (!p)
            return;
        cout << "\t" << p << "    : " << p->mp_dato << "  con FE  " << p->FE << endl;
        cout << p->mp_son[0] << "\t\t" << p->mp_son[1] << endl;
        printHelper(p->mp_son[0]);
        //cout<<p->mp_dato<<endl;
        printHelper(p->mp_son[1]);
    }
    bool insertHelper(T d, NodoAVL<T> *&p, NodoAVL<T> *padre)
    {
        if (!p)
        {
            //cout<<"Insertando "<<d<<endl;
            p = new NodoAVL<T>(d);
            if (padre)
            {
                p->mp_son[2] = padre;
                NodoAVL<T> **aux = &p;
                do
                {
                    aux = &((*aux)->mp_son[2]);
                    if (p->mp_dato < (*aux)->mp_dato)
                    {
                        (*aux)->FE -= 1;
                    }
                    else
                    {
                        (*aux)->FE += 1;
                    }
                    switch ((*aux)->FE)
                    {
                    case 0:
                        return true;
                    case 2:
                        if ((*aux)->mp_son[1]->FE == 1)
                            rotacionDerecha(*aux);
                        else
                        {
                            // rotacionIzquierda((*aux)->mp_son[1]);
                            // rotacionDerecha((*aux)->mp_son[2]);
                            rightRotate(*aux);
                        }
                        return true;
                    case -2:
                        if ((*aux)->mp_son[0]->FE == -1)
                            rotacionIzquierda(*aux);
                        else
                        {
                            leftRotate(*aux);
                            // rotacionDerecha((*aux)->mp_son[0]);
                            // rotacionIzquierda((*aux)->mp_son[2]);
                        }
                        return true;
                    }
                } while (((*aux)->FE == 1 || (*aux)->FE == -1) && (*aux)->mp_son[2] != NULL);
            }
            return true;
        }
        padre = p;
        if (p->mp_dato == d)
            return false;
        return insertHelper(d, p->mp_son[p->mp_dato < d], padre);
    }

public:
    AVL_Tree()
    {
        mp_root = NULL;
    }

    void rotacionDerecha(NodoAVL<T> *p)
    {
        cout << "En Rotacion derecha con " << p->mp_dato << endl;
        NodoAVL<T> *q = p->mp_son[1];
        q->mp_son[2] = p->mp_son[2];
        p->mp_son[1] = q->mp_son[0];
        if (q->mp_son[0])
            (q->mp_son[0])->mp_son[2] = p;
        q->mp_son[0] = p;
        p->mp_son[2] = q;
        switch (q->FE)
        {
        case 0:
            p->FE = 0; //arreglar
            q->FE = 1;
            break;
        case 1:
            q->FE = 0;
            p->FE = 0;
            break;
        }
        if (q->mp_son[2] == NULL)
        {
            mp_root = q;
        }
        else
        {
            NodoAVL<T> *padre = q->mp_son[2];
            padre->mp_son[p->mp_dato > padre->mp_dato] = q;
        }
    }

    void rotacionIzquierda(NodoAVL<T> *p)
    {
        cout << "En Rotacion izquierda con " << p->mp_dato << endl;
        NodoAVL<T> *q = p->mp_son[0];
        q->mp_son[2] = p->mp_son[2];
        p->mp_son[0] = q->mp_son[1];
        if (q->mp_son[1])
            (q->mp_son[1])->mp_son[2] = p;
        q->mp_son[1] = p;
        p->mp_son[2] = q;
        switch (q->FE)
        {
        case 0:
            p->FE = 0; //arreglar
            q->FE = 1;
            break;
        case -1:
            q->FE = 0;
            p->FE = 0;
            break;
        }
        if (q->mp_son[2] == NULL)
        {
            mp_root = q;
        }
        else
        {
            NodoAVL<T> *padre = q->mp_son[2];
            padre->mp_son[p->mp_dato > padre->mp_dato] = q;
        }
    }

    bool insert(T d)
    {
        return insertHelper(d, mp_root, NULL);
    }
    void print()
    {
        printHelper(mp_root);
    }
    void leftRotate(NodoAVL<T> *p)
    {

        cout << "En rotacion izquierda con " << p->mp_dato << endl;
        NodoAVL<T> *q = p->mp_son[0];
        NodoAVL<T> *r = q->mp_son[1];
        r->mp_son[2] = p->mp_son[2];

        q->mp_son[1] = r->mp_son[0];
        if (r->mp_son[0])
            r->mp_son[0]->mp_son[2] = q;

        p->mp_son[0] = r->mp_son[1];
        if (r->mp_son[1])
            r->mp_son[1]->mp_son[2] = p;

        r->mp_son[0] = q;
        q->mp_son[2] = r;

        r->mp_son[1] = p;
        p->mp_son[2] = r;

        switch (r->FE)
        {
        case 0:
            p->FE = 0;
            q->FE = 0;
            break;
        case 1:
            p->FE = 0;
            q->FE = -1;
            break;
        case -1:
            p->FE = 1;
            q->FE = 0;
            break;
        }
        if (r->mp_son[2] == NULL)
        {
            mp_root = r;
        }
        else
        {
            NodoAVL<T> *padre = r->mp_son[2];
            padre->mp_son[p->mp_dato > padre->mp_dato] = r;
        }
    }

    void rightRotate(NodoAVL<T> *p)
    {

        cout << "En rotacion derecha con " << p->mp_dato << endl;
        NodoAVL<T> *q = p->mp_son[1];
        NodoAVL<T> *r = q->mp_son[0];
        r->mp_son[2] = p->mp_son[2];

        q->mp_son[0] = r->mp_son[1];
        if (r->mp_son[1])
            r->mp_son[1]->mp_son[2] = q;

        p->mp_son[1] = r->mp_son[0];
        if (r->mp_son[0])
            r->mp_son[0]->mp_son[2] = p;

        r->mp_son[1] = q;
        q->mp_son[2] = r;

        r->mp_son[0] = p;
        p->mp_son[2] = r;

        switch (r->FE)
        {
        case 0:
            p->FE = 0;
            q->FE = 0;
            break;
        case 1:
            p->FE = -1;
            q->FE = 0;
            break;
        case -1:
            p->FE = 0;
            q->FE = 1;
            break;
        }
        if (r->mp_son[2] == NULL)
        {
            mp_root = r;
        }
        else
        {
            NodoAVL<T> *padre = r->mp_son[2];
            padre->mp_son[p->mp_dato > padre->mp_dato] = r;
        }
    }
    NodoAVL<T> minimum()
    {
        NodoAVL<T> *min = mp_root;
        while (min->mp_son[0])
        {
            min = min->mp_son[0];
        }
        return min;
    }
    void Remove(T x)
    {
        NodoAVL<T> *aux = mp_root;
        while (aux != NULL)
        {
            if (aux->mp_dato == x)
            {
                break;
            }
            aux = aux->mp_son[x > (aux->mp_dato)];
        }
        if (aux != NULL)
        {
            if (aux->mp_son[0] && aux->mp_son[1])
            {
                NodoAVL<T> *aux2 = aux->mp_son[1];
                while (aux2->mp_son[0] != NULL)
                {
                    aux2 = aux2->mp_son[0];
                }
                aux->mp_dato = aux2->mp_dato;
                if (aux2->mp_son[1])
                {
                    NodoAVL<T> *aux3 = aux2;
                    aux2 = aux2->mp_son[2];
                    aux2->mp_son[aux2->mp_dato < aux3->mp_dato] = aux3->mp_son[1];
                    aux3 = aux3->mp_son[1];
                    aux3->mp_son[2] = aux2;
                    
                }
                else
                {
                    NodoAVL<T> *aux3 = aux2;
                    aux2 = aux2->mp_son[2];
                    aux2->mp_son[aux2->mp_dato < aux3->mp_dato] = NULL;
                }
                NodoAVL<T> *aux3 = aux;
                do
                {
                    aux3 = aux3->mp_son[2];
                    if (x < aux3->mp_dato)
                    {
                        aux3->FE += 1;
                    }
                    else
                    {
                        aux3->FE -= 1;
                    }
                    switch (aux3->FE)
                    {
                    case 0:
                        return;
                    case 2:
                        if ((aux3)->mp_son[1]->FE == 1)
                            rotacionDerecha(aux3);
                        else
                        {
                            rightRotate(aux3);
                        }
                        return;
                    case -2:
                        if ((aux3)->mp_son[0]->FE == -1)
                            rotacionIzquierda(aux3);
                        else
                        {
                            leftRotate(aux3);
                        }
                        return ;
                    }
                } while (((aux3)->FE == 1 || (aux3)->FE == -1) && (aux3)->mp_son[2] != NULL);
            }
            else if (aux->mp_son[0] != NULL)
            {
                NodoAVL<T> *aux2 = aux;
                aux = aux->mp_son[2];
                aux->mp_son[aux->mp_dato < aux2->mp_dato] = aux2->mp_son[0];
                aux2 = aux2->mp_son[0];
                aux2->mp_son[2] = aux;

                NodoAVL<T> *aux3 = aux2;
                do
                {
                    aux3 = aux3->mp_son[2];
                    if (x < aux3->mp_dato)
                    {
                        aux3->FE += 1;
                    }
                    else
                    {
                        aux3->FE -= 1;
                    }
                    switch (aux3->FE)
                    {
                    case 0:
                        return;
                    case 2:
                        if ((aux3)->mp_son[1]->FE == 1)
                            rotacionDerecha(aux3);
                        else
                        {
                            rightRotate(aux3);
                        }
                        return;
                    case -2:
                        if ((aux3)->mp_son[0]->FE == -1)
                            rotacionIzquierda(aux3);
                        else
                        {
                            leftRotate(aux3);
                        }
                        return ;
                    }
                } while (((aux3)->FE == 1 || (aux3)->FE == -1) && (aux3)->mp_son[2] != NULL);
            }
            else if (aux->mp_son[1] != NULL)
            {
                NodoAVL<T> *aux2 = aux;
                aux = aux->mp_son[2];
                aux->mp_son[aux->mp_dato < aux2->mp_dato] = aux2->mp_son[1];
                aux2 = aux2->mp_son[1];
                aux2->mp_son[2] = aux;

                NodoAVL<T> *aux3 = aux2;
                do
                {
                    aux3 = aux3->mp_son[2];
                    if (x < aux3->mp_dato)
                    {
                        aux3->FE += 1;
                    }
                    else
                    {
                        aux3->FE -= 1;
                    }
                    switch (aux3->FE)
                    {
                    case 0:
                        return;
                    case 2:
                        if ((aux3)->mp_son[1]->FE == 1)
                            rotacionDerecha(aux3);
                        else
                        {
                            rightRotate(aux3);
                        }
                        return;
                    case -2:
                        if ((aux3)->mp_son[0]->FE == -1)
                            rotacionIzquierda(aux3);
                        else
                        {
                            leftRotate(aux3);
                        }
                        return ;
                    }
                } while (((aux3)->FE == 1 || (aux3)->FE == -1) && (aux3)->mp_son[2] != NULL);
            }
            else
            {
                cout<<"Entre aqui"<<endl;
                NodoAVL<T> *aux2 = aux;
                aux = aux->mp_son[2];
                aux->mp_son[aux->mp_dato < aux2->mp_dato] = NULL;
                NodoAVL<T> *aux3 = aux2;
                do
                {
                    aux3 = aux3->mp_son[2];
                    if (x < aux3->mp_dato)
                    {
                        aux3->FE += 1;
                    }
                    else
                    {
                        aux3->FE -= 1;
                    }
                    switch ((aux3)->FE)
                    {
                    case 0:
                        return;
                    case 2:
                        if ((aux3)->mp_son[1]->FE == 1)
                            rotacionDerecha(aux3);
                        else
                        {
                            rightRotate(aux3);
                        }
                        return;
                    case -2:
                        if ((aux3)->mp_son[0]->FE == -1)
                            rotacionIzquierda(aux3);
                        else
                        {
                            leftRotate(aux3);
                        }
                        return ;
                    }
                } while (((aux3)->FE == 1 || (aux3)->FE == -1) && (aux3)->mp_son[2] != NULL);
            }
        }
    }
};