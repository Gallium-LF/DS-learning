#include <iostream>
using namespace std;

int* dp= new int [1000];
int minOpMatrixMult(int* sizes, int n){
    // n represents number of matrices
    // 0th matrix has dimensions sizes[0] x sizes[1]
    // 1st matrix has dimensions sizes[1] x sizes[2]
    // ...
    // (n-1)-th matrix has dimensions sizes[n-1] x sizes[n]
    //
    // Goal: find minimum number of operations to multiply the whole set of matrices
    // also print the parenthesis to do it.
    
    // TODO
    if(sizes==NULL||n==0){
        return 0;
    }
    dp[0]=0;
    dp[1]=sizes[0]*sizes[1]*sizes[2];
    for(int i=2;i<n;i++){
        int sum1=dp[i-2]+sizes[i-1]*sizes[i]*sizes[i+1]+sizes[0]*sizes[i-1]*sizes[i+1];
        int sum2=dp[i-1]+sizes[0]*sizes[i]*sizes[i+1];
        dp[i]=sum1>sum2?sum2:sum1;
    }
    return dp[n-1];
}

/* UPLOAD START */

int* testArray(int &t, int &right_ans){
    // set t as array size
	// set right_ans as correct answer
    // return the test array data
    int *a=new int [5];
    a[0]=10;a[1]=3;a[2]=10;a[3]=3;a[4]=3;
    t=5;
    right_ans=207;
    return a;
}

/* UPLOAD END */

void test(){
    int t=0;
	int right_ans = 0;
    int* testArr = testArray(t,right_ans);
    
    cout << minOpMatrixMult(testArr,t-1) << " " << right_ans << endl;
}

int main(){
    test();
    return 0;
}
