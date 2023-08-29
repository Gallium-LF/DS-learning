#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/* UPLOAD START */
int simplePatternMatch(string s, string p){
    int i=0,j=0,rs=0,rp=0,k=0,star=0;
    bool hh=false;
    int pL=p.length(),sL=s.length();
    for(;i<sL&&j<pL;){
    		if(p[j]=='*'){
    			rp=j++;
    			rs=i;
    			hh=true;
			}
    		if(s[i]==p[j]){
    			i++;
	    		j++;
			}
			else if(!hh&&s[i]!=p[j]){
				i-=j-1;
				j=0;
			}
			else if(hh&&s[i]!=p[j]){
				
				i-=j-rp-2;j=rp+1;
				k++;
			}
	}
	for(int kp=0;kp<p.length();kp++)
		if(p[kp]=='*') star++;
	if(p[j]=='\0') return i-j-k+star;
	else return -1;
}

/* UPLOAD END */

int main(){
    int x;
    cin >> x;
    string s1 = "aaccdabbca";
    switch(x){
        case 1:
            cout << simplePatternMatch(s1,"abb") << endl;
            cout << simplePatternMatch(s1,"cda") << endl;
            cout << simplePatternMatch(s1,"ccdb") << endl;
            break;
        case 2:
            cout << simplePatternMatch(s1,"aa*ab") << endl;
            cout << simplePatternMatch(s1,"ad*ab") << endl;
            cout << simplePatternMatch(s1,"ac*d") << endl;
            break;
        case 3:
            cout << simplePatternMatch(s1,"e*ac*da") << endl;
            cout << simplePatternMatch(s1,"ac*cb*a") << endl;
            cout << simplePatternMatch(s1,"c*cd*ca") << endl;
        default: ;
    }
    return 0;
}
