#include <iostream>
#include <string>
using namespace std;
int* getNext(string T){
    int L = T.length();
    int* next = new int[L];
    if(L==0) return next;
    next[0] = -1;
    if(L==1)
        return next;
    next[1] = 0;
    for(int i=2;i<L;i++){
        int k = next[i-1];
        while(k!=-1 && T[k]!=T[i-1]){
            k = next[k];
        }
        next[i] = k+1;
    }
    return next;
}
int main(){
	string s;
	cin>>s;
	int i;
	int L=s.length();
	int *next=getNext(s);
	if(L%(L-1-next[L-1])==0){
		L=L-1-next[L-1];
		cout<<L<<endl;
		for(i=0;i<L;i++){
			cout<<s[i];
		}
	}
	else{
		cout<<L<<endl;
		cout<<s;
	}
}
