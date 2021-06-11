#include "sudoku_letterale.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//Costruttore di default

Sudoku_letterale::Sudoku_letterale()
{
    n=3;
    range_lettere=n*n;
    celle_totali=range_lettere*range_lettere;
    square.resize(n*n);
    lock_square.resize(n*n);
    for(unsigned int i=0;i<n*n;i++)
        for(unsigned int j=0;j<n*n;j++){
            square[i].push_back('0');
            lock_square[i].push_back(false);
        }
}

//Costruttore con parametri

Sudoku_letterale::Sudoku_letterale(unsigned int numero)
{
    n=numero;
    range_lettere=n*n;
    celle_totali=range_lettere*range_lettere;
    square.resize(n*n);
    lock_square.resize(n*n);
    for(unsigned int i=0;i<n*n;i++)
        for(unsigned int j=0;j<n*n;j++){
            square[i].push_back('0');
            lock_square[i].push_back(false);
        }
}

//Costruttore copia
Sudoku_letterale::Sudoku_letterale(Sudoku_letterale &a)
{

    n=a.n;
    range_lettere=a.range_lettere;
    celle_totali=a.celle_totali;
    square.resize(n*n);
    lock_square.resize(n*n);
    for(unsigned int i=0; i<n*n; i++)
        for(unsigned int j=0; j<n*n; j++){
            square[i].push_back(a.square[i][j]);
            lock_square[i].push_back(a.lock_square[i][j]);
        }
}
//Distruttore
Sudoku_letterale::~Sudoku_letterale()
{
    square.clear();
    lock_square.clear();
}
//Metodo che resistuisce il numero di soluzioni
unsigned int Sudoku_letterale::get_n(){
    return n;
}
//Metodo che stampa il sudoku
void Sudoku_letterale::stampa()
{
    char linea_orizzontale=196;
    char linea_verticale=179;
    std::cout<<" ";
    for(unsigned int z = 0; z<n*n;z++)
        std::cout<<linea_orizzontale<<linea_orizzontale<<linea_orizzontale;
         for(unsigned int z = 1; z<n;z++)
        std::cout<<linea_orizzontale<<linea_orizzontale<<linea_orizzontale;
        std::cout<<linea_orizzontale<<linea_orizzontale;
        std::cout<<std::endl;
    for(unsigned int i=0;i<n*n;i++){
            std::cout<<linea_verticale<<"  ";
        for(unsigned int j=0;j<n*n;j++){
        if(square[i][j]=='0')
            std::cout<<"   ";
            else
                std::cout<<square[i][j]<<"  ";

        if((j+1)%n==0)
            std::cout<<linea_verticale<<"  ";
        }



    std::cout<<std::endl;
    std::cout<<linea_verticale<<"  ";
    for(unsigned int z = 0 ;z<n*n;z++){
            std::cout<<"   ";
        if((z+1)%n==0)
            std::cout<<linea_verticale<<"  ";


    }
    std::cout<<std::endl;

    if((i+1)%n==0){
    std::cout<<" ";
    for(unsigned int z = 0; z<n*n;z++)
        std::cout<<linea_orizzontale<<linea_orizzontale<<linea_orizzontale;
         for(unsigned int z = 1; z<n;z++)
        std::cout<<linea_orizzontale<<linea_orizzontale<<linea_orizzontale;
        std::cout<<linea_orizzontale<<linea_orizzontale;
        std::cout<<std::endl;

    }

    }
    std::cout<<std::endl<<std::endl<<std::endl;
}

//Metodo che controlla se "lettera" può stare nella casella [riga][colonna].
//Nel primo for il metodo restituirà false se troverà lungo la riga un valore uguale a "lettera"
//Nel secondo for il metodo resituirà false se troverà lungo la colonna una valore uguale a "lettera"
//z e x sono indici che ci servono per posizionarci nella cella dove vogliamo inserire il lettera.
//I 2 cicli for innestati alla fine controllano la presenza di un valore uguale nella cella di appartenenza.


bool Sudoku_letterale::check_elemento(unsigned int riga,unsigned int colonna,char lettera)
{
    for(unsigned int i = 0;i<n*n;i++)
        if(square[riga][i]==lettera && i!=colonna)
            return false;

    for(unsigned int i = 0;i<n*n;i++)
        if(square[i][colonna]==lettera && i!=riga)
            return false;

    int z = (riga)/n;
    int x = (colonna)/n;

    for(unsigned int i = z*n;i<z*n+n;i++)
        for(unsigned int j = x*n; j<x*n+n;j++)
            if(square[i][j]==lettera && (j!=colonna || i!=riga))
            return false;

    return true;


}

//Il seguente metodo genera un sudoku casualmente che abbia almeno una soluzione
//Inizialmente azzera tutte le posizioni (utile dal secondo passo in quanto il costruttore ha già inizializzato il sudoku)
//Il while interno si ferma quando sono stati inseriti n^3 elementi
//Genera un numero rand che viene sommato ad 'A' e le cordinate x e y
//Se lock_square[x][y] == false significa che la posizione è libera e se check_elemento == true significa che la lettera può essere inserita
//aggiorna square e lock square e incrementa il contatore
// L'algoritmo alla fine controlla se il sudoku ha almeno una soluzione.
// In questo caso azzera tutte le posizioni con lock_square = false (in quanto il sudoku è stato risolto)
// Nel caso non abbia soluzione ricomincia

void Sudoku_letterale::genera_sudoku()
{
    srand(time(NULL));

    do{
        unsigned int cont=0;
        for(unsigned int i = 0;i<n*n;i++)
            for(unsigned int j=0;j<n*n;j++){
                    square[i][j]='0';
                    lock_square[i][j]=false;
                }
    while(cont<=n*n*n){
        char lettera = 'A'+rand()%(n*n);
        unsigned int x=rand()%(n*n);
        unsigned int y=rand()%(n*n);
        if(lock_square[x][y]==false && check_elemento(x,y,lettera)==true)
        {
            square[x][y]=lettera;
            lock_square[x][y]=true;
            cont++;
        }

        }
    }
    while(controll_sudoku(0)==false);
    for(unsigned int i = 0;i<n*n;i++)
                for(unsigned int j=0;j<n*n;j++)
                    if(lock_square[i][j]==false)
                        square[i][j]='0';


    }

//Metodo che restituisce false se il sudoku non è costruito adeguatamente, true nell'altro caso


bool Sudoku_letterale::check_sudoku()
{
    for(unsigned int i=0;i<n*n;i++)
        for(unsigned int j=0;j<n*n;j++)
            if(square[i][j]!='0' && (check_elemento(i,j,square[i][j]))==false){
                std::cout<<square[i][j]<<i<<j;
                return false;
            }
    return true;
}

//Metodo per inserire una lettera in una determinata posizione
//Per prima cosa controlla se la lettera appartiene al range di quelle che possono essere inserite
//Controlla se può stare in quella posizione e aggiorna square e lock_square
//Nel caso una di queste due condizioni fosse violata allora aggiorna square a 0 e lock_square a false

void Sudoku_letterale::insert_elemento(char lettera,unsigned int riga,unsigned int colonna)
{
    if(lettera>='A' && lettera<'A'+range_lettere && check_elemento(riga,colonna,lettera))
    {
        square[riga][colonna]=lettera;
        lock_square[riga][colonna]=true;
    }
    else
    {
        square[riga][colonna]='0';
        lock_square[riga][colonna]=false;
    }
}

//metodo che risolve il sudoku con la tecnica del backtracking e restituisce true appena trova una soluzione

bool Sudoku_letterale:: controll_sudoku (unsigned int i)
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
            square[x][y]=(*it);
            if(i==celle_totali-1){
                return true;
            }
            if(controll_sudoku(i+1))
                return true;

        }

        if(lock_square[x][y]==false)
            square[x][y]='0';
            return false;
}
