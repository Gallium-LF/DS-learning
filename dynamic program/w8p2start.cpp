#include <iostream>
using namespace std;

/* Question 2 UPLOAD START */
int numOfFriendPairs(int n){
    // return the number of pairings with n people mod 10000019
    // max of n will be 150 in this problem
    long long int *num=new long long int[n+1];
    num[0]=1;num[1]=1;
    for(int i=2;i<=n;i++){
    	int tmp=0;
    	tmp=1*num[i-1]+num[i-2]*(i-1);
    	tmp%=10000019;
    	num[i]=tmp;
	}
	return num[n];
}
/* Question 2 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << (3*i) << ": " << numOfFriendPairs(3*i) << endl;
    }
}

int main(){
    test();
    return 0;
}
