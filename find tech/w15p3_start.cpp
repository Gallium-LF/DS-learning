#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

class PancakeStack{
    private:
        int* stacksizes;
        int numCakes;
    public:
        PancakeStack(){
            stacksizes = NULL;
            numCakes = 0;
        }
        PancakeStack(int* sizes, int n){
            stacksizes = NULL;
            setStackSizes(sizes,n);
        }
        ~PancakeStack(){
            if(stacksizes!=NULL) delete [] stacksizes;
        }
        void setStackSizes(int* sizes, int n){
            if(stacksizes!=NULL) delete [] stacksizes;
            stacksizes = new int[n];
            numCakes = n;
            for(int i=0;i<n;i++){
                stacksizes[i] = sizes[i];
            }
        }
        void printsizes(){
            for(int i=0;i<numCakes;i++){
                cout << left << setw(6) << stacksizes[i];
                if(i%10==9) cout << endl;
            }
            cout << endl;
        }
        int getStackSize(){
            return numCakes;
        }
        int getSizeAtPos(int x){
            return stacksizes[x];
        }
        void flip(int k){
            // flip the cakes from stacksizes[0] through stacksizes[k] around.
            // (0,1,2,3,4,5,...,k,k+1,...,n) -> (k,k-1,...,1,0,k+1,...,n)
            int tmp = 0;
            for(int i=0;i<k-i;i++){
                tmp = stacksizes[i];
                stacksizes[i] = stacksizes[k-i];
                stacksizes[k-i] = tmp;
            }
        }
};

/* UPLOAD START */

void sortCakes(PancakeStack &x){
    // TODO
    // arrange cakes from small to large.
	int i,j,k;
	i=0;j=x.getStackSize();
	bool finish=false;
	while(j!=0){
		int max=-1;
		for(i=0;i<j;i++){
			if(x.getSizeAtPos(i)>max){
				max=x.getSizeAtPos(i);
				k=i;
			}
		}
		j--;
		if(k>=j)continue;
		if(x.getSizeAtPos(0)!=max){
			x.flip(k);
			x.flip(j);
		} 
		else{
			x.flip(j);
		}
	}
}

/* UPLOAD END */

void test1(){
    int cakes[5] = {5,4,2,3,1};
    PancakeStack pcs(cakes,5);
    
    sortCakes(pcs);
    pcs.printsizes();
}

int main(){
    test1();
    return 0;
}
