#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <vector>
#include "griglie.h"

class Sudoku: public Griglie
{
    public:
        Sudoku();                       //costruttore di default
        Sudoku(unsigned int);           //costruttore con parametri
        Sudoku(Sudoku &);               //costruttore copia
        unsigned int get_n();           //metodo che restituisce il numero di righe e colonne del sudoku
        void stampa();                  //metodo che stampa il sudoku
        bool check_elemento(unsigned int,unsigned int,unsigned int);
                                        //metodo che verifica se un numero può stare in una determinata posizione
        bool check_sudoku();            //verifica la correttezza del sudoku creato
        void genera_sudoku();           //genera un sudoku casualmente che ha almeno una soluzione
        void insert_elemento(unsigned int,unsigned int,unsigned int);
                                        //inserisce l'elemento nella posizione desiderata
        ~Sudoku();                      //Distruttore
    protected:
        std::vector<std::vector<unsigned int> > square;//matrice di interi che contiene i numeri del sudoku
        std::vector<std::vector<bool> > lock_square;   //matrice bool. Se una posizione è settata a true allora l'elemento
                                                       // non può essere modificato.
        unsigned int n;                                //Il numero di righe e colonne del sudoku
        unsigned int range_numeri;                     //attibuto che contiene il numero massimo che può essere inserito
        unsigned int celle_totali;                     //il numero di celle del sudoku

    private:
        bool controll_sudoku(unsigned int);//metodo chiamato dal metodo genera_sudoku() che verifica l'esistenza di una soluzione

};

#endif // SUDOKU_H
