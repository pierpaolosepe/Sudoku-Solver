#ifndef GRIGLIE_H
#define GRIGLIE_H

class Griglie
{
    public:
        virtual unsigned get_n()=0;
        virtual void stampa()=0;
        virtual bool check_sudoku()=0;
        virtual void genera_sudoku()=0;

};

#endif // GRIGLIE_H
