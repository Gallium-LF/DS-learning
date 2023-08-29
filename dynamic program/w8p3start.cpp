#include <iostream>
#include <iomanip>
using namespace std;

class EggDropTest{
    private:
        int critFloor;
        int highestFloor;
        
        int numTries;
        int eggsBroken;
        bool exactFloorTested;
        bool oneAboveTested;
        
    public:
        EggDropTest(){ // do not use this.
            numTries = 0;
            eggsBroken = 0;
            exactFloorTested = false;
            oneAboveTested = false;
        }
        EggDropTest(int cfloor, int tfloor){
            critFloor = cfloor;
            highestFloor = tfloor;
            numTries = 0;
            eggsBroken = 0;
            exactFloorTested = false;
            oneAboveTested = false;
        }
        bool testFloor(int fnum){
            // true if egg survives, false if egg breaks.
            numTries++;
            if(fnum <= critFloor){
                if(fnum==critFloor) exactFloorTested = true;
                return true;
            }
            else{
                if(fnum == critFloor + 1) oneAboveTested = true;
                eggsBroken++;
                return false;
            }
        }
        int getTries(){
            return numTries;
        }
        int getEggsBroken(){
            return eggsBroken;
        }
        bool floorConfirmed(){
            if(critFloor == 0){
                return oneAboveTested;
            }
            else if(critFloor==highestFloor){
                return exactFloorTested;
            }
            else{
                return (oneAboveTested && exactFloorTested);
            }
        }
        
        void setData(int cfloor, int tfloor){
            resetTries();
            critFloor = cfloor;
            highestFloor = tfloor;
        }
        void resetTries(){
            numTries = 0;
            eggsBroken = 0;
            exactFloorTested = false;
            oneAboveTested = false;
        }
};

/* Question 3 UPLOAD START */
// guaranteed at worst 300 floors, and at worst 10 eggs.
int besttry[301][11];
int bestfloor[301][11];
void initAnswers(){
	for(int i=0;i<11;i++){
		for(int j=0;j<301;j++){
			besttry[j][i]=-2;
			bestfloor[j][i]=-2;
		}
	}
	for(int i=0;i<11;i++){
		besttry[0][i]=0;
		besttry[1][i]=1;
		bestfloor[0][i]=-1;
		bestfloor[1][i]=1;
	}
	for(int i=0;i<301;i++){
		besttry[i][0]=-1;
		besttry[i][1]=i;
		bestfloor[i][0]=-1;
		bestfloor[i][1]=1;
	}
	for(int i=2;i<11;i++){
		for(int j=2;j<301;j++){
			for(int k=1;k<=j;k++){
					int a=besttry[j-k][i]+1;
					int b=besttry[k-1][i-1]+1;
				if(besttry[j][i]==-2){
					besttry[j][i]=a>b?a:b;
					bestfloor[j][i]=1;
				}
				else{
					int tmp1=a>b?a:b;
					if(tmp1<=besttry[j][i]){
						besttry[j][i]=tmp1;
						bestfloor[j][i]=k;
					}
				}
			}
		}
	}
}

int nextTestFloor(int hFloor, int eggsLeft, int lastSurvival,int lastBreak){
    // gives us next floor to test on.
    // return -1 if there's no further need to test.
    if(eggsLeft==0)return -1;
    else if((lastSurvival+1)==lastBreak)return -1;
    else if(eggsLeft==1) return lastSurvival+1;
    else{
		int tmp=lastBreak-lastSurvival-1;
	    return lastSurvival+bestfloor[tmp][eggsLeft];
	}
    
}

int canHandleFloors(int eggs, int numTries){
	int r;
	for(int j=0;j<301;j++){
		if(besttry[j][eggs]==numTries)
			r=j;
	}
	return r;
}

int minTimesForBuilding(int eggs, int numFloors){
    return besttry[numFloors][eggs];
}

/* Question 3 UPLOAD END */

void minTimesTest(){
    for(int i=1;i<=10;i++){
        cout << right << setw(5) << i;
    }
    cout << endl;
    for(int j=1;j<=25;j++){
        for(int i=1;i<=10;i++)
            cout << right << setw(5) << minTimesForBuilding(i,j);
        cout << endl;
    }
    int testings[8] = {30,35,40,45,50,100,200,300};
    for(int j=0;j<8;j++){
        for(int i=1;i<=10;i++)
            cout << right << setw(5) << minTimesForBuilding(i,testings[j]);
        cout << endl;
    }
    cout << endl;
}

void handleFloorTest(){
    cout << right << setw(5) << " ";
    for(int i=1;i<=10;i++){
        cout << right << setw(5) << i;
    }
    cout << endl;
    for(int i=1;i<=8;i++){
        cout << right << setw(5) << i;
        for(int j=1;j<=10;j++){
            cout << right << setw(5) << canHandleFloors(j,i);
        }
        cout << endl;
    }
    cout << endl;
}

void setUpCase(int eggCount, int cFloor, int hFloor, int target){
    int lastSurvival = 0;
    int lastBreak = hFloor+1;
    int nextTest = 0;
    int eggsLeft = eggCount;
    EggDropTest edt(cFloor,hFloor);
    while(nextTest!=-1){
        nextTest = nextTestFloor(hFloor,eggsLeft,lastSurvival,lastBreak);
        if(nextTest==-1) break;
        if(edt.testFloor(nextTest)){
            lastSurvival = nextTest;
        }
        else{
            eggsLeft--;
            lastBreak = nextTest;
            if(eggsLeft==0) break;
        }
    }
    if(edt.floorConfirmed() && edt.getTries()<= target){
        cout << "Good" << endl;
    }
    else{
        cout << "Bad" << endl;
    }
}

void specificTests(int i){
    int floors[6] = {0,20,40,60,80,100};
    int counts[11] = {0,0,14,9,8,7,7,7,7,7,7};
    switch(i){
        case 10:
        case 9:
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
            for(int j=0;j<6;j++)
                setUpCase(i,floors[j],100,counts[i]);
            break;
        case 1: // reality check
            setUpCase(1,0,100,1);
            setUpCase(1,100,100,100);
            setUpCase(1,50,300,51);
            setUpCase(1,89,200,90);
        default:
            break;
    }
}

int main(){
    int testNum = 0;
    initAnswers();
    cin >> testNum;
    switch(testNum){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            specificTests(testNum);
            break;
        default:
            minTimesTest();
            handleFloorTest();
    } 
    return 0;
}
