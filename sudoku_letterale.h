#ifndef SUDOKU_LETTERALE_H
#define SUDOKU_LETTERALE_H
#include "Griglie.h"
#include <vector>

class Sudoku_letterale: public Griglie
{
    public:
        Sudoku_letterale();                           //Costruttore di default
        Sudoku_letterale(unsigned int);               //Costruttore con parametri
        Sudoku_letterale(Sudoku_letterale &);         //Costruttore copia
        unsigned int get_n();                         //Restituisci n il numero di righe e colonne
        void stampa();                                //Stampa il sudoku
        bool check_elemento(unsigned int,unsigned int,char);//Verifica se un elemento pu� essere inserito in una posizione
        bool check_sudoku();                          //Verifica se il sudoku inserito rispetta le propriet�
        void genera_sudoku();                         //Genera un sudoku casualmente che abbia almeno una soluzione
        void insert_elemento(char,unsigned int,unsigned int);//Inserisci elemento in una determinata posizione
        ~Sudoku_letterale();                          //Distuttore
    protected:
        std::vector<std::vector<char> > square;       //Matrice di char che rappresenta il sudoku
        std::vector<std::vector<bool> > lock_square;  //Matrice di bool. Se la posizione x,y � settata a TRUE allora
                                                      //l'elemento che si trova nella posizione x,y di square non
                                                      //pu� essere modificato.
        unsigned int n;                               // Il numero di righe e colonne di ogni cella
        unsigned int range_lettere;                   //La lettera pi� grande che pu� essere inserita
        unsigned int celle_totali;
    private:
        bool controll_sudoku(unsigned int);  //Metodo che controlla che il sudoku generato da genera_sudoku abbia
                                             //almeno una soluzione
};

#endif // SUDOKU_LETTERALE_H
