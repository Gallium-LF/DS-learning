#include <iostream>
#include <stdlib.h>
using namespace std;

/* UPLOAD START */
int Parr(int *r,int first,int end){
	int i=first,j=end;
	while(i<j){
		while(i<j&&r[i]<r[j])j--;
		if(i<j){
			int tmp=r[j];
			r[j]=r[i];
			r[i]=tmp;
			i++;
		}
		while(i<j&&r[i]<=r[j])i++;
		if(i<j){
			int tmp=r[j];
			r[j]=r[i];
			r[i]=tmp;
			j--;
		}
	}
	return i;
}
void Quick(int *r,int first,int end){
	if(first<end){
		int p=Parr(r,first,end);
		Quick(r,first,p-1);
		Quick(r,p+1,end);
	}
}
int maxQuadProduct(int* arr, int n){
    // TODO
    int i,j;
	int times=0;
	Quick(arr,0,n-1);
	for(i=0;i<4;i++){
		if(arr[i]<0)times++;
	}
	if(times==2||times==3){
		int a=arr[0]*arr[1]*arr[n-2]*arr[n-1];
		int b=arr[n-3]*arr[n-4]*arr[n-2]*arr[n-1];
		return a>b?a:b;
	}
	else if(times==4){
		int a=arr[0]*arr[1]*arr[n-2]*arr[n-1];
		int b=arr[n-3]*arr[n-4]*arr[n-2]*arr[n-1];
		int c=arr[0]*arr[1]*arr[2]*arr[3];
		if(a>=b&&a>=c)return a;
		else if(b>=a&&b>=c) return b;
		else if(c>=a&&c>=b) return c;
	}
	else{
		return arr[n-3]*arr[n-4]*arr[n-2]*arr[n-1];
	}
}

/* UPLOAD END */

void test1(){
    int tmp1[7] = {3,7,5,1,9,10,2};
    int tmp4[10] = {-10,-8,-2,0,3,9,15,1,7,4};
    cout << "Case 1: Maximum product is " << maxQuadProduct(tmp1,7) << endl;
    cout << "Case 4: Maximum product is " << maxQuadProduct(tmp4,10) << endl;
    cout << endl;
}

int main()
{
    test1();
    return 0;
}
