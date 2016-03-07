#include<iostream>
#include<iomanip>

using namespace std;
int direct;

class Block{
public:
	//Block():e(0),w(0),s(0),n(0),walk(false){}
	//char e,w,s,n;
	Block():s("0000"),walk(false){}
	string s;
	bool walk;
	
};

Block myB[50][50];

void updateBlock(int dir, Block &bl,string str){
	if(bl.s != str)
		bl.s = str;
	if(!bl.walk)
		bl.walk =true;
	direct = dir;
}
pair<int, int> turnlf(string s1, int r, int c){
	int row = 50, col = 50;
	int i=1, bi=r, bj=c;
	
	updateBlock(direct, myB[bi][bj],"0001");
	bi++;
	char fi, se;
	while(i < s1.size()){
		fi = s1[i];
		if(fi != 'W'){
			i++;	
			se = s1[i];
			if(fi == 'L' && se == 'W'){
				switch(direct) {
					case 0://90wn
						updateBlock(90, myB[bi][bj],"0101");
						bi--;
						break;
					case 90://180sw
						updateBlock(180, myB[bi][bj],"0110");
						bj--;
						break;
					case 180://270es
						updateBlock(270, myB[bi][bj],"1010");
						bi++;
						break;
					case 270://0ne
						updateBlock(0, myB[bi][bj],"1001");
						bj++;
						break;
				}
			}
			else if(fi == 'R' && se == 'W'){
				switch(direct) {
					case 0://270ws
						updateBlock(270, myB[bi][bj],"0110");
						bi++;
						break;
					case 90://0se
						updateBlock(0, myB[bi][bj],"1010");
						bj++;
						break;
					case 180://90en
						updateBlock(90, myB[bi][bj],"1001");
						bi--;
						break;
					case 270://180nw
						updateBlock(180, myB[bi][bj],"0101");
						bj--;
						break;
				}
			}
			else if(fi == 'R' && se == 'R'){
				switch(direct){//e,w,s,n;
					case 0://180w
						updateBlock(180, myB[bi][bj],"0100");
						bj--;
						break;
					case 90://270s
						updateBlock(270, myB[bi][bj],"0010");
						bi++;
						break;
					case 180://0e
						updateBlock(0, myB[bi][bj],"1000");
						bj++;
						break;
					case 270://90n
						updateBlock(90, myB[bi][bj],"0001");
						bi--;
						break;
				}//switch
				i++;//read one more step which must be 'W'	
			}	
		}//first if
		
		else if(fi == 'W'){
			switch(direct){//e,w,s,n;
					case 0://
						updateBlock(0, myB[bi][bj],"1100");
						bj++;
						break;
					case 90://
						updateBlock(90, myB[bi][bj],"0011");
						bi--;
						break;
					case 180://
						updateBlock(180, myB[bi][bj],"1100");
						bj--;
						break;
					case 270://
						updateBlock(270, myB[bi][bj],"00s1");
						bi++;
						break;
				}
		}
		i++;
	}//end of while
	for(int m =0; m < row; m++){
		for(int n = 0; n< col; n++)
			if(myB[m][n].walk)
				cout<<"1 ";
			else
				cout<<"0 ";
		cout<<endl;
	}/*
	for(int m =0; m< s1.size(); m++)
		cout<<setw(2)<<m<<" ";
	cout<<endl;
	for(int m =0; m< s1.size(); m++)
		cout<<setw(2)<<s1[m]<<" ";
	cout<<endl;*/	
	direct = direct >= 180 ? direct-180: direct+180;
	pair<int, int> re (bi,bj);
	return  re;
}//end pf func

int main(){
direct = 270;
pair<int, int> tem = turnlf("WRWWLWWLWWLWLWRRWRWWWRWWRWLW",0,25); 
cout<<endl;
turnlf("WWRRWLWLWWLWWLWWRWWRWWLW", tem.first, tem.second);

return 0;
}
