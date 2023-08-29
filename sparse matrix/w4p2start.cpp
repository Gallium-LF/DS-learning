#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */
string g;
int* getNext(int L){
    int* next = new int[L];
    if(L==0) return next;
    next[0] = -1;
    if(L==1)
        return next;
    next[1] = 0;
    for(int i=2;i<L;i++){
        // calculate next[i]
        int k = next[i-1];
        while(k!=-1 && g[k]!=g[i-1]){
            k = next[k];
        }
        next[i] = k+1;
    }
    return next;
}

int KMP(string S){
    int i=0,j=0;
    int tLen=S.length();
    int sLen=S.length();
    int* next = getNext(tLen);
    while(i<sLen && j<tLen){
        if(j==-1||S[i]==g[j]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    if(i==sLen) return j;
}

void makePalindrome(string s){
    int i,j=0,sLen=s.length();
    for(i=sLen-1;i>=0;j++,i--){
    	g[j]=s[i];
	}
	int k=KMP(s);
	cout<<s;
	for(;k<sLen;k++)
		cout<<g[k];
	cout<<endl;
}

/* UPLOAD END */

int main(){
    int x;
    cin >> x;
    switch(x){
        case 1:
            makePalindrome("A");
            makePalindrome("ABA");
             break;
        case 2:
            makePalindrome("AB");
            makePalindrome("ABC");
             break;
        case 3:
            makePalindrome("ABCB");
            makePalindrome("ABCC");
        default: ;
    }
    return 0;
}
