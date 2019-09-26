//***************************START OF FILE**********************
// School: Colorado Technical University
// Class: Design and Analysis of Algorithms
// Class Code: CS627-1903A-01
// Project: Unit 2 Individual Project
// Author: Todd Gregersen

// Date: 2019 - July - 17

// Compiled with: G++ 4.2.1
// OS: macOS 10.14.5


#include <iostream>
#include <string>

using namespace std;

static int j=30;  // Size of the array.

//******************** Main Algorithm *****************************

// Break down function, performs search in a recursive fashion.
int breakdown(string arr[], int l, int h, string value) {	
	int r = h - l;
	int a = 0;
	int b = 0;
	int c = 0;
	int t = 0;

	if( r > 3 ){
		t = r/3;

		// Evaluate the search value to find where it fits in array.
		if( value[0] >= arr[l][0] && value[0] <= arr[l+t-1][0] ){

			// Search sub section of array.
			a = breakdown(arr, l, l+t-1, value);
		}
		if( value[0] >= arr[l+t][0] && value[0] <= arr[h-t][0] ){
			b = breakdown(arr, l+t, h-t, value);
		}
		if( value[0] >= arr[h-t+1][0] && value[0] <= arr[h][0] ){
			c = breakdown(arr, h-t+1, h, value);
		}
	} else {

		// If the size of the r value is less than 3 then compare all values from l to h.
		for(int i=l; i<=h; i++){
			if( value == arr[i]){
				return i;	// return index for match.
			}
		}
	}

	if (a>0){ return a; }	// Return a to calling function.
	if (b>0){ return b; }	// Return b to calling function.
	if (c>0){ return c; }	// Return c to calling function.
	
	return -1;	// Failed state. No value found.
}

//*****************************************************************

// Search function, formats information for the recursion function.
int Search(string playlist[], string value){
	int L = 0;
	int H = j-1;  // Get the size of the array.

	int answer = breakdown(playlist, L, H, value);
	return answer;
}

// Main Driver
int main(int argc, const char* argv[]){
	string v = "Test";
	string arr[30];  // Define array size here as well.

	for( int k=0; k<j; k++ ) {	// Initialize array and fill with data.
		string t = "";
		for( int m=0; m<5; m++ ) {
			t.append("a");
			t.append("b");
		}
		arr[k] = t;
	}

	arr[29] = "testtest"; 	// Test value.
	int p = Search(arr, "testtest");
	
	cout<<"END VALUE: "<<p<<endl;	// Output test.

	return 0;
}
//**************************END OF FILE****************************