#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

template <class T>
void bubbleAsc(T* &arr, int n){
    bool swapped = false;
    do{
        swapped = false;
        for(int i=0;i<n-1;i++){
            if(arr[i] > arr[i+1]){
                T tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                swapped = true;
            }
        }
    }while(swapped);
}

template <class T>
void bubbleAscS(T* &arr, int n){
    int lastSwap = n-1;
    while(lastSwap>0){
        int bound = lastSwap;
        lastSwap = 0;
        for(int i=0;i<bound;i++){
            if(arr[i] > arr[i+1]){
                T tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                lastSwap = i+1;
            }
        }
    }
}

template <class T>
void insertionAsc(T* &arr, int n){
    for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(arr[j+1] < arr[j]){
                T tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

template <class T>
void insertionAscB(T* &arr, int n){
    for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(arr[j+1] < arr[j]){
                T tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
            else
                break;
        }
    }
}

template <class T>
void shellAsc(T* &arr, int n){
    // we play separation of n/2, then n/4, n/8, etc...
    int curSep = n;
    do{
        curSep = curSep / 2;
        for(int i=curSep;i<n;i++){
            for(int j=i-curSep;j>=0;j-=curSep){
                if(arr[j+curSep] < arr[j]){
                    T tmp = arr[j];
                    arr[j] = arr[j+curSep];
                    arr[j+curSep] = tmp;
                }
                else
                    break;
            }
        }
    }while(curSep > 1);
}

template <class T>
int quickPivot(T* &arr, int n, int sIndex, int eIndex){ //use first element as pivot, put pivot in correct position, return index
    int le = sIndex;
    int ri = eIndex;
    while(le<ri){
        while(le<ri && arr[le] <= arr[ri]) ri--;
        if(le<ri){
            int tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
            le++;
        }
        while(le<ri && arr[le] <= arr[ri]) le++;
        if(le<ri){
            int tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
            ri--;
        }
    }
    return le;
}

template <class T>
void quickAsc(T* &arr, int n, int sIndex, int eIndex){ //start index, end index inclusive
    if(sIndex >= eIndex) return;
    int pivotPos = quickPivot(arr,n, sIndex, eIndex);
    quickAsc(arr,pivotPos,sIndex,pivotPos-1);
    quickAsc(arr,n-pivotPos-1,pivotPos+1,eIndex);
}

template <class T>
void selectionAsc(T* &arr, int n){
    int max, mPos;
    for(int j=n-1;j>=1;j--){
        max = arr[0];
        mPos = 0;
        for(int i=1;i<=j;i++){
            if(max < arr[i]){
                max = arr[i];
                mPos = i;
            }
        }
        arr[mPos] = arr[j];
        arr[j] = max;
    }
}

const int initSize = 100;
template <class T>
class AMinHeap{ // class T better has its comparison operators correctly overloaded
    private:
        T* data;
        int numItems;
        int capacity;
        void doubleCap(){
            T* newData = new T[capacity*2];
            capacity = capacity * 2;
            for(int i=1;i<=numItems;i++){
                newData[i] = data[i];
            }
            delete [] data;
            data = newData;
        }
        void siftDown(int ind){
            if(2*ind > numItems) return;
            int tmpL = 2*ind;
            int tmpR = 2*ind + 1;
            bool switchLeft = false;
            while((tmpL <= numItems && data[ind] > data[tmpL]) || (tmpR <= numItems && data[ind] > data[tmpR])){
                switchLeft = false; //default is to switch with right.
                if(tmpL <= numItems && data[ind] > data[tmpL]){
                    if(tmpR <= numItems && data[ind] > data[tmpR]){ //top bigger than both children
                        if(data[tmpL] <= data[tmpR]){ // this is telling us to switch left with parent.
                            switchLeft = true;
                        }
                    }
                    else{ //top bigger than left, but smaller than right (or right is empty)
                        switchLeft = true;
                    }
                }
                if(switchLeft){
                    T tmp = data[ind];
                    data[ind] = data[tmpL];
                    data[tmpL] = tmp;
                    ind = tmpL;
                }
                else{
                    T tmp = data[ind];
                    data[ind] = data[tmpR];
                    data[tmpR] = tmp;
                    ind = tmpR;
                }
                tmpL = 2*ind;
                tmpR = 2*ind+1;
            }
        }
        void siftUp(int ind){
            if(ind==1) return;
            int tmp = ind/2;
            while(data[tmp] > data[ind]){
                T t_tmp = data[tmp]; //exchange while parent > child
                data[tmp] = data[ind];
                data[ind] = t_tmp;
                ind = tmp;
                tmp = ind/2;
            }
        }
    public:
        AMinHeap(){
            data = new T[initSize];
            numItems = 0;
            capacity = initSize;
        }
        AMinHeap(T* arr, int n){
            if(n < initSize){
                data = new T[initSize];
                numItems = n;
                capacity = initSize;
            }
            else{
                data = new T[2*n];
                numItems = n;
                capacity = 2*n;
            }
            for(int i=1;i<=n;i++){
                data[i] = arr[i-1];
            }
            for(int i=n/2;i>=1;i--){
                siftDown(i);
            }
        }
        ~AMinHeap(){
            delete [] data;
        }
        bool isEmpty(){
            return numItems==0;
        }
        T getMin(){
            if(numItems==0) throw "Heap Empty";
            return data[1];
        }
        void push(T x){
            if(numItems==capacity-1) doubleCap();
            numItems++;
            data[numItems] = x;
            siftUp(numItems);
        }
        T delMin(){
            if(numItems==0) throw "Heap Empty";
            T x = data[1];
            data[1] = data[numItems];
            numItems--;
            siftDown(1);
            return x;
        }
        void printLevelOrder(){ //assumes class T has an overloaded ostream << operator.
            for(int i=1;i<=numItems;i++){
                cout << data[i] << " ";
            }
        }
};

template <class T>
void heapSortAsc(T* &arr, int n){
    AMinHeap<T> amh(arr,n);
    for(int i=0;i<n;i++){
        arr[i] = amh.delMin();
    }
}

template <class T>
void mergeSortAsc(T* &arr, int n){
    int mergeStep = 1; //size of each merged list
    T* arr2 = new T[n];
    while(mergeStep < n){
        for(int i=0;i<n;i+=2*mergeStep){ // increment is 2*mergeStep, since we are merging every 2 lists
            int j=i;
            int k=i+mergeStep;
            int z=i;
            while(j<i+mergeStep && k<i+2*mergeStep && k<n){ //when true, we haven't run into end of list nor finished current list
                if(arr[j] <= arr[k]){ // if = is left out, we won't have a stable merge sort.
                    arr2[z] = arr[j];
                    z++;
                    j++;
                }
                else{
                    arr2[z] = arr[k];
                    z++;
                    k++;
                }
            }
            while(j<i+mergeStep && j<n){
                arr2[z] = arr[j];
                z++;
                j++;
            }
            while(k<i+2*mergeStep && k<n){
                arr2[z] = arr[k];
                z++;
                k++;
            }
        }

        for(int i=0;i<n;i++){ // putting the sorted runs of length 2*mergeStep into arr.
            arr[i] = arr2[i];
        }
        mergeStep = mergeStep * 2;
    }
    delete [] arr2;
}

int* generateRandom(int num, int min, int max){ //generate random numbers between min and max, inclusive
    int* tmp = new int[num];
    for(int i=0;i<num;i++)
        tmp[i] = rand() % (max+1-min) + min;
    return tmp;
}

template <class T>
T* dupArray(T* arr, int n){
    T* tmp = new T[n];
    for(int i=0;i<n;i++){
        tmp[i] = arr[i];
    }
    return tmp;
}


void printIArr(int* arr, int n){
    // print, at most 10 per row
    int count = 0;
    for(int i=0;i<n;i++){
        cout << left << setw(10) << arr[i];
        count = (count+1)%10;
        if(count==0) cout << endl;
    }
    if(count!=0) cout << endl;
    cout << endl;
}

int main(){
    srand(time(NULL));
    int* seq1 = generateRandom(70,0,100);
    int* seq2 = generateRandom(2000,0,100000);

    int* tmp = NULL;

    cout << "Sequence 1:" << endl;
    printIArr(seq1, 70);

    tmp = dupArray<int>(seq1,70);
    insertionAsc<int>(tmp,70);

    cout << "Insertion: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    insertionAscB<int>(tmp,70);

    cout << "Insertion with Break: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    shellAsc<int>(tmp,70);

    cout << "Shell: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    cout << "Sequence 1:" << endl;
    printIArr(seq1, 70);

    tmp = dupArray<int>(seq1,70);
    bubbleAsc<int>(tmp,70);

    cout << "Bubble: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    bubbleAscS<int>(tmp,70);

    cout << "Better Bubble: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    quickAsc<int>(tmp,70,0,69);

    cout << "Quick Sort: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    selectionAsc<int>(tmp,70);

    cout << "Selection Sort: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    heapSortAsc<int>(tmp,70);

    cout << "Heap Sort: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    mergeSortAsc<int>(tmp,70);

    cout << "Merge Sort: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    cout << "Insertion 70: ";
    clock_t start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        insertionAsc<int>(tmp,70);
        delete [] tmp;
    }
    clock_t end = clock();
    double timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Insertion 70 with break: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        insertionAscB<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        shellAsc<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Bubble 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        bubbleAsc<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Better Bubble 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        bubbleAscS<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Quick Sort 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        quickAsc<int>(tmp,70,0,69);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Selection 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        selectionAsc<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Heap Sort 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        heapSortAsc<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Merge Sort 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        mergeSortAsc<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Insertion 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        insertionAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Insertion 2000 with break: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        insertionAscB<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        shellAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Bubble 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        bubbleAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Better Bubble 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        bubbleAscS<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Quick Sort 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        quickAsc<int>(tmp,2000,0,1999);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Selection 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        selectionAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Heap Sort 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        heapSortAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Merge Sort 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        mergeSortAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;
}
