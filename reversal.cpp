//***************************START OF FILE**********************
// School: Colorado Technical University
// Class: Design and Analysis of Algorithms
// Class Code: CS627-1903A-01
// Project: Unit 1 Individual Project
// Author: Todd Gregersen

// Date: 2019 - July - 10

// Compiled with: G++ 4.2.1
// OS: macOS 10.14.5

#include <iostream>
#include <iterator>
#include <chrono>
#include <ctime>

using namespace std::chrono;

// Input some qty of numbers to populate table.
void populate(int in, int table[]) { 
	for( int i = 0; i<in; i++ ){
		table[i] = i;
	}
}

//******************** Main Algorithm *****************************
// This function uses the same idea behind reversing a pair of values in place.
void Reversal(int q, int in[]) {  // Size of array and array.

	int j = (q)-1;	// Start one less than size (to avoid overflow).

	for( int i = 0; i < q/2; i++ ) { // Loop until halfway through array as we move from both ends. This will skip the mid point in an odd array.
		in[i] = in[i] ^ in[j-i]; // Set i to the xor of end point.
		in[j-i] = in[i] ^ in[j-i]; // Set end point to i.
		in[i] = in[i] ^ in[j-i]; // Set i to end point.
	}
}
//*****************************************************************

// Main driver
int main(){

	int qty = 2500;		// Set array size.

	int table[qty]; 	// Declare array.

	populate(qty, table);	// Populate the array.


	/*
	std::cout << "\nIn order: " << std::endl;		// Output the array.
	for(int i = 0; i<(qty); i++){
		std::cout << table[i] << " ";
	}
	*/

	high_resolution_clock::time_point Ts = high_resolution_clock::now();	// Get start time.
	Reversal(qty, table);		// Reverse the array.
	high_resolution_clock::time_point Te = high_resolution_clock::now();	// Get end time.

	/*
	std::cout << "\nReversed: " << std::endl;		// Output resultant array.
	for(int i = 0; i<(qty); i++){
		std::cout << table[i] << " ";
	}
	*/

	duration<double> dur = duration_cast<duration<double>>(Te-Ts);	// Process time for output.
	std::cout << "\nTime for reversal: " << dur.count() << "s\n";	// Output time.

	return 0;
}
//**************************END OF FILE****************************