#include<iostream>
using namespace std;

template<typename T>
class NodoAVL{
    private:
        T mp_dato;
        NodoAVL<T>* mp_son[3];
        short int FE;
        template<typename U>friend class AVL_Tree;
    public:
        NodoAVL(){
            mp_dato=0;
            mp_son[0]=NULL;
            mp_son[1]=NULL;
            mp_son[2]=NULL;
            FE=0;
        }
        NodoAVL(T d){
            mp_dato=d;
            mp_son[0]=NULL;
            mp_son[1]=NULL;
            mp_son[2]=NULL;
            FE=0;
        }
};

template<typename T>
class AVL_Tree{
    private:
        NodoAVL<T> *mp_root;
        void printHelper(NodoAVL<T>* p){
            if(!p) return;
            printHelper(p->mp_son[0]);
            cout<<p->mp_dato<<endl;
            printHelper(p->mp_son[1]);
        }
        bool insertHelper(T d, NodoAVL<T>*&p,NodoAVL<T>* padre){
            if(!p){
                p=new NodoAVL<T>(d);
                p->FE=0;
                if(p->mp_son[2]){
                    p->mp_son[2]=padre;
                    NodoAVL<T>* aux=p;
                    do
                    {
                        aux=aux->mp_son[2];
                        if(p->mp_dato<aux->mp_dato){
                            aux->FE-=1;
                        }
                        else{
                            aux->FE+=1;
                        }

                        if(aux->FE==2){
                            rightRotate(aux);
                        }
                        else if(aux->FE==-2){
                            leftRotate(aux);
                        }
                    }while (aux->FE==1||aux->FE==-1);
                
                }
                return true;
            }
            padre=p;
            if (p->mp_dato==d) return false;
            return insertHelper(d, p->mp_son[p->mp_dato<d],padre);
        }
    public:
        AVL_Tree(){
            mp_root=NULL;
        }
        void leftRotate(NodoAVL<T>* &p){
            NodoAVL<T>*q,*r;
            q=p->mp_son[0];
            r=q->mp_son[1];

            q->mp_son[1]=r->mp_son[0];
            p->mp_son[0]=r->mp_son[1];

            r->mp_son[0]=q;
            r->mp_son[1]=p;

            switch(r->FE){
                case 0:
                    p->FE=0;
                    q->FE=0;
                    break;
                case 1:
                    p->FE=0;
                    q->FE=-1;
                    r->FE=1;
                    break;
                case -1:
                    p->FE=1;
                    q->FE=0;
                    r->FE=-1;
                    break;
            }
            p=r;
        }

        void rightRotate(NodoAVL<T>* &p){
            NodoAVL<T> *q,*r;
            q=p->mp_son[1];
            r=q->mp_son[0];

            p->mp_son[1]=r->mp_son[0];
            q->mp_son[0]=r->mp_son[1];

            r->mp_son[0]=p;
            r->mp_son[1]=q;

            switch(r->FE){
                case 0:
                    p->FE=0;
                    q->FE=0;
                    break;
                case 1:
                    p->FE=-1;
                    q->FE=0;
                    r->FE=1;
                    break;
                case -1:
                    p->FE=0;
                    q->FE=1;
                    r->FE=-1;
                    break;
            }
            p=r;
        }

        void doubleRotate(NodoAVL<T>*& p){
            NodoAVL<T>*q;
            q=p->mp_son[1];
            p->mp_son[1]=q->mp_son[0];
            q->mp_son[0]=p;
            p=q;
            // switch(q->FE){
            //     case 0:
            //         p->FE=0;
            //         break;
            //     case 1:
            //         p->FE=-1;
            //         break;
            //     case -1:
            //         p->FE=0;
            //         break;
            // }
        }

        bool insert(T d){
            return insertHelper(d,mp_root,NULL);
        }
        void print(){
            printHelper(mp_root);
        }
};