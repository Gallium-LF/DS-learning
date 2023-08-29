#include <iostream>
#include <iomanip>
#include <stdlib.h> // for srand and rand

using namespace std;

template <class T>
class ArrayWrap{
    private:
        int length;
        T* baseArray;
        mutable int readCount; // mutable to allow modification in const functions
    public:
        ArrayWrap(){ // never actually used
            length = 0;
            baseArray = NULL;
            readCount = 0;
        }
        ArrayWrap(T* arr, int n){
            length = n;
            baseArray = arr;
            readCount = 0;
        }
        int getLength(){
            return length;
        }
        int getReadCount(){
            return readCount;
        }
        T& operator[](int pos){
            readCount++;
            return baseArray[pos];
        }
        const T& operator[](int pos) const{
            readCount++;
            return baseArray[pos];
        }
};

int maxEleBitonic(ArrayWrap<int> &aw){
    // Requirement: runtime efficiency should be O(ln n)
    // This will be observed via readCount.
    // TODO
    int leng=aw.getLength();
    int low=0,high=leng-1,mid,midD;
	while(low<=high){
		mid=(low+high)/2;
		int lowD=aw[low],highD=aw[high];
		if(highD>lowD){
			low=mid+1;
		}
		else if(highD<lowD){
			high=mid-1;
		}
		else if(highD == lowD){
			midD=aw[mid];
			if(aw[mid+1]>midD){
				low=mid+1;
			}
			else{
				high=mid-1;
			}
		}
	}
	return aw[low];
}

/* UPLOAD START */

int* testArray(int &t, int &right_ans){
    // set t as array size
	// set right_ans as correct answer
    // return the test array data
	int *a=new int [5];
	a[0]=1;a[1]=1;a[2]=3;a[3]=1;a[4]=1;
	t=5;
	right_ans=3;
	return a;
}

/* UPLOAD END */

void test(){
    int t=0;
	int right_ans = 0;
    int* testArr = testArray(t,right_ans);
    ArrayWrap<int> aw1(testArr,t);

    cout << maxEleBitonic(aw1) << " " << right_ans << endl;
}

int main(){
    test();
    return 0;
}
