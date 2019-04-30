#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <malloc.h>
using namespace std;

void bubble_sort (vector<int> &vetor,unsigned long long int &swap, unsigned long long int &comp) {
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

void insertion_sort(vector<int> &vetor,unsigned long long int &swap,unsigned long long int &comp) {

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

void SelectionSort(vector<int> &vetor,unsigned long long int &swap,unsigned long long int &comp) {
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

void merge(vector<int> &arr, int l, int m, int r,unsigned long long int &swap,unsigned long long int &comp) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    vector<int> L;
    vector<int> R;

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L.push_back(arr[l + i]);

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2){
        swap++;
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
        swap++;
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2){
        swap++;
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(vector<int> &arr, int l, int r,unsigned long long int &swap,unsigned long long int &comp) {
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

void quicksort(vector<int> &values, int began, int end,unsigned long long int &swap,unsigned long long int &comp) {
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
vector<T> counting_sort(const vector<T> &op ,unsigned long long int &swap,unsigned long long int &comp) {
    if ( op.empty() )
        return vector<T> {};

    auto min = *min_element( op.begin(), op.end() );
    auto max = *max_element( op.begin(), op.end() );

    vector<int> contagem( max - min + 1, 0 );
    for ( auto it = op.begin(); it != op.end(); ++it ){
        ++contagem[ *it - min ];
        comp++;
    }
    partial_sum( contagem.begin(), contagem.end(), contagem.begin() );

    vector<T> ordenado( op.size() );
    for ( auto it2 = op.rbegin(); it2 != op.rend(); ++it2 ){
        ordenado[ --contagem[ *it2 - min ] ] = *it2;
        swap++;
    }
    return ordenado;
}


void BucketSort(vector<int> &data,unsigned long long int &swap,unsigned long long int &comp) {
    int count = data.size();
    int minValue = data[0];
    int maxValue = data[0];

    for (int i = 1; i < count; i++){
        comp++;
        if (data[i] > maxValue)
            maxValue = data[i];
        comp++;
        if (data[i] < minValue)
            minValue = data[i];
    }

    int bucketLength = maxValue - minValue + 1;
    vector<int>* bucket = new vector<int>[bucketLength];

    for (int i = 0; i < bucketLength; i++){
        bucket[i] = vector<int>();
    }

    for (int i = 0; i < count; i++){
        bucket[data[i] - minValue].push_back(data[i]);
        swap++;
    }

    int k = 0;
    for (int i = 0; i < bucketLength; i++){
        int bucketSize = bucket[i].size();

        if (bucketSize > 0){
            for (int j = 0; j < bucketSize; j++){
                swap++;
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
    myfile->clear();
    myfile->seekg(0);
}
void copy(vector<int> &vector1,vector<int> &vector2){
    vector1.clear();
    for (int i = 0; i < vector2.size(); i++) {
        int aux = vector2[i];
        vector1.push_back(aux);
    }
}

void oneforall(vector<int> original){
    ofstream swapoutfile;
    ofstream compoutfile;
    ofstream timeoutfile;
    swapoutfile.open("C:\\Users\\MHI\\CLionProjects\\PAA\\Aleatorios\\swap.csv",ios::app);
    compoutfile.open("C:\\Users\\MHI\\CLionProjects\\PAA\\Aleatorios\\comp.csv",ios::app);
    timeoutfile.open("C:\\Users\\MHI\\CLionProjects\\PAA\\Aleatorios\\time.csv",ios::app);

    vector<int> ordenado;
    vector<int> vetor;
    unsigned long long int swap=0;
    unsigned long long int comp=0;
    double time;
    double time;

    copy(vetor,original);
    clock_t start = clock();
    bubble_sort(vetor, swap, comp);
    clock_t end = clock();
    time = (double) (end-start) / CLOCKS_PER_SEC;
    swapoutfile<<swap<<";";
    compoutfile<<comp<<";";
    timeoutfile<<time<<";";
    cout<<swap<<" | "<<comp<<" | "<<time<<endl;
    cout<<"feito p/ bubble"<<endl;

    swap=0;comp=0;time=0.0;
    copy(vetor,original);
    start = clock();
    insertion_sort(vetor, swap, comp);
    end = clock();
    time = (double) (end-start) / CLOCKS_PER_SEC;
    swapoutfile<<swap<<";";
    compoutfile<<comp<<";";
    timeoutfile<<time<<";";
    cout<<swap<<" | "<<comp<<" | "<<time<<endl;
    cout<<"feito p/ insertion_sort"<<endl;

    swap=0;comp=0;time=0.0;
    copy(vetor,original);
    start = clock();
    SelectionSort(vetor, swap, comp);
    end = clock();
    time = (double) (end-start) / CLOCKS_PER_SEC;
    swapoutfile<<swap<<";";
    compoutfile<<comp<<";";
    timeoutfile<<time<<";";
    cout<<swap<<" | "<<comp<<" | "<<time<<endl;
    cout<<"feito p/ SelectionSort"<<endl;


    swap=0;comp=0;time=0.0;
    copy(vetor,original);
    start = clock();
    mergeSort(vetor,0,vetor.size(), swap, comp);
    end = clock();
    time = (double) (end-start) / CLOCKS_PER_SEC;
    swapoutfile<<swap<<";";
    compoutfile<<comp<<";";
    timeoutfile<<time<<";";
    cout<<swap<<" | "<<comp<<" | "<<time<<endl;
    cout<<"feito p/ mergeSort"<<endl;

    swap=0;comp=0;time=0.0;
    copy(vetor,original);
    start = clock();
    quicksort(vetor,0,vetor.size(), swap, comp);
    end = clock();
    time = (double) (end-start) / CLOCKS_PER_SEC;
    swapoutfile<<swap<<";";
    compoutfile<<comp<<";";
    timeoutfile<<time<<";";
    cout<<swap<<" | "<<comp<<" | "<<time<<endl;
    cout<<"feito p/ quicksort"<<endl;

    swap=0;comp=0;time=0.0;
    copy(vetor,original);
    start = clock();
    ordenado=counting_sort(vetor, swap, comp);
    end = clock();
    time = (double) (end-start) / CLOCKS_PER_SEC;
    swapoutfile<<swap<<";";
    compoutfile<<comp<<";";
    timeoutfile<<time<<";";
    cout<<swap<<" | "<<comp<<" | "<<time<<endl;
    cout<<"feito p/ counting_sort"<<endl;

    swap=0;comp=0;time=0.0;
    copy(vetor,original);
    start = clock();
    BucketSort(vetor, swap, comp);
    end = clock();
    time = (double) (end-start) / CLOCKS_PER_SEC;
    swapoutfile<<swap<<endl;
    compoutfile<<comp<<endl;
    timeoutfile<<time<<endl;
    cout<<swap<<" | "<<comp<<" | "<<time<<endl;
    cout<<"feito p/ BucketSort"<<endl;

    cout<<"feito p/ todos"<<endl;
    original.clear();
    ordenado.clear();
    timeoutfile.close();
    swapoutfile.close();
    compoutfile.close();
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
    strings.push_back("1000000.txt");
    strings.push_back("1250000.txt");
    strings.push_back("1500000.txt");
    strings.push_back("2000000.txt");
//    for (int i = 15; i < strings.size(); i++) {
//        myfile.open(("C:\\Users\\MHI\\CLionProjects\\PAA\\Aleatorios\\a" + strings.at(i)));
//        if(!myfile.is_open()){
//            return i;
//        }
//        myfile.clear();
//        myfile.seekg(0, ios::beg);
//        vector<int> element;
//        pushelements(element,&myfile);
//        oneforall(element);
//        element.clear();
//        myfile.close();
//        cout<<"----------------------"<<i<<endl;
//    }
    ofstream swapoutfile;
    ofstream compoutfile;
    ofstream timeoutfile;
    swapoutfile.open("C:\\Users\\MHI\\CLionProjects\\PAA\\Aleatorios\\swap.csv",ios::app);
    compoutfile.open("C:\\Users\\MHI\\CLionProjects\\PAA\\Aleatorios\\comp.csv",ios::app);
    timeoutfile.open("C:\\Users\\MHI\\CLionProjects\\PAA\\Aleatorios\\time.csv",ios::app);
    myfile.open(("C:\\Users\\MHI\\CLionProjects\\PAA\\Aleatorios\\a" + strings.at(15)));
    unsigned long long int swap,comp;
    double time;
    clock_t start,end;
    swap=0;comp=0;time=0.0;
    vector<int> vetor;
    pushelements(vetor,&myfile);
//    start = clock();
//    mergeSort(vetor,0,vetor.size(), swap, comp);
//    end = clock();
//    time = (double) (end-start) / CLOCKS_PER_SEC;
//    swapoutfile<<swap<<";";
//    compoutfile<<comp<<";";
//    timeoutfile<<time<<";";
//    cout<<swap<<" | "<<comp<<" | "<<time<<endl;
//    cout<<"feito p/ mergeSort"<<endl;
    vector<int> test={10,20,30,40,50,60,70};
    copy(vetor,test);
    test[2]=123132;
    for (int i = 0; i < vetor.size(); ++i) {
        cout<<vetor[i]<<" ";
    }

    return 0;
}