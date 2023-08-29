#include <iostream>
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

template <class T>
class BinTree{
    private:
        T data;
        BinTree<T>* left;
        BinTree<T>* right;
    public:
        BinTree(){
            left = NULL;
            right = NULL;
        }
        BinTree(T x){
            data = x;
            left = NULL;
            right = NULL;
        }
        ~BinTree(){
            
        }
        void addLChild(BinTree<T>* bt){
            left = bt;
        }
        void addLChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addLChild(bt);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
        }
        void addRChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addRChild(bt);
        }
        T getData(){
            return data;
        }
        void setData(T x){
            data = x;
        }
        BinTree<T>* getLChild(){
            return left;
        }
        BinTree<T>* getRChild(){
            return right;
        }
        void printPreOrderR(){
            cout << data << " ";
            if(left!=NULL) left->printPreOrderR();
            if(right!=NULL) right->printPreOrderR();
        }
        void printPostOrderR(){
            if(left!=NULL) left->printPostOrderR();
            if(right!=NULL) right->printPostOrderR();
            cout << data << " ";
        }
        void printInOrderR(){
            if(left!=NULL) left->printInOrderR();
            cout << data << " ";
            if(right!=NULL) right->printInOrderR();
        }
        void printLevelOrder(){
            LinkQueue<BinTree<T> *> q;
            q.enQueue(this);
            while(!q.isEmpty()){
                BinTree<T>* tmpN = q.deQueue();
                cout << tmpN->data << " ";
                if(tmpN->left!=NULL) q.enQueue(tmpN->left);
                if(tmpN->right!=NULL) q.enQueue(tmpN->right);
            }
        }
        
        void printPreOrderNR(){
            LinkStack<BinTree<T>*> s;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !s.isEmpty()){
                if(tmp!=NULL){
                    cout << tmp->data << " ";
                    s.push(tmp);
                    tmp = tmp->left;
                }
                else if(!s.isEmpty()){
                    tmp = s.pop()->right;
                }
            }
        }
        
        void printInOrderNR(){
            LinkStack<BinTree<T>*> s;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !s.isEmpty()){
                if(tmp!=NULL){
                    s.push(tmp);
                    tmp = tmp->left;
                }
                else if(!s.isEmpty()){
                    tmp = s.pop();
                    cout << tmp->data << " ";
                    tmp = tmp->right;
                }
            }
        }
        
        void printPostOrderNR(){
            LinkStack<BinTree<T>*> s;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !s.isEmpty()){
                if(tmp!=NULL){
                    s.push(tmp);
                    tmp = tmp->left;
                }
                else if(!s.isEmpty()){
                    tmp = s.pop();
                    if(!s.isEmpty() && s.getTop()==tmp){
                        cout << s.pop()->data << " ";
                        tmp = NULL;
                    }
                    else{
                        s.push(tmp);
                        s.push(tmp);
                        tmp = tmp->right;
                    }
                }
            }
        }
};

/* Solution here */

// matrix chain multiplication problem
int minOpMatrixMult(int* sizes, int n){
    // n represents number of matrices
    // 0th matrix has dimensions sizes[0] x sizes[1]
    // 1st matrix has dimensions sizes[1] x sizes[2]
    // ...
    // (n-1)-th matrix has dimensions sizes[n-1] x sizes[n]
    //
    // Goal: find minimum number of operations to multiply the whole set of matrices
    // also print the parenthesis to do it.
    void printsolution(int best[500][500],int i,int j); 
    int answer[n+1][n+1];
    int best[500][500];
    int i,j,k,l;
    for(i=0;i<n;i++){
    	answer[i][i]=0;
	}
	for(i=0;i<n+1;i++){
		for(j=0;j<n+1;j++){
			best[i][j]=0;
		}
	}
	for(l=2;l<n+1;l++){
		for(i=1;i<=n-l+1;i++){
			j=i+l-1;
			answer[i][j]=answer[i][i]+answer[i+1][j]+sizes[i-1]*sizes[i]*sizes[j];
			best[i][j]=i;
			for(k=i+1;k<j;k++){
				int tmp=answer[i][k]+answer[k+1][j]+sizes[i-1]*sizes[k]*sizes[j];
				if(tmp<answer[i][j]){
					answer[i][j]=tmp;
					best[i][j]=k;
				}
			}
		}
	}
	printsolution(best,1,n);
	cout<<endl;
	return answer[1][n];
    // TODO
}
void printsolution(int (*best)[500],int i,int j){
	if(i==j){
		cout<<"("<<i-1<<")";
	}
	else{
		cout<<"(";
		printsolution(best,i,best[i][j]);
		printsolution(best,best[i][j]+1,j);
		cout<<")";
	}
}
/* End solution */

void test1(){
    int case1[5] = {10,3,10,3,3};
    int case4[5] = {1,2,3,4,5};
    int case5[3] = {3,3,3};
    int case6[4] = {8,4,1,5};
    int case7[6] = {10,1,50,50,20,5};
    cout << "Case 1: " << endl;
    int x = minOpMatrixMult(case1,4);
    cout << "Total operations = " << x << endl << endl;
    
    cout << "Case 4: " << endl;
    x = minOpMatrixMult(case4,4);
    cout << "Total operations = " << x << endl << endl;
    
    cout << "Case 5: " << endl;
    x = minOpMatrixMult(case5,2);
    cout << "Total operations = " << x << endl << endl;
    
    cout << "Case 6: " << endl;
    x = minOpMatrixMult(case6,3);
    cout << "Total operations = " << x << endl << endl;
    
    cout << "Case 7: " << endl;
    x = minOpMatrixMult(case7,5);
    cout << "Total operations = " << x << endl << endl;
}

int main(){
    test1();
    return 0;
}
