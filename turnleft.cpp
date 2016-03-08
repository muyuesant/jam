#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>

using namespace std;
int direct;// global variable to hold the direction. 0 90 180 270
int maxbi, maxbj;// index help to determind the size of the maza

class Block{
public:
	Block():s("0000"),walk(false){}
	string s;// e,w,s,n;  a string which size is 4 to indicate that which wall of the block is open. 0 is close, 1 is open. 
	bool walk;// indicates that the block has been walk through.
};

Block myB[50][50];// global 2d array of block which represent the maze.

//update the string of the block and set walk to true;
void updateBlock(int dir, Block &bl,string str){
	if(bl.s != str && bl.s == "0000" && str != "0000")
		bl.s = str;
	else if(bl.s != str && bl.s != "0000" && str != "0000")
		//bl.s = str;  0101,0011,0110
		for(int i =0; i< 4; i++)
			if( str[i] =='1')
				bl.s[i] = '1';

	if(!bl.walk)
		bl.walk =true;
	direct = dir;
}

//fucntion that receives a string, the indexs of the entrance block as the parameters
// return a pair value which consists the index of the exist.
pair<int, int> turnlf(string s1, int r, int c){
	int row = 50, col = 50;
	int i=0, bi=r, bj=c;
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
				maxbi = maxbi > bi ? maxbi : bi;
				maxbj = maxbj > bj ? maxbj : bj;
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
				maxbi = maxbi > bi ? maxbi : bi;
				maxbj = maxbj > bj ? maxbj : bj;
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
				maxbi = maxbi > bi ? maxbi : bi;
				maxbj = maxbj > bj ? maxbj : bj;
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
				maxbi = maxbi > bi ? maxbi : bi;
				maxbj = maxbj > bj ? maxbj : bj;
		}
		i++;
	}//end of while
	
	direct = direct >= 180 ? direct-180: direct+180; // when get out the maze, reverse the direction.
	pair<int, int> re (bi,bj);
	return  re;
}//end pf func

void resetmyB(Block &b){
b.s="0000";
b.walk = false;
}

int main(){
ifstream infile("tl.txt");
ofstream outfile("tl-re.txt");
int testNum, caseNum=1;
string s1, s2, ts;
getline(infile, ts);
testNum = atoi(ts.c_str());
for(int k =0; k< testNum; k++){
	direct = 270;
	maxbi =0; 
	maxbj=0;
	infile>>s1;
	pair<int, int> tem = turnlf(s1,0,25); 
	infile>>s2;
	turnlf(s2,tem.first, tem.second);
	getline(infile,ts);///////move to next line;
	//reset the entrance and the exist block of the maze.
	resetmyB(myB[0][25]);
	resetmyB(myB[tem.first][tem.second]);
		
	outfile<<"case #"<< caseNum<<":";
	caseNum++;
	for(int i=0; i<= maxbi; i++){
		for(int j = 0; j<= maxbj; j++){
			if(myB[i][j].walk){
				if(stoi(myB[i][j].s,nullptr,2)>9)
					outfile<< (char)('a' + stoi(myB[i][j].s,nullptr,2) - 10);
				else
					outfile<<stoi(myB[i][j].s,nullptr,2);	
			}
			resetmyB(myB[i][j]);
		}
		outfile<<endl;
	}
	
}
infile.close();
outfile.close();
return 0;
}
