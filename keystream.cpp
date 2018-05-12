/*
Farokh Confectioner
CS 166 - 04
Coding A5/1 Keystream Extra Credit
*/

#include "keystream.h"
#include <iostream>

keystream::keystream(vector<int> key_val) {
	this->key = key_val;
	this->applyKey();
}

void keystream::applyKey() {
	for (int i = 0; i < x_size; i++) {
		reg_x.push_back(key[i]);
	}
	for (int i = 0; i < y_size; i++) {
		reg_y.push_back(key[i + x_size]);
	}
	for (int i = 0; i < z_size; i++) {
		reg_z.push_back(key[i + x_size + y_size]);
	}
}

vector<int> keystream::get_key_stream(int keystream_length) {
	vector<int> result;
	for (int i = 0; i < keystream_length; i++) {
		int maj = majority();

		if (reg_x[maj_pos_x] == maj) {
			int first_x = first_x_bit();
			reg_x = shift_register(reg_x, first_x);
		}
		if (reg_y[maj_pos_y] == maj) {
			int first_y = first_y_bit();
			reg_y = shift_register(reg_y, first_y);
		}
		if (reg_z[maj_pos_z] == maj) {
			int first_z = first_z_bit();
			reg_z = shift_register(reg_z, first_z);
		}
		result.push_back(reg_x[reg_x.size() - 1] ^
			reg_y[reg_y.size() - 1] ^ reg_z[reg_z.size() - 1]);
	}
	return result;
}

vector<int> keystream::shift_register(vector<int> reg, int first_bit) {
	vector<int> ret;
	ret.push_back(first_bit);
	for (int i = 0; i < reg.size() - 1; i++) {
		ret.push_back(reg[i]);
	}

	return ret;
}

int keystream::majority() {
	if(reg_x[maj_pos_x] + reg_y[maj_pos_y] + reg_z[maj_pos_z] >= 2) return 1;
	else return 0;
}

int keystream::first_x_bit() {
	return this->reg_x[13] ^ this->reg_x[16] ^ this->reg_x[17] ^ this->reg_x[18];
}

int keystream::first_y_bit() {
	return reg_y[20] ^ reg_y[21];
}

int keystream::first_z_bit() {
	return reg_z[7] ^ reg_z[20] ^ reg_z[21] ^ reg_z[22];
}

void keystream::print_arr(vector<int> arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i];
	}
	cout << endl;
}

int main() {
	vector<int> key_1 = {	
		1,0,0,1,0,0,0,1,1,1,0,1,1,0,1,
		1,0,0,0,0,0,0,1,0,1,1,1,0,1,0,
		1,1,0,1,0,1,1,1,0,0,1,0,1,0,0,
		1,0,0,0,1,1,0,1,1,0,1,1,0,0,0,
		0,0,0,1
	};

	vector<int> key_2 = {
		1,1,1,0,0,1,0,1,1,0,0,0,1,0,1,
		0,1,1,1,1,0,1,0,0,0,1,0,1,0,1,
		0,0,0,0,1,1,0,1,0,1,1,1,1,1,0,
		0,0,1,0,1,0,0,1,0,1,1,1,1,0,1,
		1,1,0,0
	};

	keystream test_obj_1(key_1);
	test_obj_1.print_arr(test_obj_1.get_key_stream(64));
	
	keystream test_obj_2(key_2);
	test_obj_2.print_arr(test_obj_2.get_key_stream(64));
}

/*
Output: 
0000011111111101100010010111101110011000010111001100001101011110
0101100011101111101100010000001100000111001100010010011111010101
*/