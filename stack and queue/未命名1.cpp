#include <iostream>
 using namespace std;
int set[100];
int k;
 
void q(int n,int m,int i)
{
    if(n==k&&n!=m)
    {
        i=0;
    }
    if(n==1)
    {
        cout<<"1"<<endl;
        return;
    }
    else if(m==1)
    {
        for(int i=0; i<n-1; i++)
            cout<<"1+";
        cout<<"1"<<endl;
        return;
    }
    if(n<m)
    {
        q(n,n,i);
    }
    if(n==m)
    {
        cout<<n<<endl;
        for(int j=0; j<i; j++)
            cout<<set[j]<<"+";
        q(n,m-1,i);
 
    }
    if(n>m)
    {
        cout<<m<<"+";
        set[i++]=m;
        q(n-m,m,i);
        i--;
        for(int j=0; j<i; j++)
            cout<<set[j]<<"+";
        q(n,m-1,i);
    }
}
 
int main()
{
    int n;
    cin>>n;
    k=n;
    q(n,n,0);
    return 0;
}
