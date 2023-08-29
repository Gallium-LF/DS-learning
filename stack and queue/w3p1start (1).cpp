#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

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
        void push(T x){//��ջ 
            DNode<T>* tmp = new DNode<T>;
            tmp->data = x;
            tmp->next = top;
            top = tmp;
            length++;
        }
        T pop(){//��ջ 
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

bool pBal(string S){
	LinkStack<char> *T=new LinkStack<char>();
	for(int i=0;i<S.length();i++){
		if(S[i]!='{'&&S[i]!='['&&S[i]!='('&&S[i]!='}'&&S[i]!=']'&&S[i]!=')') continue;
		if(S[i]=='{'||S[i]=='['||S[i]=='(') T->push(S[i]);
		else{
			if(T->isEmpty()) return false;
			char ch=T->getTop();
			if(ch=='('&&S[i]==')'||ch=='{'&&S[i]=='}'||ch=='['&&S[i]==']') T->pop();
			else return false;
		}
	}
	if(!T->isEmpty()){
		return false;
	}
	return true;
    // TODO
    
}

/* UPLOAD END */

void test1(){
    string t1 = "aaa";
    string t3 = "([{}])";
    cout << (pBal(t1) ? "Balanced" : "Unbalanced") << endl;
    cout << (pBal(t3) ? "Balanced" : "Unbalanced") << endl;
}

void test2(){
    string t1 = "()";
    string t2 = "())(";
    string t3 = "({)}";
    cout << (pBal(t1) ? "Balanced" : "Unbalanced") << endl;
    cout << (pBal(t2) ? "Balanced" : "Unbalanced") << endl;
    cout << (pBal(t3) ? "Balanced" : "Unbalanced") << endl;
}

void test3(){
    string t1 = "[([[{{23174}}]])";
    string t3 = "(((55(44))[]{}{}{}{}))";
    cout << (pBal(t1) ? "Balanced" : "Unbalanced") << endl;
    cout << (pBal(t3) ? "Balanced" : "Unbalanced") << endl;
}

int main(){
    int x;
    cin >> x;
    switch(x){
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3();
        default: ;
    }
    return 0;
}
