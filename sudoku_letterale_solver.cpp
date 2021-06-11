#include "sudoku_letterale_solver.h"
#include <iostream>

//Costruttore di default
Sudoku_letterale_solver::Sudoku_letterale_solver()
{
    conta_cicli=0;
    numero_soluzioni=0;

}

//Costruttore con parametri
Sudoku_letterale_solver::Sudoku_letterale_solver(unsigned int numero):Sudoku_letterale(numero)
{
    conta_cicli=0;
    numero_soluzioni=0;

}

//Costruttore copia
Sudoku_letterale_solver::Sudoku_letterale_solver(Sudoku_letterale_solver &a):Sudoku_letterale(a)
{

    conta_cicli=a.conta_cicli;
    numero_soluzioni=a.numero_soluzioni;

}

//Distruttore
Sudoku_letterale_solver::~Sudoku_letterale_solver()
{
    //dtor
}


//Metodo che restituisce il numero di soluzioni del sudoku
unsigned int Sudoku_letterale_solver:: get_numero_soluzioni()
{
    return numero_soluzioni;
}
//Metodo che restituisce il numero di cicli di backtracking effettuati
unsigned int Sudoku_letterale_solver:: get_conta_cicli()
{
    return conta_cicli;
}


void Sudoku_letterale_solver:: solve()
{
    bool solution = solver(0);
}

//metodo che consente di risolvere un sudoku
//L'indice i corrisponde all'i-esima cella se consideriamo la nostra matrice come un vettore
//Inizialmente i vale 0
//y = i%range lettere ci consente di avanzare lungo la colonna
//x= i/range_lettere ci consente di avanzare lungo la riga
//In questo caso risolviamo il sudoku per righe
// valori possibile è un vettore di char che contiene tutti i possibili valori che possono andare in una cella
//Se la prima condizione è verificata significa che il sudoku non è ancora stato risolto
//Se la casella x,y è !=0 e lock_square = true significa che il valore è di default e non deve essere modificato
//Nell'altro caso allora controlliamo tutti i possibili valori e li inseriamo nel vettore valori_possibili
//Se il ciclo for viene eseguito significa che c'è almeno un valore possibile per quella cella
//Se i raggiunge il numero celle totali-1 (in quanto si parte da 0) allora il sudoku è stato risolto
//Ritorniamo false in modo da continuare a trovare soluzioni
//Nel caso i<celle totali -1 allora chiamiamo ricorsivamente questo metodo con i+1
//Nel caso che il ciclo for non fosse eseguito significa che in quella cella non può andare alcun valore
//Azzeriamo quindi la nostra variabile nel caso lock_square è uguale a false
//e torniamo alla chiamata precedente


bool Sudoku_letterale_solver:: solver (unsigned int i)
{


    int y = i%range_lettere;         // avanzo sulla riga
    int x = i/range_lettere;         //scendo sulla colonna




    std::vector <char> valori_possibili;
    if(i<=celle_totali-1){           //indice parte da 0
        if(square[x][y]!='0' && lock_square[x][y]==true)
            valori_possibili.push_back(square[x][y]);
        else{
            for(char val_da_ins = 'A'; val_da_ins<range_lettere+'A'; val_da_ins++)
                if(check_elemento(x,y,val_da_ins)==true)
                    valori_possibili.push_back(val_da_ins);
        }
    }

        for (std::vector<char>::iterator it = valori_possibili.begin() ; it != valori_possibili.end(); it++){
            square[x][y]=*it;
            if(i==celle_totali-1){


                numero_soluzioni++;
                std::cout<<std::endl<<" - CICLI DI BACKTRACKING = "<<conta_cicli<<std::endl;
                std::cout<<" - SOLUZIONE NUMERO = "<<numero_soluzioni<<std::endl;

                conta_cicli++;
                stampa();
                if(lock_square[x][y]==false)
                    square[x][y]=0;
                return false;
            }

            if(solver(i+1))
                return true;

        }



        if(lock_square[x][y]==false)
            square[x][y]='0';
            conta_cicli++;
            return false;

}

//Metodo che consente di trovare le soluzioni banali delle celle
//Questo metodo, infatti, riempie tutte le celle che hanno un unico valore da inserire
//Per ogni quadrato costruiamo una matrice n*n
//Lungo le righe abbiamo le celle
//Lungo le colonne abbiamo i valori da inserire che vanno da 'A' a 'A'+n*n
//C'è un contatore repeat che si incrementa  ogni volta che viene inserito un valore nel sudoku di partenza
//Se è stato inserito almeno uno ripeti tutta la procedura
//Per ogni elemento del nostro quadrato inseriamo 1 se è possibile inserire quel determinato valore
//Attraverso prelaborazione riga controlla se è l'unico valore che può essere inserito
//Attraverso prelaborazione colonna controlla se è l'unica cella che può contenere quel valore

void Sudoku_letterale_solver::partial_solve()
{
    std::vector<std::vector<unsigned int> > b;
    b.resize(n*n);
    for(unsigned int i=0;i<n*n;i++)
        for(unsigned int j=0;j<n*n;j++)
            b[i].push_back(0);



    unsigned int repeat=1;
    unsigned int cont_elab=0;
    while(repeat>0){
            repeat=0;
            cont_elab++;
       for(unsigned int z=0;z<n*n;z+=n){
                for(unsigned int y=0;y<n*n;y+=n){
                        set_matrice(b);






        for(unsigned int i=z;i<z+n;i++){
            for(unsigned int j=y;j<y+n;j++)
            {

            if(square[i][j]=='0'){
                for(unsigned int k=0;k<n*n;k++)
                    if(check_elemento(i,j,k+'A')==true)
                        b[(i-z)*n+(j-y)][k]=1;

            }

            }
        }



    prelab_riga(b,z,y,repeat);
    prelab_colonna(b,z,y,repeat);

                }


}
}
std::cout<<std::endl;
std::cout<<" - NUMERO DI PRELABORAZIONI = "<<cont_elab<<std::endl;


}

//Controlla se in una riga c'è un solo 1
//In questo caso inseriscilo nel sudoku di partenza

void Sudoku_letterale_solver::prelab_riga(std::vector<std::vector<unsigned int> > b,unsigned int correzione_riga,unsigned int correzione_colonna,unsigned int &repeat)
{

    int indice_riga;
    int cont=0;
    char elemento_da_ins;
    for(unsigned int i = 0;i<n*n; i++){
        for(unsigned int j=0;j<n*n;j++)
    {
        if(b[i][j]==1){
            cont++;
            indice_riga=i;
            elemento_da_ins=j+'A';
        }
    }
        if(cont == 1){
            square[correzione_riga+indice_riga/n][correzione_colonna+(indice_riga-n*(indice_riga/n))]=elemento_da_ins;
            lock_square[correzione_riga+indice_riga/n][correzione_colonna+(indice_riga-n*(indice_riga/n))]=true;
            repeat++;
        }
    cont = 0;
    }

}

//Controlla se in una colonna c'è un solo 1
//In questo caso inseriscilo nel sudoku di partenza

void Sudoku_letterale_solver::prelab_colonna(std::vector<std::vector<unsigned int> >b,unsigned int correzione_riga,unsigned int correzione_colonna,unsigned int &repeat)
{
    unsigned int indice_riga;

    unsigned int cont=0;
    char elemento_da_ins;
        for(unsigned int j = 0; j < n*n; j++){
            for(unsigned int i = 0; i < n*n; i++)
    {
        if(b[i][j]==1){
            cont++;
            indice_riga=i;
            elemento_da_ins=j+'A';
        }
    }
        if(cont == 1){
            square[correzione_riga+indice_riga/n][correzione_colonna+(indice_riga-n*(indice_riga/n))]=elemento_da_ins;
            lock_square[correzione_riga+indice_riga/n][correzione_colonna+(indice_riga-n*(indice_riga/n))]=true;
            repeat++;
        }

    cont = 0;
    }

}

void Sudoku_letterale_solver::set_matrice(std::vector<std::vector<unsigned int> > &b)
{

    for(unsigned int i=0;i<n*n;i++)
        for(unsigned int j=0;j<n*n;j++)
            b[i][j]=0;

}
