#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include "sudoku.h"


class Sudoku_solver: public Sudoku
{
    public:
        Sudoku_solver();                //costruttore di default
        Sudoku_solver(unsigned int);    //costruttore con parametri
        Sudoku_solver(Sudoku_solver &); //costruttore copia
        void solve();                   //metodo che risolve il sudoku
        void partial_solve();           //metodo che trova le caselle dove può andare solamente un numero
        unsigned get_numero_soluzioni();//metodo che restituisce il numero di soluzioni trovate
        unsigned int get_conta_cicli(); //metodo che restituisce il numero di cicle di backtracking effettuati
        ~Sudoku_solver();               //distruttore

    private:
        bool solver(unsigned int );     //metodo chiamato dal metodo solve (non deve essere accessibile direttamente dall'utente)
        unsigned int conta_cicli;       //attibuto che conta i cicli di backtracking
        unsigned int numero_soluzioni;  //attibuto che conta il numero di soluzioni trovate
        void set_matrice(std::vector<std::vector<unsigned int> > &); //metodo utilizzato dal metodo partial solve
        void prelab_riga(std::vector<std::vector<unsigned int> > ,unsigned int ,unsigned int ,unsigned int &); //metodo utilizzato dal metodo partial solve
        void prelab_colonna(std::vector<std::vector<unsigned int> >,unsigned int , unsigned int ,unsigned int &); //metodo utilizzato dal metodo partial solve
};

#endif // SUDOKU_SOLVER_H
