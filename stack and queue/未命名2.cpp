#include <iostream>
using namespace std;
template <class T>
struct DNode{
    T data;
    DNode<T>* next;
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
int main(){
	int n,m;
	cin>>n>>m;
	int i,tmp,d;
	LinkQueue<int> *q=new LinkQueue<int>;
	for(i=0;i<n;i++){
		q->enQueue(i+1);
	}
	d=m;
	while(!q->isEmpty()){
		if(m%q->getLength()!=0&&m>q->getLength()){
			d=m%q->getLength();
		}
		else
			d=m;
		for(i=1;q->getLength()>1&&i<d;i++){
			tmp=q->deQueue();
			q->enQueue(tmp);
		}
		cout<<q->deQueue()<<" ";
	}
	return 0;
} 
