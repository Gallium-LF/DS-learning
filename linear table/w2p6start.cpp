#include <iostream>
using namespace std;

/* UPLOAD START */
// You can use VecList, LinkList or none of these structures in writing the IntPolynomial class
struct node{
	int mici;
	int xishu;
	node* next;
};
class IntPolynomial{
    private:
    	int *c;
    	int *d;
        int n;
        node* head;
    public:
        IntPolynomial(){
        	head = new node;
            head->next = NULL;
        	c=NULL;
        	d=NULL;
        	n=0;
        }
        IntPolynomial(int * c0, int * d0, int n0){
        	head = new node;
            head->next = NULL;
        	c=c0;
        	d=d0;
        	n=n0;
        	for(int i=n-1;i>=0;i--){
                node* tmpNode = new node;
                tmpNode->next = head->next;
                tmpNode->mici  = d[i];
                tmpNode->xishu = c[i];
                head->next = tmpNode;
            }
        }
        ~IntPolynomial(){
        	while(head!=NULL){
                node* tmpNode = head;
                head = head->next;
                delete tmpNode;
            }
        }
        int getDegree(){
        	node* a;
        	int* i=new int;
        	a=this->head;
            if(n==0) return -1;
            else{
            	while(a!=NULL){
					*i=a->mici;
            		a=a->next;
            		
				}
			}
			return *i;
        }
        IntPolynomial* Add(IntPolynomial* c){
        	node* a,*b,*l;
        	node* h=new node;
        	h->next=NULL;
        	l=h;
        	a=head->next;
        	b=c->head->next;
        	while(a!=NULL&&b!=NULL){
				if(a->mici<b->mici){
					node* m=new node;
					m->mici=a->mici;
					m->xishu=a->xishu;
					m->next=NULL;
					l->next=m;
					l=m;
					a=a->next;
				}
				else if(a->mici>b->mici){
					node* m=new node;
					m->mici=b->mici;
					m->xishu=b->xishu;
					m->next=NULL;
					l->next=m;
					l=m;
					b=b->next;
				}
				else{
					if(a->xishu+b->xishu!=0){
						node* m=new node;
						m->xishu=a->xishu+b->xishu;
						m->mici=a->mici;
						m->next=NULL;
						l->next=m;
						l=m;
						b=b->next;
						a=a->next;
					}
					else{
						b=b->next;
						a=a->next;
					}
				}
			}
			if(a==NULL&&b!=NULL){
				while(b!=NULL){
					node* m=new node;
					m->xishu=b->xishu;
					m->mici=b->mici;
					m->next=NULL;
					l->next=m;
					l=m;
					b=b->next;
				}
			}
			else if(a!=NULL&&b==NULL){
				while(a!=NULL){
					node* m=new node;
					m->xishu=a->xishu;
					m->mici=a->mici;
					m->next=NULL;
					l->next=m;
					l=m;
					a=a->next;
				}
			}
			a=h;
			int times=0;
			while(a!=NULL){
				if(a->xishu!=0) times++;
				a=a->next;
			}
			IntPolynomial* result=new IntPolynomial();
			result->n=times;
			
			result->head=h;
            return result;
        }
        IntPolynomial* Subtract(IntPolynomial* c){
        	node* a,*b,*l;
        	node* h=new node;
        	h->next=NULL;
        	l=h;
        	a=head->next;
        	b=c->head->next;
        	while(a!=NULL&&b!=NULL){
				if(a->mici<b->mici){
					node* m=new node;
					m->mici=a->mici;
					m->xishu=a->xishu;
					m->next=NULL;
					l->next=m;
					l=m;
					a=a->next;
				}
				else if(a->mici>b->mici){
					node* m=new node;
					m->mici=b->mici;
					m->xishu=-b->xishu;
					m->next=NULL;
					l->next=m;
					l=m;
					b=b->next;
				}
				else{
					if(a->xishu-b->xishu!=0){
						node* m=new node;
						m->xishu=a->xishu-b->xishu;
						m->mici=a->mici;
						m->next=NULL;
						l->next=m;
						l=m;
						b=b->next;
						a=a->next;
					}
					else{
						b=b->next;
						a=a->next;
					}
				}
			}
			if(a==NULL&&b!=NULL){
				while(b!=NULL){
					node* m=new node;
					m->xishu=-b->xishu;
					m->mici=b->mici;
					m->next=NULL;
					l->next=m;
					l=m;
					b=b->next;
				}
			}
			else if(a!=NULL&&b==NULL){
				while(a!=NULL){
					node* m=new node;
					m->xishu=a->xishu;
					m->mici=a->mici;
					m->next=NULL;
					l->next=m;
					l=m;
					a=a->next;
				}
			}
			a=h;
			int times=0;
			while(a!=NULL){
				if(a->xishu!=0) times++;
				a=a->next;
			}
			IntPolynomial* result=new IntPolynomial();
			result->n=times;
			result->head=h;
            return result;
        }
        IntPolynomial* Multiply(IntPolynomial* e){
			int i=0;
			node* a=this->head->next,*b=e->head->next,*d;
			IntPolynomial* t=new IntPolynomial();
			t->head->next=NULL;
			d=t->head;
			IntPolynomial* y=new IntPolynomial();
			node* r=new node;
			r->mici=0;
			r->xishu=0;
			r->next=NULL;
			y->head->next=r;
			while(a!=NULL)
			{   
				b=e->head->next;
				d=t->head;
				while(b!=NULL)
				{
					node* c=new node;	
					c->mici=a->mici+b->mici;
					c->xishu=a->xishu*b->xishu;
					c->next=NULL;
					d->next=c;
					d=c;			
					b=b->next;
				}
				y=y->Add(t);
				a=a->next;
			}
			int times=0;
			a=y->head;
			while(a!=NULL){
				if(a->xishu!=0) times++;
				a=a->next;
			}
			y->n=times;
			return y;
        }
        void printPolynomial(){
            int i=0;
            node* u;
            if(n==0) cout<<"0";
            else{
            for(u=head->next;u!=NULL;u=u->next){
            	if(i==0){
            		if(u->mici==1&&u->xishu==1)cout<<"x";
            		else if(u->mici==1&&u->xishu==-1)cout<<"-x";
            		else if(u->mici==0&&u->xishu!=0)cout<<u->xishu;
            		else if(u->xishu==-1&&u->mici!=1)cout<<"-x^"<<u->mici;
            		else if(u->xishu==1&&u->mici!=1)cout<<"x^"<<u->mici;
            		else if(u->xishu!=0&&u->mici!=1)cout<<u->xishu<<"x^"<<u->mici;
            		else if(u->xishu!=0&&u->mici==1)cout<<u->xishu<<"x";
            		if(u->xishu!=0)i++;
				}
				else{
					if(u->mici==1&&u->xishu==1)cout<<"+x";
            		else if(u->mici==1&&u->xishu==-1)cout<<"-x";
            		else if(u->xishu==-1&&u->mici!=1)cout<<"-x^"<<u->mici;
            		else if(u->xishu==1&&u->mici!=1)cout<<"+x^"<<u->mici;
            		else if(u->mici!=1&&u->xishu>1)cout<<"+"<<u->xishu<<"x^"<<u->mici;
            		else if(u->mici!=1&&u->xishu<-1)cout<<u->xishu<<"x^"<<u->mici;
            		else if(u->mici==1&&u->xishu>1)cout<<"+"<<u->xishu<<"x";
            		else if(u->mici==1&&u->xishu<-1)cout<<u->xishu<<"x";
					}
				}
			}
		
			cout<<endl;
        }
};

/* UPLOAD END */

void test1(){    
    int p4c[5] = {3,-5,4,5,-1};
    int p4d[5] = {0,1,5,9,11};
    IntPolynomial p4(p4c,p4d,5);
    IntPolynomial* p1;
    p1=&p4;
    p1->printPolynomial();
}

void test2(){
    int p1c[3] = {3,5,-6};
    int p1d[3] = {0,1,4};
    IntPolynomial p1(p1c,p1d,3);
    
    int p4c[5] = {3,5,6,1,-1};
    int p4d[5] = {0,1,7,9,11};
    IntPolynomial p4(p4c,p4d,5);
    p1.Add(&p4)->printPolynomial();
  p4.Subtract(&p1)->printPolynomial();
   p4.Add(&p4)->printPolynomial();
  p4.Subtract(&p4)->printPolynomial();
}

void test3(){
    int p1c[3] = {3,5,-6};
    int p1d[3] = {0,1,4};
    IntPolynomial p1(p1c,p1d,3);
    
    int p4c[5] = {3,5,6,1,-1};
    int p4d[5] = {0,1,7,9,11};
    IntPolynomial p4(p4c,p4d,5);
    p1.Multiply(&p1)->printPolynomial();
}

int main(){
    int x;
    cin >> x;
    switch(x){
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3(); 
        default:
        ;
    }
    return 0;
}
