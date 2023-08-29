#include <iostream>
using namespace std;

/* UPLOAD START */

template <class T>
struct node{
	int r,c;
	T x;
	node* next;
};


// In the class below, we assume it is meaningful to put 0 as a value for the type T.
template <class T>
class SparseMatrix{
    private:
        int r,c,num;
        node<T> *head;
    public:
        SparseMatrix(){
        	r=10;c=10,num=0;
        	head=new node<T>;
        	head->r=0;
        	head->c=0;
        	head->next=NULL;
            // default is 10 rows, 10 columns
            
        }
        SparseMatrix(int r0, int c0){
            r=r0;c=c0,num=0;
        	head=new node<T>;
        	head->r=0;
        	head->c=0;
        	head->next=NULL;
        }
        ~SparseMatrix(){
        	node<T> *tmp=head->next;
        	node<T> *front=head->next;
        	while(tmp){
        		tmp=tmp->next;
        		delete front;
        		front=tmp;
			}
        }
        void setEntry(int rPos, int cPos, T x){
            node<T> *NN=new node<T>;
            NN->c=cPos;
            NN->r=rPos;
            NN->x=x;
            int i=0;
            node<T> *tmp=head->next;
            node<T> *Front=head;
			if(rPos<this->r&&cPos<this->c&&x!=0){
				while(i<num){
					if(rPos>tmp->r){
						Front=tmp;
						tmp=tmp->next;
					}
					else if(rPos==tmp->r&&cPos>tmp->c){
						Front=tmp;
						tmp=tmp->next;
					}
					else if(rPos==tmp->r&&cPos==tmp->c){
						tmp->x=x;
						break;
					}
					else{
						Front->next=NN;
						NN->next=tmp;num++;
						break;
					}
					i++;
				}
				if(i==num){
					Front->next=NN;
					NN->next=tmp;
					num++;
				}
			}
        }
        T getEntry(int rPos, int cPos){
            node<T> *tmp=head->next;
            for(;tmp!=NULL;tmp=tmp->next){
            	if(rPos==tmp->r&&cPos==tmp->c) return tmp->x;
			}
			return 0;
        }
        SparseMatrix<T> * add(SparseMatrix<T> * B){
            int i,j,k;
            i=0;j=0;k=0;
			SparseMatrix<T> *R=new SparseMatrix<T>;
            node<T> *a=this->head->next;
            node<T> *b=B->head->next;
            if(this->c!=B->c||this->r!=B->r){
            	throw "Matrices have incompatible sizes";
			}
			else{
				R->c=this->c;R->r=this->r;
				while(i<this->num&&j<B->num){
					if(a->r==b->r&&a->c==b->c){
						R->setEntry(a->r,a->c,a->x+b->x);
						a=a->next;b=b->next;
						i++;j++;
					}
					else if(a->r<b->r||a->r==b->r&&a->c<b->c){
						R->setEntry(a->r,a->c,a->x);
						a=a->next;
						i++;
					}
					else if(b->r<a->r||b->r==a->r&&b->c<a->c){
						R->setEntry(b->r,b->c,b->x);
						b=b->next;
						j++;
					}
				}
				while(i<this->num){
					R->setEntry(a->r,a->c,a->x);
					a=a->next;
					i++;
				}
				while(j<B->num){
					R->setEntry(b->r,b->c,b->x);
					b=b->next;
					j++;
				}
			}
            return R;
        }
        SparseMatrix<T> * subtract(SparseMatrix<T> * B){
            int i,j,k;
            i=0;j=0;k=0;
			SparseMatrix<T> *R=new SparseMatrix<T>;
            node<T> *a=this->head->next;
            node<T> *b=B->head->next;
            if(this->c!=B->c||this->r!=B->r){
            	throw "Matrices have incompatible sizes";
			}
			else{
				R->c=this->c;R->r=this->r;
				while(i<this->num&&j<B->num){
					if(a->r==b->r&&a->c==b->c){
						R->setEntry(a->r,a->c,a->x-b->x);
						a=a->next;b=b->next;
						i++;j++;
					}
					else if(a->r<b->r||a->r==b->r&&a->c<b->c){
						R->setEntry(a->r,a->c,a->x);
						a=a->next;
						i++;
					}
					else if(b->r<a->r||b->r==a->r&&b->c<a->c){
						R->setEntry(b->r,b->c,-b->x);
						b=b->next;
						j++;
					}
				}
				while(i<this->num){
					R->setEntry(a->r,a->c,a->x);
					a=a->next;
					i++;
				}
				while(j<B->num){
					R->setEntry(b->r,b->c,-b->x);
					b=b->next;
					j++;
				}
			}
            return R;
        }
        
        SparseMatrix<T> * multiply(SparseMatrix<T> * B){
            //perform multiplication if the sizes of the matrices are compatible.
            int i,j,k;
            i=0;j=0;k=0;
            int rr[this->num*B->num];
            int rc[this->num*B->num];
            T rv[this->num*B->num];
			SparseMatrix<T> *R=new SparseMatrix<T>;
            node<T> *a=this->head->next;
            node<T> *b=B->head->next;
            if(this->c!=B->r){
            	throw "Matrices have incompatible sizes";
			}
			else{
				if(this->num*B->num!=0){
					R->r=this->r;R->c=B->c;
					for(i=0,a=this->head->next;a!=NULL;i++,a=a->next){
						for(j=0,b=B->head->next;b!=NULL;j++,b=b->next){
							if(a->c==b->r){
								rr[k]=a->r;
								rc[k]=b->c;
								rv[k]=a->x*b->x;
								for(int q=0;q<k;q++){
									if(rr[k]==rr[q]&&rc[k]==rc[q]){
										rv[q]+=rv[k];
										k--;
									}
								}
								k++;
							}
						}
					}
					for(i=0;i<k;i++){
						R->setEntry(rr[i],rc[i],rv[i]);
					}
				}
				
			}
			return R;
        }
        
        
        // Only call this function if you know the size of matrix is reasonable.
        void printMatrix(){
        	node<T> *tmp=head->next;
            int i,j;
            for(i=0;i<r;i++){
            	for(j=0;j<c;j++){
            		if(tmp!=NULL&&tmp->c==j&&tmp->r==i){
            			cout<<tmp->x<<" ";
            			tmp=tmp->next;
					}
					else
            			cout<<"0"<<" ";
				}
				cout<<endl;
			}
        }
        
        //This is for printing only non-zero entries
        void printNZMatrix(){
            node<T> *tmp=head->next;
            while(tmp!=NULL){
            	cout<<tmp->r<<" "<<tmp->c<<" "<<tmp->x<<endl;
            	tmp=tmp->next;
			}
        }
};

/* UPLOAD END */

int main(){

    SparseMatrix<int> X(5,5);
    SparseMatrix<int> Y(5,5);
    X.setEntry(4,0,-1);
    Y.setEntry(0,4,1);
    X.setEntry(4,4,1);
	Y.setEntry(4,4,1);
	Y.setEntry(0,0,-6);
    Y.setEntry(0,1,3);
    Y.setEntry(0,2,6);
    Y.setEntry(1,2,3);
    X.setEntry(0,2,6);
    X.setEntry(1,2,3);
    X.setEntry(0,0,6);
    X.setEntry(1,0,5);
    Y.setEntry(1,0,3);
    Y.setEntry(1,1,2);
    Y.setEntry(2,0,3);
    Y.setEntry(2,1,-2);
    X.setEntry(2,0,3);
    X.setEntry(2,2,2);
    X.setEntry(0,1,8);
    X.setEntry(1,1,0);
    X.printNZMatrix();
    cout<<endl;
    Y.printMatrix();
    cout<<endl;
    X.add(&Y)->printNZMatrix();
    cout<<endl;
    X.subtract(&Y)->printNZMatrix();
    cout<<endl;
    X.multiply(&Y)->printNZMatrix();
    return 0;
}
