#include <iostream>
#include <iomanip>
using namespace std;

/* UPLOAD START */
template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void insertLast(T x){
            insertEleAtPos(length,x);
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
        deleteEle(T x){
        	deleteEleAtPos(locateEle(x));
		}
};
template <class T>
class AMinHeap{ // class T better has its comparison operators correctly overloaded
    private:
        T *arr;
        int length;
    public:
        AMinHeap(){
        	arr=new T[1];
        	arr[0]=-1;
            length=0;
        }
        AMinHeap(T* arr0, int n){
            int i;
            arr=new T[n+1];
        	arr[0]=-1;
            length=n;
            for(i=0;i<n;i++)
            	arr[i+1]=arr0[i];
            for(i=n/2;i>=1;i--){
            	adjd(i);
			}
        }
        ~AMinHeap(){
        	delete []arr;
        }
        bool isEmpty(){
            return length==0;
        }
        T getMin(){
            if(length==0)throw "Heap Empty";
            return arr[1];
        }
        void push(T x){
        	int i;
        	T *tmp=new T[length+2];
        	for(i=0;i<length+1;i++)
        		tmp[i]=arr[i];
        	delete []arr;
        	arr=tmp;
        	arr[length+1]=x;
            length++;
            if(length==1)return;
            adj(length);
        }
        void adjd(int pi){
        	int l=pi*2;
        	int r=pi*2+1;
        	int min=pi;
        	if(l<=length&&arr[l]<arr[min])
        		min=l;
        	if(r<=length&&arr[r]<arr[min])
        		min=r;
        	if(min==pi)
        		return;
        	T tmp=arr[pi];
        	arr[pi]=arr[min];
        	arr[min]=tmp;
        	adjd(min);
		}
        void adj(int ci){
        	int pi=(ci)/2;
        	int pd=arr[pi];
        	int cd=arr[ci];
        	if(pd>cd){
        		arr[pi]=cd;
        		arr[ci]=pd;
        		adj(pi);
			}
		}
        T delMin(){
            if(length==0)throw "Heap Empty";
            T min=this->getMin();
            arr[1]=arr[length];
            length--;
            adjd(1);
            return min;
        }
        T* getLevelOrderArray(){
            return arr;
        }
        int getNumData(){
            return length;
        }
};

/* UPLOAD END */

template <class T>
void printLevelOrder(T* data, int numItems){ //assumes class T has an overloaded ostream << operator.
    for(int i=1;i<=numItems;i++){
        cout << data[i] << " ";
    }
}

int test1(){ // normal test
    AMinHeap<int> amh;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    amh.push(10);
    amh.push(8);
    amh.push(6);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    amh.push(4);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    
    cout << "Top: " << amh.getMin() << endl;
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    
    cout << "Popping:" << endl;
    while(!amh.isEmpty()){
        cout << "Current Min: " << amh.delMin() << endl;
        cout << endl;
    }
    return 0;
}

int main(){
    //unit test for Heap.
    test1();
    return 0;
}
