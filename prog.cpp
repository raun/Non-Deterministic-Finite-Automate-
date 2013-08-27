#include<iostream>
#include<string>
#include<fstream>
#define M 3
using namespace std;
class state{
	int *output;
	int count,N;
	public:
		state(){
			output=new int;
			N=0;
			count=0;}
		void getstate(int ar[],int n){
			N=n;
			output= new int[n];
			for(int i=0;i<n;++i)
				output[i]=ar[i];
		}
		int retOut(){
			count++;
			if(count==N){
				count=0;
				return output[N-1];
			}
			return output[count-1];
		}
		int Single(){
			if(N==1)
			return 1;
			else
			return 0;
		}
		void show(){
			cout<<output[0];
			if(N==2)
			cout<<","<<output[1];
			
	}
};
int CheckString(string str,int index,state nfa[][M],int cur,int final){
	if((str[index]=='\0')&&(cur==final))
		return 1;
	else if(str[index]=='\0')
		return 0;
	else if((nfa[cur][str[index]-'a'].Single()==1)&&(cur!=-1)){
			cur=nfa[cur][str[index]-'a'].retOut();
			cout<<"\nCurrent="<<cur;
			return CheckString(str,index+1,nfa,cur,final);
		}
		else if(cur!=-1){
			int c1=nfa[cur][str[index]-'a'].retOut(),c2=nfa[cur][str[index]-'a'].retOut();
			cout<<"\nCurrent1="<<c1<<"\tCurrent2="<<c2;
			if(CheckString(str,index+1,nfa,c1,final)==1)
				return 1;
			else if(CheckString(str,index+1,nfa,c2,final)==1)
				return 1;
			else
				return 0;
		}
}
int main(){
	ifstream fin("inp.txt");
	state NFA[10][M];
	char ch;
	int initial,final,n=0,temp[2];
	fin>>ch;
	while(fin){
		//cout<<"Inside while";
		for(int j=0;j<M;){
			if(ch>='0'&&ch<='9'){
				temp[0]=ch-'0';
				fin>>ch;
			}
			else if(ch=='*'){
				temp[0]=-1;
				fin>>ch;	
			}
			if(ch==','){
				fin>>ch;
				temp[1]=ch-'0';
				NFA[n][j].getstate(temp,2);
				//cout<<"\nPut 2 values";
				j++;
				fin>>ch;
			}
			else{
				NFA[n][j].getstate(temp,1);
				/*if(temp[0]!=-1)
				cout<<"\nput single";
				else
				cout<<"\nPut -";
				*/j++;
			}
		}
		n++;
	}
	cout<<"\nThe entered NFA is following:";
	cout<<"\nState\tOn A\tOn B\tOn C";
	for(int i=0;i<n;++i){
		cout<<endl<<"S-"<<i;
		for(int j=0;j<M;++j){
			cout<<"\t";
			NFA[i][j].show();
		}
	}
	cout<<"\nEnter initial state:";
	cin>>initial;
	cout<<"\nEnter final state:";
	cin>>final;
	string str;
	cout<<"\nEnter the string:";
	cin>>str;
	if(CheckString(str,0,NFA,0,final)==1)
		cout<<"\nAccepted";
	else
		cout<<"\nNot Accepted";
	cin>>ch;
	cout<<endl;
	return 0;
}
