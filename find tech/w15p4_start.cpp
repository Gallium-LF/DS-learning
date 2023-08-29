#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

/* UPLOAD START */

template <class T>
class ASet{ // for now we assume datatype T can be sorted
    private:
        T *arr;
        int n;
        int cap;
        void doubleArrSize(){
            T * oldArr = arr;
            arr = new T[2*cap];
            cap = 2 * cap;
            for(int i=0;i<n;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        ASet(){
            n=0;
            cap = 100;
            arr = new T[cap];
        }
        ASet(T* arr0, int n0){ //incoming array is guaranteed not to have duplicates.
            cap = 100 + 2*n0;
            n=0;
            arr=new T[cap];
            for(int i=0;i<n0;i++){
            	addEle(arr0[i]);
			}
        }
        ~ASet(){
            delete []arr;
        }
        void addEle(T x){
        	if(this->hasEle(x))return;
        	if(n==cap)
        		this->doubleArrSize();
        	if(n==0){
        		arr[0]=x;
        		n++;
        		return;
			}
			else{
				int l=0,r=n-1;
				int mid;
				while(l<=r){
					mid=(l+r)/2;
					if(arr[mid]>x){
						r=mid-1;
					}
					else{
						l=mid+1;
					}
				}
				for(int i=n-1;i>=l;i--)
					arr[i+1]=arr[i];
				arr[l]=x;
				n++;
				return;
			}
        }
        bool isEmpty(){
            return n==0;
        }
        bool removeEle(T x){
            // returns true if removed.
            // returns false if it is not in the set
            if(hasEle(x)){
            	int l=0,r=n-1;
            	int mid;
            	while(l<=r){
            		mid=(l+r)/2;
            		if(arr[mid]==x)break;
            		else if(arr[mid]>x)r=mid-1;
            		else if(arr[mid]<x)l=mid+1;
				}
				for(int i=mid;i<n;i++)
					arr[i]=arr[i+1];
				n--;
				return true;
			}
			else return false;
        }
        bool hasEle(T x){
        	if(n==0)return false;
            else{
            	if(x>arr[n-1])return false;
            	else if(x<arr[0])return false;
            	else{
            		int l=0,r=n-1;
            		int mid;
            		while(l<=r){
            			mid=(l+r)/2;
            			if(arr[mid]==x)return true;
            			else if(arr[mid]>x)r=mid-1;
            			else if(arr[mid]<x)l=mid+1;
					}
					return false;
				}
			}
			return false;
        }
        bool isSubsetOf(ASet<T>* S){
            for(int i=0;i<n;i++){
            	if(!S->hasEle(arr[i]))return false;
			}
			return true;
        }
        bool containsSet(ASet<T>* S){
            for(int i=0;i<S->cardinality();i++){
            	if(!this->hasEle(S->arr[i]))return false;
			}
			return true;
        }
        bool isDisjointFrom(ASet<T>* S){
            for(int i=0;i<n;i++){
            	if(S->hasEle(arr[i]))return false;
			}
			return true;
        }
        int cardinality(){
            return n;
        }
        ASet<T>* setUnion(ASet<T>* S){
            ASet<T> *r=new ASet<T>(arr,n);
            if(this->isDisjointFrom(S)){
            	for(int i=0;i<S->n;i++)
            		r->addEle(S->arr[i]);
            	return r;
			} 
			else{
				for(int i=0;i<S->n;i++){
           		 	if(!r->hasEle(S->arr[i]))
            			r->addEle(S->arr[i]);
				}
				return r;	
			}
            
        }
        ASet<T>* intersect(ASet<T>* S){
        	ASet<T> *r=new ASet<T>;
            if(this->isDisjointFrom(S))
            	return r;
            else{
            	for(int i=0;i<S->n;i++){
           		 	if(this->hasEle(S->arr[i]))
            			r->addEle(S->arr[i]);
				}
				return r;
			}
        }
        ASet<T>* subtract(ASet<T>* S){
            ASet<T> *i=this->intersect(S);
            ASet<T> *r=new ASet<T>(arr,n);
            for(int j=0;j<i->n;j++){
            	r->removeEle(i->arr[j]);
			}
			return r;
        }
        ASet<T>* symDiff(ASet<T>* S){
            ASet<T> *a=this->setUnion(S);
            ASet<T> *b=this->intersect(S);
            ASet<T> *r=a->subtract(b);
			return r; 
        }
        void printSet(){ //print the elements of S in ascending order
        if(n==0){
        	cout<<"{}"<<endl;
        	return;
		}
        cout<<"{";
        for(int i=0;i<n-1;i++)
        	cout<<arr[i]<<",";
        cout<<arr[n-1]<<"}"<<endl;
        }
};

/* UPLOAD END */

void simpleTest(){
    ASet<int> A;
    for(int i=1;i<=4;i++){
        A.addEle(i);
    }
    cout << "Set A: ";
    A.printSet();
    cout << "Cardinality of A: " << A.cardinality() << endl << endl;
    
    int tmpB[4] = {3,6,5,4};
    ASet<int> B(tmpB,4);
    cout << "Set B: ";
    B.printSet();
    cout << "Cardinality of B: " << B.cardinality() << endl << endl;
    
    ASet<int>* C = A.intersect(&B);
    ASet<int>* D = A.subtract(&B);
    
    cout << "Intersecting A and B gets set C, ";
    C->printSet();
    cout << "Union of A and B is ";
    (A.setUnion(&B))->printSet();
    cout << "Let set D be the set of elements in A but not B. Then set D is ";
    D->printSet();
    cout << "Symmetric difference of A and B is ";
    (A.symDiff(&B))->printSet();
    
    cout << endl << "Checking subset relations:" << endl;
    cout << "A " << (A.containsSet(C) ? "contains" : "does not contain") << " set C" << endl;
    cout << "B " << (B.containsSet(D) ? "contains" : "does not contain") << " set D" << endl;
    cout << "C is " << (C->isSubsetOf(&A) ? "" : "not ") << "a subset of A" << endl;
    cout << "D is " << (D->isSubsetOf(&B) ? "" : "not ") << "a subset of B" << endl;
}

int main(){
	simpleTest();
    return 0;
}
