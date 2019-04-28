#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <malloc.h>
using namespace std;

void bubble_sort (vector<int> &vetor,long int &swap, long int &comp) {
    int k, j, aux;
    for (k = vetor.size() - 1; k > 0; k--) {
        for (j = 0; j < k; j++) {
            comp++;
            if (vetor[j] > vetor[j + 1]) {
                swap++;
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }

}

void insertion_sort(vector<int> &vetor,long int &swap,long int &comp) {

    for (int i = 1; i < vetor.size(); i++) {
        int escolhido = vetor[i];
        int j = i - 1;

        while ((j >= 0) && (vetor[j] > escolhido)) {
            comp++;
            swap++;
            vetor[j + 1] = vetor[j];
            j--;
        }
        swap++;
        vetor[j + 1] = escolhido;
    }
}

void SelectionSort(vector<int> &vetor,long int &swap,long int &comp) {
    for (int indice = 0; indice < vetor.size(); ++indice) {
        int indiceMenor = indice;
        for (int indiceSeguinte = indice+1; indiceSeguinte < vetor.size(); ++indiceSeguinte) {
            comp++;
            if (vetor[indiceSeguinte] < vetor[indiceMenor]) {
                indiceMenor = indiceSeguinte;
            }
        }
        swap++;
        int aux = vetor[indice];
        vetor[indice] = vetor[indiceMenor];
        vetor[indiceMenor] = aux;
    }
}

void merge(vector<int> &arr, int l, int m, int r,long int &swap,long int &comp) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2){
        comp++;
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(vector<int> &arr, int l, int r,long int &swap,long int &comp) {
    if (l < r){
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m, swap, comp);
        mergeSort(arr, m+1, r, swap, comp);

        merge(arr, l, m, r, swap, comp);
    }
}

void quicksort(vector<int> &values, int began, int end,long int &swap,long int &comp) {
    int i, j, pivo, aux;
    i = began;
    j = end-1;
    pivo = values[(began + end) / 2];
    while(i <= j){
        while(values[i] < pivo && i < end){
            comp++;
            i++;
        }
        while(values[j] > pivo && j > began){
            comp++;
            j--;
        }
        if(i <= j){
            swap++;
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;
            i++;
            j--;
        }
    }
    if(j > began)
        quicksort(values, began, j+1, swap, comp);
    if(i < end)
        quicksort(values, i, end, swap, comp);

}

template<class T>
vector<T> counting_sort(const vector<T> &op ,long int &swap,long int &comp) {
    if ( op.empty() )
        return vector<T> {};

    auto min = *min_element( op.begin(), op.end() );
    auto max = *max_element( op.begin(), op.end() );

    vector<int> contagem( max - min + 1, 0 );
    for ( auto it = op.begin(); it != op.end(); ++it )
        ++contagem[ *it - min ];

    partial_sum( contagem.begin(), contagem.end(), contagem.begin() );

    vector<T> ordenado( op.size() );
    for ( auto it2 = op.rbegin(); it2 != op.rend(); ++it2 )
        ordenado[ --contagem[ *it2 - min ] ] = *it2;
    return ordenado;
}


void BucketSort(vector<int> &data,long int &swap,long int &comp) {
    int count = data.size();
    int minValue = data[0];
    int maxValue = data[0];

    for (int i = 1; i < count; i++)
    {
        if (data[i] > maxValue)
            maxValue = data[i];
        if (data[i] < minValue)
            minValue = data[i];
    }

    int bucketLength = maxValue - minValue + 1;
    vector<int>* bucket = new vector<int>[bucketLength];

    for (int i = 0; i < bucketLength; i++)
    {
        bucket[i] = vector<int>();
    }

    for (int i = 0; i < count; i++)
    {
        bucket[data[i] - minValue].push_back(data[i]);
    }

    int k = 0;
    for (int i = 0; i < bucketLength; i++)
    {
        int bucketSize = bucket[i].size();

        if (bucketSize > 0)
        {
            for (int j = 0; j < bucketSize; j++)
            {
                data[k] = bucket[i][j];
                k++;
            }
        }
    }
}

int fileNlines(ifstream *myfile){
    int lines = 0;
    string str;
    while(getline(*myfile,str)){
        lines++;
    }
    return lines;
}
void pushelements(vector<int> &vetor, ifstream *myfile){
    int aux = 0;
    string str;
    getline(*myfile,str);
    vetor.push_back(stoi(str));
    for(int i=0;*myfile>>aux;i++){
        vetor.push_back(aux);
    }
}
void copy(vector<int> &vector1,vector<int> &vector2){
    for (int i = 0; i < vector1.size(); ++i) {
        vector1[i] = vector2[i];
    }
}
void oneforall(vector<int> &vetor,long int &swap,long int comp){
    vector<int> ordenado(vetor.size());
    vector<int> original(vetor.size());

    copy(original,vetor);
    bubble_sort(vetor, swap, comp);
    cout<<"feito p /bubble"<<endl;
    copy(vetor,original);
    insertion_sort(vetor, swap, comp);
    cout<<"feito p/ insertion_sort"<<endl;
    copy(vetor,original);
    SelectionSort(vetor, swap, comp);
    cout<<"feito p/ SelectionSort"<<endl;
    copy(vetor,original);
    mergeSort(vetor,0,vetor.size(), swap, comp);
    cout<<"feito p/ mergeSort"<<endl;
    copy(vetor,original);
    quicksort(vetor,0,vetor.size(), swap, comp);
    cout<<"feito p/ quicksort"<<endl;
    copy(vetor,original);
    ordenado=counting_sort(vetor, swap, comp);
    cout<<"feito p/ counting_sort"<<endl;
    copy(vetor,original);
    BucketSort(vetor, swap, comp);
    cout<<"feito p/ BucketSort"<<endl;
    cout<<"feito p/ todos"<<endl;
    original.clear();
    ordenado.clear();
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
    strings.push_back("50000.txt");
    strings.push_back("75000.txt");
    strings.push_back("100000.txt");
    strings.push_back("200000.txt");
    strings.push_back("500000.txt");
    strings.push_back("750000.txt");
    strings.push_back("100000.txt");
    strings.push_back("200000.txt");
    strings.push_back("500000.txt");
    strings.push_back("750000.txt");
    strings.push_back("1000000.txt");
    strings.push_back("1250000.txt");
    strings.push_back("2000000.txt");
    myfile.open(("C:\\Users\\mauri\\CLionProjects\\PAA\\Aleatorios\\a" + strings.at(0)));
    if(!myfile.is_open()){
        return 404;
    }
    myfile.clear();
    myfile.seekg(0, ios::beg);
    vector<int> element;
    pushelements(element,&myfile);
    vector<int> ordenado(element.size());
    long int swap=0,comp=0;
    bubble_sort(element,swap,comp);
    cout<<swap<<" "<<comp<<endl;
//    ordenado = counting_sort(element);
//    element.clear();
//    ordenado.clear();
//    insertion_sort(element);
//    oneforall(element);





    return 0;
}