/*
Farokh Confectioner
CS 166 - 04
Coding A5/1 Keystream Extra Credit
*/

#pragma once
#include <vector>
#include <iostream>
using namespace std;

//A class modeling the A5/1 keystream.
class keystream {

public:
	//Constructs the A5/1 object
	keystream(vector<int> key_val);

	//Applies the keys to the registers
	void applyKey();

	//Returns the keystream output as a string.
	vector<int> get_key_stream(int keystream_length);

	//Prints out an array of ints.
	void print_arr(vector<int> arr);

private:
	vector<int> key;
	vector<int> reg_x;
	vector<int> reg_y;
	vector<int> reg_z;
	int x_size = 19;
	int y_size = 22;
	int z_size = 23;
	int maj_pos_x = 8;
	int maj_pos_y = 10;
	int maj_pos_z = 10;

	//Shifts all the bits right and places the first new bit in the 
	//most significant bit.
	vector<int> shift_register(vector<int> reg, int first_bit);

	//Calculates the majority value.
	int majority();

	//Gets the new first bit in register x.
	int first_x_bit();

	//Gets the new first bit in register y.
	int first_y_bit();

	//Gets the new first bit in register z.
	int first_z_bit();
};