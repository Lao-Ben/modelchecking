#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <iostream>
#include <fstream>
#include "Node.h"
#include "BDD.h"

class Fonction
{
    public:
        Fonction(int n);
        virtual ~Fonction();
        int getSize();
        void setSize(int n);
        int queen();
        int knight();
    protected:
    private:
        int size;
};

#endif // FONCTION_H_INCLUDED
