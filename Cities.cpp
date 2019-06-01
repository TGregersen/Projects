#include <iostream>
#include <vector>
using namepsace std;

// Produced for Code Jam. 

//inputs
//straight road 1,2,3, left to right
//N buses with Ai Bi service range.
//P subcities

//T //#of test cases
//N
//2N integers
//P //#of cities of interest
//C city
//Ci city

int N,P,R,C;

cin>>T;
vector < vector <int> > allcases;
for(int i=0; i<T; i++){		//all test cases
	vector <int> case;
	cin>>N;
	case.push_back(N);
	for(int j=0; j<(2*case[0]); j++){	//all N lines
		cin>>R;
		case.push_back(R);
	}

	indexP=2+2*N;
	cin>>P;
	case.push_back(P);
	for(int k=0; k<case[indexP]; k++){	//all P lines
		cin>>C;
		case.push_back(C);
	}

	vector <int> count;
	for(int m=1; m<case[indexP]; m++){
		for(int l=1; l<2*case[0]; l++){	//skip N and start at ranges.
			if(case[l]<case[indexP+m]<case[l+1]){	//skip P and get cities one at a time. compare to A-B
				count[m]++;
			}
			l++; //double increase to skip to next range set.
		}
	}

	cout<<"Case #";
	cout<<i<<": ";

	for(int n=1; n<case[indexP]; n++){
		cout<<count[n];
	}

	allcases.push_back(case);
}
