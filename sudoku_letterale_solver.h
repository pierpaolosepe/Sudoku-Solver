#ifndef SUDOKU_LETTERALE_SOLVER_H
#define SUDOKU_LETTERALE_SOLVER_H
#include "sudoku_letterale.h"

class Sudoku_letterale_solver: public Sudoku_letterale
{
    public:
        Sudoku_letterale_solver();                          //Costruttore di default
        Sudoku_letterale_solver(unsigned int);              //Costruttore con parametri
        Sudoku_letterale_solver(Sudoku_letterale_solver &); //Costruttore copia
        void solve();                                       //Metodo che consente di risolvere il sudoku
        unsigned int get_numero_soluzioni();                //Metodo che restituisce il numero di soluzioni
        unsigned int get_conta_cicli();                     //Metodo che restituisce il numero di cicli
        void partial_solve();                               //Metodo che inserisce i numeri sicuri nel sudoku
        ~Sudoku_letterale_solver();                         //Distruttore

    private:
        bool solver(unsigned int );                         //Metodo chiamato dal metodo solver per risolvere il sudoku
        unsigned int conta_cicli;                           //Attributo che conta i cicli di backtracking effettuati
        unsigned int numero_soluzioni;                      //Attributo che conta il numero di soluzioni trovate
        void set_matrice(std::vector<std::vector<unsigned int> > &);//Metodo chiamato dal metodo partial_solve
        void prelab_riga(std::vector<std::vector<unsigned int> > ,unsigned int ,unsigned int ,unsigned int &);  //Metodo chiamato dal metodo partial_solve
        void prelab_colonna(std::vector<std::vector<unsigned int> >,unsigned int ,unsigned int ,unsigned int &);//Metodo chiamato dal metodo partial_solve

};

#endif // SUDOKU_LETTERALE_SOLVER_H
