#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<fstream>
#include<string>

using namespace std;

void storeCredit(int a[], int size, int c){
	if(size == 0)
		cout<<"empty array.\n";
	else{
		map<int, int> storeMap;
		map<int, int>::iterator iter=storeMap.end();
		for(int i=0;i< size; i++ ){
			storeMap.insert(map<int, int>::value_type(c-a[i], a[i]));
		}
		for(int i = 0; i<size; i++){
			iter = storeMap.find(a[i]);
			if(iter!= storeMap.end()){
				cout<<"found it:\n"<<iter->first<<" "<< iter->second<<endl;
				break;	
			}
		}
		if(iter == storeMap.end())
			cout<<"no match\n";
	}

}

int minScaPro(vector<int> &v1, vector<int> &v2){
	priority_queue<int> q1(v1.begin(), v1.end()), q1_2(v1.begin(), v1.end());
	priority_queue<int, vector<int>, greater<int> > q2(v2.begin(), v2.end());
	int sum=0;
	/*while(!q1_2.empty()){
		cout<<q1_2.top()<<" ";
		q1_2.pop();
	}*/
	//cout<<endl;
	while(!q1.empty()){
		//cout<<q2.top()<<" ";
		sum+= q1.top() * q2.top();
		q1.pop();
		q2.pop();
	} 
	//cout<<"\nminimum scalar product is: "<<sum<<endl;
	return sum;
}
int main(){
	ifstream infile ("msp-s.txt");
	ofstream outfile("res-msp.txt");
	if(!infile.is_open()) 
		cout<<"file not open.\n";
	else{
		int testNum, caseNum = 1;
		string temStr;
		getline(infile, temStr);
		testNum = atoi(temStr.c_str());
		while(testNum > 0){
			getline(infile, temStr);
			int size = atoi(temStr.c_str());
			//if(size == 0)
			
			vector<int> v1(size), v2(size);
			for(int i =0; i<size; i++)
				infile >> v1[i]; 
			for(int i =0; i<size; i++)
				infile >> v2[i]; 
			outfile<<"case #"<<caseNum<<": "<<minScaPro(v1,v2)<<endl;	
			caseNum++;
			testNum--;
			getline(infile,temStr);// move to nextline;	
		}
	}
	infile.close();
	outfile.close();
return 0;
}
