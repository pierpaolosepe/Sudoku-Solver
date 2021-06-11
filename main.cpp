#include <iostream>
#include "sudoku.h"
#include "sudoku_solver.h"
#include "Griglie.h"
#include "sudoku_letterale.h"
#include "sudoku_letterale_solver.h"
#include <cstdio>

int main()
{

    std::cout<<""<<std::endl;
    std::cout<<"                   _____________________"<<std::endl;
    std::cout<<"                  |                     |"<<std::endl;
    std::cout<<"                  |   N-SUDOKU SOLVER   |"<<std::endl;
    std::cout<<"                  |_____________________|"<<std::endl<<std::endl;
    std::cout<<" - IL SEGUENTE PROGRAMMA PERMETTE DI RISOLVERE SUDOKU N*N ( N >= 2 )."<<std::endl;
    std::cout<<" - IL PROGRAMMA CALCOLA ANCHE SE LA SOLUZIONE E' UNICA O SE ESISTONO DIVERSE SOLUZIONI"<<std::endl;
    std::cout<<" - ALLO STESSO SUDOKU."<<std::endl<<std::endl<<std::endl;
    int n;
    do{
    std::cout <<" - INSERISCI IL NUMERO DI RIGHE E COLONNE :"<<std::endl;
    std::cout<<" -> ";
    std::cin>>n;
    }while(n<2);
    std::cout<<std::endl;
    std::cout<<" - SCEGLI IL TIPO DI SUDOKU DA RISOLVERE"<<std::endl<<std::endl;
    std::cout<<" - [1] SUDOKU NUMERICO"<<std::endl<<std::endl;
    std::cout<<" - [2] SUDOKU LETTERALE"<<std::endl<<std::endl;
    std::cout<<" -> ";
    int scelta;
    std::cin>>scelta;
    std::cout<<std::endl;
    switch(scelta)
    {
        case 1: {
                Sudoku_solver b(n);
                std::cout<<" - SCEGLI COSA FARE"<<std::endl<<std::endl;
                std::cout<<" - [1] INSERISCI QUALCHE NUMERO"<<std::endl<<std::endl;
                std::cout<<" - [2] INSERISCI TUTTI I NUMERI"<<std::endl<<std::endl;
                std::cout<<" - [3] GENERA UN SUDOKU CASUALMENTE"<<std::endl<<std::endl;
                std::cout<<" -> ";
                std::cin>>scelta;
                switch(scelta)
                {
                    case 1:
                    while(scelta!=0){
                        std::cout<<std::endl;
                        std::cout<<" - RIGA    : ";
                        int riga;
                        std::cin>>riga;
                        std::cout<<std::endl;
                        std::cout<<" - COLONNA : ";
                        int colonna;
                        std::cin>>colonna;
                        std::cout<<std::endl;
                        std::cout<<" - NUMERO  : ";
                        int numero;
                        std::cin>>numero;
                        std::cout<<std::endl;
                        b.insert_elemento(numero,riga-1,colonna-1);
                        b.stampa();
                        std::cout<<" - [1]: INSERISCI UN ALTRO NUMERO"<<std::endl<<std::endl;
                        std::cout<<" - [0]: FINE INSERIMENTO"<<std::endl<<std::endl;
                        std::cout<<" ->";
                        std::cin>>scelta;
                    }
                    break;

                case 2:
                    for(int i=0;i<n*n;i++)
                            for(int j=0;j<n*n;j++){
                                std::cout<<" - RIGA    : "<<i+1;
                                std::cout<<std::endl;
                                std::cout<<" - COLONNA : "<<j+1;
                                std::cout<<std::endl;
                                std::cout<<" - NUMERO  : ";
                                int numero;
                                std::cin>>numero;
                                std::cout<<std::endl;
                                b.insert_elemento(numero,i,j);
                                b.stampa();

                            }
                        std::cout<<" - [1]: CORREGGI UN NUMERO"<<std::endl<<std::endl;
                        std::cout<<" - [0]: FINE INSERIMENTO"<<std::endl<<std::endl;
                        std::cout<<" ->";
                        std::cin>>scelta;
                        while(scelta!=0){
                        std::cout<<" - RIGA    : ";
                        int riga;
                        std::cin>>riga;
                        std::cout<<std::endl;
                        std::cout<<" - COLONNA : ";
                        int colonna;
                        std::cin>>colonna;
                        std::cout<<std::endl;
                        std::cout<<" - NUMERO  :";
                        int numero;
                        std::cin>>numero;
                        std::cout<<std::endl;
                        b.insert_elemento(numero,riga-1,colonna-1);
                        b.stampa();
                        std::cout<<" - [1]: CORREGGI UN NUMERO"<<std::endl<<std::endl;
                        std::cout<<" - [0]: FINE INSERIMENTO"<<std::endl<<std::endl;
                        std::cout<<"-->";
                        std::cin>>scelta;
                        }
                        break;

                case 3: b.genera_sudoku();
                        b.stampa();
                        break;
                }
                std::cout<<std::endl;
                std::cout<<" - UTILIZZARE LA PRELABORAZIONE DEI DATI ?"<<std::endl;
                std::cout<<" - (CONSENTE DI RISPARMIARE CICLI DI BACKTRACKING TROVANDO LE SOLUZIONI OVVIE)"<<std::endl<<std::endl;
                std::cout<<" - [1] RISOLVI SUDOKU ( SENZA PRELABORAZIONE )"<<std::endl<<std::endl;
                std::cout<<" - [2] RISOLVI SUDOKU ( CON PRELABORAZIONE )"<<std::endl<<std::endl;
                std::cout<<" - [3] RISOLVI SUDOKU ( CON ENTRAMBI I METODI )"<<std::endl<<std::endl;
                std::cout<<" -> ";
                std::cin>>scelta;
                switch(scelta)
                {
                    case 1:{b.solve();
                            std::cout<<" - NUMERO DI SOLUZIONI TROVATE  : "<<b.get_numero_soluzioni()<<std::endl;
                            std::cout<<" - NUMERO DI CICLI BACKTRACKING : "<<b.get_conta_cicli()<<std::endl;
                            break;
                    }

                    case 2: {b.partial_solve();
                            std::cout<<" - SUDOKU DOPO LA PRELABORAZIONE DEI DATI"<<std::endl;
                            b.stampa();
                            fflush(stdin);
                            std::cout<<" - PREMI INVIO PER CONTINUARE . . . ";
                            char pausa=getchar();
                            b.solve();
                            std::cout<<" - NUMERO DI SOLUZIONI TROVATE  : "<<b.get_numero_soluzioni()<<std::endl;
                            std::cout<<" - NUMERO DI CICLI BACKTRACKING : "<<b.get_conta_cicli()<<std::endl;
                            break;
                    }

                    case 3: {Sudoku_solver c=b;
                            b.solve();
                            std::cout<<" - SUDOKU PRIMA DELLA PRELABORAZIONE DEI DATI"<<std::endl;
                            c.stampa();
                            c.partial_solve();
                            std::cout<<" - SUDOKU DOPO LA PRELABORAZIONE DEI DATI"<<std::endl;
                            c.stampa();
                            fflush(stdin);
                            std::cout<<" - PREMI INVIO PER CONTINUARE . . . ";
                            char pausa=getchar();
                            c.solve();
                            std::cout<<" - NUMERO DI SOLUZIONI TROVATE  (SENZA PRELABORAZIONE)  : "<<b.get_numero_soluzioni()<<std::endl;
                            std::cout<<" - NUMERO DI CICLI BACKTRACKING (SENZA PRELABORAZIONE)  : "<<b.get_conta_cicli()<<std::endl;
                            std::cout<<" - NUMERO DI SOLUZIONI TROVATE  (CON PRELABORAZIONE)    : "<<c.get_numero_soluzioni()<<std::endl;
                            std::cout<<" - NUMERO DI CICLI BACKTRACKING (CON PRELABORAZIONE)    : "<<c.get_conta_cicli()<<std::endl;
                            break;
                    }
                }


        }break;


        case 2: {
                Sudoku_letterale_solver d(n);
                std::cout<<" - SCEGLI COSA FARE"<<std::endl<<std::endl;
                std::cout<<" - [1] INSERISCI QUALCHE LETTERA"<<std::endl<<std::endl;
                std::cout<<" - [2] INSERISCI TUTTE LE LETTERE"<<std::endl<<std::endl;
                std::cout<<" - [3] GENERA UN SUDOKU CASUALMENTE"<<std::endl<<std::endl;
                std::cout<<" -> ";
                std::cin>>scelta;
                switch(scelta){
                case 1:
                {
                    while(scelta!=0){
                        std::cout<<std::endl;
                        std::cout<<" - RIGA    :";
                        int riga;
                        std::cin>>riga;
                        std::cout<<std::endl;
                        std::cout<<" - COLONNA :";
                        int colonna;
                        std::cin>>colonna;
                        std::cout<<std::endl;
                        std::cout<<" - LETTERA :";
                        char lettera;
                        std::cin>>lettera;
                        std::cout<<std::endl;
                        d.insert_elemento(lettera,riga-1,colonna-1);
                        d.stampa();
                        std::cout<<" - [1]: INSERISCI UN' ALTRA LETTERA"<<std::endl<<std::endl;
                        std::cout<<" - [0]: FINE INSERIMENTO"<<std::endl<<std::endl;
                        std::cout<<" ->";
                        std::cin>>scelta;
                    }
                }break;

                case 2:for(int i=0;i<n*n;i++)
                            for(int j=0;j<n*n;j++){
                                std::cout<<" - RIGA    : "<<i+1<<std::endl;;
                                std::cout<<" - COLONNA : "<<j+1<<std::endl;;
                                std::cout<<" - LETTERA : ";
                                char lettera;
                                std::cin>>lettera;
                                d.insert_elemento(lettera,i,j);
                                d.stampa();
                            }
                        std::cout<<" - [1]: CORREGGI UNA LETTERA"<<std::endl<<std::endl;
                        std::cout<<" - [0]: FINE INSERIMENTO"<<std::endl<<std::endl;
                        std::cout<<" ->";
                        std::cin>>scelta;
                        while(scelta!=0){
                        std::cout<<" - RIGA    :";
                        int riga;
                        std::cin>>riga;
                        std::cout<<std::endl;
                        std::cout<<" - COLONNA :";
                        int colonna;
                        std::cin>>colonna;
                        std::cout<<std::endl;
                        std::cout<<" - LETTERA :";
                        char lettera;
                        std::cin>>lettera;
                        std::cout<<std::endl;
                        d.insert_elemento(lettera,riga-1,colonna-1);
                        d.stampa();
                        std::cout<<" - [1]: CORREGGI UNA LETTERA"<<std::endl<<std::endl;
                        std::cout<<" - [0]: FINE INSERIMENTO"<<std::endl<<std::endl;
                        std::cout<<" ->";
                        std::cin>>scelta;
                    }break;

                case 3:{
                    d.genera_sudoku();
                    d.stampa();
                }break;
                }
                std::cout<<std::endl;
                std::cout<<" - UTILIZZARE LA PRELABORAZIONE DEI DATI ?"<<std::endl;
                std::cout<<" - (CONSENTE DI RISPARMIARE CICLI DI BACKTRACKING TROVANDO LE SOLUZIONI OVVIE)"<<std::endl<<std::endl;
                std::cout<<" - [1] RISOLVI SUDOKU ( SENZA PRELABORAZIONE )"<<std::endl<<std::endl;
                std::cout<<" - [2] RISOLVI SUDOKU ( CON PRELABORAZIONE )"<<std::endl<<std::endl;
                std::cout<<" - [3] RISOLVI SUDOKU ( CON ENTRAMBI I METODI )"<<std::endl<<std::endl;
                std::cout<<" -> ";
                std::cin>>scelta;
                switch(scelta)
                {
                    case 1:d.solve();

                            std::cout<<" - NUMERO DI SOLUZIONI TROVATE  : "<<d.get_numero_soluzioni()<<std::endl;
                            std::cout<<" - NUMERO DI CICLI BACKTRACKING : "<<d.get_conta_cicli()<<std::endl;
                            break;
                    case 2: {d.partial_solve();
                            std::cout<<" - SUDOKU DOPO LA PRELABORAZIONE DEI DATI"<<std::endl;
                            d.stampa();
                            fflush(stdin);
                            std::cout<<" - PREMI INVIO PER CONTINUARE . . . ";
                            char pausa=getchar();
                            d.solve();
                            std::cout<<" - NUMERO DI SOLUZIONI TROVATE  : "<<d.get_numero_soluzioni()<<std::endl;
                            std::cout<<" - NUMERO DI CICLI BACKTRACKING : "<<d.get_conta_cicli()<<std::endl;
                            break;
                    }
                    case 3: {Sudoku_letterale_solver e=d;
                            d.solve();
                            std::cout<<" - SUDOKU PRIMA DELLA PRELABORAZIONE DEI DATI"<<std::endl;
                            e.stampa();
                            e.partial_solve();
                            std::cout<<" - SUDOKU DOPO LA PRELABORAZIONE DEI DATI"<<std::endl;
                            e.stampa();
                            fflush(stdin);
                            std::cout<<" - PREMI INVIO PER CONTINUARE . . . ";
                            char pausa=getchar();
                            e.solve();
                            std::cout<<" - NUMERO DI SOLUZIONI TROVATE  (SENZA PRELABORAZIONE)  : "<<d.get_numero_soluzioni()<<std::endl;
                            std::cout<<" - NUMERO DI CICLI BACKTRACKING (SENZA PRELABORAZIONE)  : "<<d.get_conta_cicli()<<std::endl;
                            std::cout<<" - NUMERO DI SOLUZIONI TROVATE  (CON PRELABORAZIONE)    : "<<e.get_numero_soluzioni()<<std::endl;
                            std::cout<<" - NUMERO DI CICLI BACKTRACKING (CON PRELABORAZIONE)    : "<<e.get_conta_cicli()<<std::endl;
                            break;}
                }

        }


    }
    return 0;
}
