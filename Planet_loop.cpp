#include <iostream>
#include <vector>
using namespace std;

// Created for Code Jam
// Takes in a number of test cases.
// Each case has a number of planets to visit not in a loop.
// Detects a loop by checking place on a number line.

vector <int> Nodes;
int xT, yT, nT, tT;
int index=0;
int hopcnt=0;
vector < vector<int> > pairs;
vector < vector<int> > outval;

//#Start
int main(){
	cin>>tT;
	for(int j=0; j<(tT-1); j++){
		cin>>nT;
		Nodes.push_back(nT);
		for(int i=0; i<(Nodes[j]-1); i++){
			cin>>xT;
			cin>>yT;
			vector <int> y = yT;
			pairs.push_back(xT);
			pairs.push_back(y);
		}
		
		//create number line
		vector <int> numlin;
		for(int i=0; i<(Nodes[j]-1); i++){		//pair by pair, add the numbers.
			if(!checknumlin(numlin, pairs[index+i])){
				numlin.push_back(pairs[index+i]);
			}
			if(!checknumlin(numlin, pairs[index+i][0])){
				numlin.push_back(pairs[index+i][0]);
			}
		}
		
		//#Check circle
		vector <int> circl;
		for(int i=0; i<(numlin.getsize()-1); i++){
			if(!checknumlin(circl, pairs[i][0])){	//check for previous path entry indicating circle.
				if(pair[i]==numlin[i]){				//x equal to numline value
					if(pair[i][0]==numlin[i+1]){	//y equal to next numlin value
						circl[i]=numlin[i];			//add to circl
					}else{
						int j=i;					//back up to last good setting others.
						until(circl[j]==pair[i]){
							outval.push_back(circle[j]);	//add items not in circle to output
							hopcnt++;
							circl[j]=pair[i];
							j--;
						};
						until(hopcnt==0){			//add hop count to non circle items.
							vector <int> hop=hopcnt;
							outval.push_back(hop);
							hopcnt--;
						}
					}
				}else{
					int j=i;
					until(circl[j]==pair[i]){
						circl[j]=pair[i];
						j--;
					};
				}
			}else{
				for(int i=0; i<(circl.getsize()-1); i++){
					for(int j=0; j<(outval.getsize()-1); j++){
						if(circl[i]!=outval[i]){
							outval.push_back(circl[i]);
							vector <int> hop=0;
							outval.push_back(hop);
						}
					}
				}
			}
		}

		//#Output values
		cout<<"Case #: "<<T;
		for(int i=0; i<outval.getsize(); i++){
			if(outval[i]==i)cout<<" "<<outval[i][0];
		}
		cout<<endl;

		index=Nodes[j]+index;	//set index to move on to next test case.
	}
}

bool checknumlin(vector <int>nl, int a){
	for(int i=0; i<(nl.getsize()-1); i++){
		if(nl[i]==a){
			return true;
		}
	}
	return false;
}
