#include <iostream>
using namespace std;

/* Question 1 UPLOAD START */
int numOfBinaryTrees(int n){
    // return the number of binary trees with n nodes mod 30011
    // max of n will be 150 in this problem
    long long int max=0;
    if(n==0) return 1;
    else{
	long long int *num=new long long int[n+1];
    num[0]=1;num[1]=1;
    for(int j=2;j<=n;j++){
    	long long int sum=0;
    	for(int i=0;i<=j-1;i++){
    		sum+=num[i]*num[j-i-1];
		}
		num[j]=sum%30011;
	}
	return num[n];
	} 
}
/* Question 1 UPLOAD END */

void test(){
    for(int i=0;i<50;i++){
        cout << (i*2) << ": " << numOfBinaryTrees(i*2) << endl;
    }
}

int main(){
    test();
    return 0;
}
