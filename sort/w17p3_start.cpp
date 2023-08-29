#include <iostream>
#include <stdlib.h>
using namespace std;

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
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkStack{
    private:
        DNode<T>* top;
        int length;
    public:
        LinkStack(){
            top = NULL;
            length = 0;
        }
        ~LinkStack(){
            while(top!=NULL){
                DNode<T>* tmp = top;
                top = top->next;
                delete tmp;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void push(T x){
            DNode<T>* tmp = new DNode<T>;
            tmp->data = x;
            tmp->next = top;
            top = tmp;
            length++;
        }
        T pop(){
            if(length==0) throw "Stack Empty!";
            DNode<T>* tmp = top;
            top = top->next;
            T tmpData = tmp->data;
            delete tmp;
            length--;
            return tmpData;
        }
        T getTop(){
            if(length==0) throw "Stack Empty!";
            return top->data;
        }
        void printStack(){
            cout << "Stack top: ";
            DNode<T>* tmp = top;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ":stack bottom" << endl;
        }
};

template <class T>
class LinkQueue{
    private:
        DNode<T>* front;
        DNode<T>* back;
        int length;
    public:
        LinkQueue(){
            front = new DNode<T>;
            front->next = NULL;
            back = front;
            length = 0;
        }
        ~LinkQueue(){
            while(front!=NULL){
                back = front;
                front = front->next;
                delete back;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void enQueue(T x){
            DNode<T>* tmpN = new DNode<T>;
            tmpN->data = x;
            tmpN->next = NULL;
            back->next = tmpN;
            back = tmpN;
            length++;
        }
        T deQueue(){
            if(length==0) throw "Queue Empty!";
            DNode<T>* tmpN = front->next;
            front->next = tmpN->next;
            T tmpD = tmpN->data;
            delete tmpN;
            length--;
            if(length==0) back = front;
            return tmpD;
        }
        T peekQueue(){
            if(length==0) throw "Queue Empty!";
            return front->next->data;
        }
        void printQueue(){
            cout << "Front of queue: ";
            DNode<T>* tmp = front->next;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ": back of queue" << endl;
        }
};

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

template <class T>
struct MultiKey{
    T* keys;
    int keylength;
};

/* UPLOAD START */
template <class T>
void Dis(MultiKey<T>** mk,LinkQueue<int> *stack,int n,int j){
	int i;
	for(i=0;i<n;i++){
		int k=mk[i]->keys[j];
		stack[k].enQueue(i);
	}
}
template <class T>
void Col(MultiKey<T>** mk,LinkQueue<int> *stack,int n,int j, int low, int high){
	MultiKey<int> **tmp = new MultiKey<int>*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new MultiKey<int>;
        tmp[i]->keys = mk[i]->keys;
        tmp[i]->keylength = mk[i]->keylength;
    }
	int k=high;
	int first;
	int i=0;
	while(k>=0){
		while(!stack[k].isEmpty()){
			first=stack[k].deQueue();
			mk[i]->keys=tmp[first]->keys;
			i++;
		}
		k--;
	}
}
template <class T>
void radixDesc(MultiKey<T>** mk, int n, int keylen, int low, int high){
    // mk is an array of MultiKey<T>*
    // n = number of items in mk.
    //key[0] most important, key[1] second most important
    // low and high inclusive
    // TODO
    LinkQueue<int> *stack=new LinkQueue<int> [high+1];
    for(int j=keylen-1;j>=0;j--){
    	Dis(mk,stack,n,j);//分装
    	Col(mk,stack,n,j,0,high);//收集
	}
}

/* UPLOAD END */

int simpleTest(){
    srand(7654321);
    MultiKey<int>** mk = new MultiKey<int>*[30];
    for(int i=0;i<30;i++){
        mk[i] = new MultiKey<int>;
        mk[i]->keys = generateRandom(4,1,9);
        mk[i]->keylength = 4;
    }
    
    radixDesc(mk,30,4,1,9);
    
    //print results
    for(int i=0;i<30;i++){
        for(int j=0;j<4;j++){
            cout << mk[i]->keys[j];
        }
        cout << " ";
        if(i%10==9) cout << endl;
    }
    
    return 0;
}

int main(){
    simpleTest();
    return 0;
}
