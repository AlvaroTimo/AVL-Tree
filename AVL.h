#include<iostream>
using namespace std;

template<typename T>
class NodoAVL{
    public:
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
    public:
        NodoAVL<T> *mp_root;
        void printHelper(NodoAVL<T>* p){
            if(!p) return;
            cout<<"\t"<<p<<"    : "<<p->mp_dato<<"  con FE  "<<p->FE<<endl;
            cout<<p->mp_son[0]<<"\t\t"<<p->mp_son[1]<<endl;
            //cout<<p->mp_son[0]->mp_dato<<"\t\t"<<p->mp_son[1]->mp_dato<<endl;
            printHelper(p->mp_son[0]);
            //cout<<p->mp_dato<<endl;
            printHelper(p->mp_son[1]);
        }
        bool insertHelper(T d, NodoAVL<T>*&p,NodoAVL<T>*padre){
            if(!p){
                cout<<"Entre"<<endl;
                p=new NodoAVL<T>(d);
                if(padre){
                    p->mp_son[2]=padre;
                    NodoAVL<T>* aux=p;
                    do
                    {
                        aux=(aux->mp_son[2]);
                        if(p->mp_dato<(aux)->mp_dato){
                            (aux)->FE-=1;
                            //cout<<"Es menor con FE: "<<(aux)->FE<<endl;
                        }
                        else{
                            //cout<<"Es mayor con FE: "<<(aux)->FE<<endl;
                            (aux)->FE+=1;
                        }
                        switch ((aux)->FE){
                            case 2:
                                // printHelper(aux);
                                // cout<<endl<<endl;
                                cout<<"raiz "<<mp_root<<endl;
                                cout<<"padre del padre "<<(padre->mp_son[2])<<endl;
                                cout<<"padre del padre de p"<<(p->mp_son[2]->mp_son[2])<<endl;
                                cout<<"aux "<<aux<<endl;

                                doubleRotate(aux);
                                //rightRotate((aux));
                                return true;
                            case -2:
                                //printHelper(p->mp_son[2]->mp_son[2]);
                                //leftRotate(p->mp_son[2]->mp_son[2]);
                                return true;
                            case 0:
                                return true;
                        }
                    }while (((aux)->FE==1||(aux)->FE==-1)&& (aux)->mp_son[2]!=NULL);
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
        // void leftRotate(NodoAVL<T>* &p){

        //     cout<<"En rotacion izquierda con "<<p<<endl;
        //     NodoAVL<T>*q,*r;

        //     q=p->mp_son[0];
        //     r=q->mp_son[1];
            
                    
        //     q->mp_son[1]=r->mp_son[0];
        //     p->mp_son[0]=r->mp_son[1];
        //     r->mp_son[0]->setPadre(q->mp_son[1]);
        //     r->mp_son[1]->setPadre(p->mp_son[0]);

        //     r->mp_son[0]=q;
        //     r->mp_son[1]=p;
        //     q->setPadre(r->mp_son[0]);
        //     p->setPadre(r->mp_son[1]);

        //     switch(r->FE){
        //         case 0:
        //             p->FE=0;
        //             q->FE=0;
        //             break;
        //         case 1:
        //             p->FE=0;
        //             q->FE=-1;
        //             break;
        //         case -1:
        //             p->FE=1;
        //             q->FE=0;
        //             break;
        //     }
            
        //     cout<<q->mp_son[2]<<" el padre de q es"<<endl;
        //     if(r->mp_son[2]==NULL){
        //         mp_root=r;
        //     }
        //     cout<<endl<<endl;
        //     printHelper(mp_root);
        //     cout<<endl<<endl;

        //     cout<<q->mp_son[2]<<" el padre de q es"<<endl;
        // }

        // void rightRotate(NodoAVL<T>* &p){
        //     cout<<"En rotacion derecha"<<endl;
        //     NodoAVL<T> *q,*r;
        //     q=p->mp_son[1];
        //     r=q->mp_son[0];

        //     p->mp_son[1]=r->mp_son[0];
        //     q->mp_son[0]=r->mp_son[1];

        //     r->mp_son[0]=p;
        //     r->mp_son[1]=q;

        //     switch(r->FE){
        //         case 0:
        //             p->FE=0;
        //             q->FE=0;
        //             break;
        //         case 1:
        //             p->FE=-1;
        //             q->FE=0;
        //             break;
        //         case -1:
        //             p->FE=0;
        //             q->FE=1;
        //             break;
        //     }
        //     p=r;
        // }

        void doubleRotate(NodoAVL<T>*& p){
            cout<<"En Rotacion DD con "<<p->mp_dato<<endl;
            // NodoAVL<T>*q=p->mp_son[1];
            // p->mp_son[1]=q->mp_son[0];
            // q->mp_son[0]=p;
            // p->mp_son[2]=q;
            // switch(q->FE){
            //     case 0:
            //         p->FE=0;
            //         break;
            //     case 1:
            //         q->FE=0;
            //         p->FE=0;
            //         break;
            // }
            // p=q;

            NodoAVL<T> *q = p->mp_son[1];
            p->mp_son[1] = q->mp_son[0];
            q->mp_son[0] = p;

            q->mp_son[2] = p->mp_son[2];
            p->mp_son[2] = q;
           
            if(q->FE == 1) p->FE = q->FE = 0;
            else if(q->FE == 0) p->FE = 1;
           
            p = q;
            //printHelper(p);
            // cout<<endl<<endl;
        }

        bool insert(T d){
            return insertHelper(d,mp_root,NULL);
        }
        void print(){
            printHelper(mp_root);
        }
};