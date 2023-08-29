#include <iostream>
using namespace std;
void test(int &i){
	i=i*i;
}
int main(){
	int a[5]={1,2,3,4,5};
	for(int &y:a){
		cout<<a[y];
	}
}
