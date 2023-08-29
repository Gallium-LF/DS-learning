#include <iostream>
using namespace std;

/* UPLOAD START */
template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkList{
    private:
        int length;
        DNode<T>* head;
    public:
        LinkList(){
            head = new DNode<T>;
            head->next = NULL;
            length = 0;
        }
        LinkList(T* a, int n){
            head = new DNode<T>;
            head->next = NULL;
            for(int i=n-1;i>=0;i--){
                DNode<T> *tmpNode = new DNode<T>;
                tmpNode->next = head->next;
                tmpNode->data = a[i];
                head->next = tmpNode;
            }
            length = n;
        }
        ~LinkList(){
            while(head!=NULL){
                DNode<T>* tmpNode = head;
                head = head->next;
                delete tmpNode;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(i < 0 || i > length)
                throw "Bad position";
            DNode<T>* tmpNode = head;
            for(int j=0;j<i;j++){
                tmpNode = tmpNode->next;
            }
            DNode<T>* newNode = new DNode<T>;
            newNode->data = x;
            newNode->next = tmpNode->next;
            tmpNode->next = newNode;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i < 0 || i >= length)
                throw "Bad position";
            DNode<T>* tmpNode = head;
            for(int j=0;j<i;j++){
                tmpNode = tmpNode->next;
            }
            DNode<T>* delNode = tmpNode->next;
            tmpNode->next = delNode->next;
            T tmp = delNode->data;
            delete delNode;
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i < 0 || i >= length)
                throw "Bad position";
            DNode<T>* tmpNode = head;
            for(int j=0;j<=i;j++){
                tmpNode = tmpNode->next;
            }
            tmpNode->data = x;
        }
        T getEleAtPos(int i){
            if(i < 0 || i >= length)
                throw "Bad position";
            DNode<T>* tmpNode = head;
            for(int j=0;j<=i;j++){
                tmpNode = tmpNode->next;
            }
            return tmpNode->data;
        }
        int locateEle(T x){
            DNode<T>* tmpNode = head->next;
            int count = 0;
            while(tmpNode!=NULL){
                if(tmpNode->data == x) return count;
                tmpNode = tmpNode->next;
                count++;
            }
            return -1;
        }
        void printList(){
            DNode<T>* tmpNode = head->next;
            while(tmpNode!=NULL){
                cout << tmpNode->data << " ";
                tmpNode = tmpNode->next;
            }
        }
        
        LinkList<T>* unionWithAnotherSortedList(LinkList<T>* L){
        	int l1=L->getLength() ;
        	int l2=this->getLength() ;
			int *r=new int[l1+l2];
			int i=0,j=0,k=0;
			while(i<l1&&j<l2){
				if(L->getEleAtPos(i)<this->getEleAtPos(j)&&L->getEleAtPos(i)!=r[k-1]){
					r[k]=L->getEleAtPos(i);
					k++;
					i++;
				}
				else if(L->getEleAtPos(i)>this->getEleAtPos(j)&&this->getEleAtPos(j)!=r[k-1]){
					r[k]=this->getEleAtPos(j);
					k++;
					j++;
				}
				else if(L->getEleAtPos(i)==this->getEleAtPos(j)){
					r[k]=L->getEleAtPos(i);
					k++;
					i++;
					j++;
				}
				else if(L->getEleAtPos(i)==r[k-1]){
					i++;
				}
				else if(this->getEleAtPos(j)==r[k-1]){
					j++;
				}
			}
			if(i==l1){
				for(;j<l2;j++,k++){
					r[k]=this->getEleAtPos(j);
				}
			}
			else{
				for(;i<l1;i++,k++){
					r[k]=L->getEleAtPos(i);
				}
			}
			LinkList<T> *R=new LinkList<T>(r,k);
			return R;
        }
};
/* UPLOAD END */

void test1(){
    int r[10] = {1,3,4,7,7,8,9,10,11,15};
    int s[4] = {-3,4,27,65};
    LinkList<int> *L1 = new LinkList<int>(r,10);
    LinkList<int> *L2 = new LinkList<int>(s,4);
    L1->unionWithAnotherSortedList(L2)->printList();
    cout << endl;
}

int main(){
    test1();
    return 0;
}
