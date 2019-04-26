#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <time.h>
#include <fstream>
using namespace std;

void bubble_sort (int vetor[], int n) {
    int k, j, aux;

    for (k = n - 1; k > 0; k--) {
        printf("\n[%d] ", k);

        for (j = 0; j < k; j++) {
            printf("%d, ", j);

            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void insertion_sort(std::vector<int> &vetor) {

    for (int i = 1; i < vetor.size(); i++) {
        int escolhido = vetor[i];
        int j = i - 1;

        while ((j >= 0) && (vetor[j] > escolhido)) {
            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = escolhido;
    }
}

void SelectionSort(int vetor[], int tam) {
    for (int indice = 0; indice < tam; ++indice) {
        int indiceMenor = indice;
        for (int indiceSeguinte = indice+1; indiceSeguinte < tam; ++indiceSeguinte) {
            if (vetor[indiceSeguinte] < vetor[indiceMenor]) {
                indiceMenor = indiceSeguinte;
            }
        }
        int aux = vetor[indice];
        vetor[indice] = vetor[indiceMenor];
        vetor[indiceMenor] = aux;
    }
}

void merge(int *saida, int *auxiliar, int inicio, int meio, int fim){
    int i, j, k;
    i = inicio;
    j = meio + 1;
    k = inicio;
    while(i <= meio && j <= fim){
        if(auxiliar[i] < auxiliar[j]){
            saida[k] = auxiliar[i];
            i++;
        }
        else{
            saida[k] = auxiliar[j];
            j++;
        }
        k++;
    }

    while(i <= meio){
        saida[k] = auxiliar[i];
        i++;
        k++;
    }

    while(j <= fim){
        saida[k] = auxiliar[j];
        j++;
        k++;
    }
    //Copia os elementos que foram ordenados para o auxiliar
    for(int p = inicio; p <= fim; p++)
        auxiliar[p] = saida [p];
}



void mergeSort(int *saida, int *auxiliar, int inicio, int fim){
    if(inicio < fim){
        int meio = (inicio + fim) / 2;
        mergeSort(saida, auxiliar, inicio, meio);
        mergeSort(saida, auxiliar, meio + 1, fim);
        merge(saida, auxiliar, inicio, meio, fim);
    }
}

void quicksort(int values[], int began, int end)
{
    int i, j, pivo, aux;
    i = began;
    j = end-1;
    pivo = values[(began + end) / 2];
    while(i <= j)
    {
        while(values[i] < pivo && i < end)
        {
            i++;
        }
        while(values[j] > pivo && j > began)
        {
            j--;
        }
        if(i <= j)
        {
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;
            i++;
            j--;
        }
    }
    if(j > began)
        quicksort(values, began, j+1);
    if(i < end)
        quicksort(values, i, end);
}

template<class T>
std::vector<T> counting_sort( const std::vector<T> &op )
{
    if ( op.empty() )
        return std::vector<T> {};

    auto min = *std::min_element( op.begin(), op.end() );
    auto max = *std::max_element( op.begin(), op.end() );

    std::vector<int> contagem( max - min + 1, 0 );
    for ( auto it = op.begin(); it != op.end(); ++it )
        ++contagem[ *it - min ];

    std::partial_sum( contagem.begin(), contagem.end(), contagem.begin() );

    std::vector<T> ordenado( op.size() );
    for ( auto it2 = op.rbegin(); it2 != op.rend(); ++it2 )
        ordenado[ --contagem[ *it2 - min ] ] = *it2;

    return ordenado;
}

#define TAM 20 /*Tamanho do vetor*/
#define NUM 10000 /*base para gerador de numeros aleatorios*/

void bucketSort(int *vet){
    int mat[10][TAM],aux[TAM],cont=1,num,w=0,i,j;


    do{
        for(i=0;i<TAM;i++){aux[i] = 0;}//Zerando o vetor auxiliar.
        for(i=0;i<10;i++)  {//Setando a Matriz com valores -1
            for(j=0;j<TAM;j++){
                mat[i][j] = -1;
            }
        }
        for (i=0;i<TAM;i++) {
            num = (vet[i]/cont)%10;//verificando o valor da esquerda para direita
            mat[num][aux[num]] = vet[i];//colocando o valor na sua posicao na matriz
            aux[num]++; //contador de colunas da matriz
        }

        for(i=0;i<10;i++) {//volta com os valores da Matriz para o vetor
            for(j=0;j<TAM;j++){
                if(mat[i][j] != -1){
                    vet[w] = mat[i][j];
                    w++;
                }
            }
        }
        w = 0;
        cont=cont*10;
    }while(aux[0] < TAM);//condicao :Enquanto vetor auxiliar < tamanho vetor
}                          //

/******************GERADOR DE NUMEROS ALEATORIOS**************************/
void gerarVet(int *vet){

    srand(time(NULL));
    for (int i=0;i<TAM;i++){
        vet[i]=rand()%NUM;
    }
}
/*******************FUNCAO PARA IMPRIMIR VETOR************************/
void imprimaVet(int *vet){
    for (int i=0;i<TAM;i++){
        cout<<vet[i]<<"|";
    }
    cout<<"**************************************************************\n";
}

int main() {
    ifstream myfile;
    vector<string> strings;
    strings.push_back("100.txt");
    strings.push_back("200.txt");
    strings.push_back("500.txt");
    strings.push_back("1000.txt");
    strings.push_back("2000.txt");
    strings.push_back("5000.txt");
    strings.push_back("75000.txt");
    strings.push_back("10000.txt");
    strings.push_back("15000.txt");
    strings.push_back("30000.txt");
    strings.push_back("500000.txt");
    strings.push_back("750000.txt");
    strings.push_back("100000.txt");
    strings.push_back("200000.txt");
    strings.push_back("500000.txt");
    strings.push_back("750000.txt");
    strings.push_back("1000000.txt");
    strings.push_back("1250000.txt");
    strings.push_back("2000000.txt");
    myfile.open(("C:\\Users\\mauri\\CLionProjects\\PAA\\Aleatorios\\a" + strings.at(0)), ifstream::ate);
    if(myfile.is_open()){
        cout<<"dsadsad";
    }

    int *a;
    cout << "a" + strings.at(0) << endl;
    int aux;
    for (int i = 0; myfile >> aux ; ++i) {
        myfile>>aux;
        a = new int;
        a[i] = aux;
        cout<<aux<<endl;
    }

    return 0;
}