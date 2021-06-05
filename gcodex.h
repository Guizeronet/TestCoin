#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

#include <stdlib.h>
#include <time.h>

bool is_prime(int value) {
	int i;
	
	for(i = 2; i < value; i ++) {
		if(value % i == 0) return false;
	}
	
	return true;
}

void generate_keys(string keys[], bool rndseed = true) {
	stringstream key_private;
	stringstream key_public;
	
	if (rndseed) srand (time(NULL));
	
	int j, i, const_value, public_value, private_value;
	char a, b;
	
	for(j = 0; j < 5; j++) {
		
		public_value = rand() % 65521 + 2;
		
		for(i = public_value; i <= 65535; i++) {
			if(is_prime(i)) {
				public_value = i;
				break;
			}
		}
		
		private_value = public_value + (rand() % 256 + 125);
		
		for(i = private_value; i <= 65535; i++) {
			if(is_prime(i)) {
				private_value = i;
				break;
			}
		}
		
		const_value = public_value + private_value;
		
		a = const_value / 255;
		b = const_value % 255;
		
		key_public << a << b;
		key_private << a << b;
		
		a = public_value / 255;
		b = public_value % 255;
		key_public << a << b;
		
		a = private_value / 255;
		b = private_value % 255;
		key_private << a << b;
		
	}
	
	keys[0] = key_private.str();
	keys[1] = key_public.str();
}

string encrypt(string data, string public_key) {
	stringstream encrypted_str;
	char a, b;
	int p_val, c_val, t_val, cript;
	
	for(int i = 0, k = 0; i < data.size(); i ++, k += 4) {
		t_val = (int) data.at(i);
		
		a = public_key.at(k);
		b = public_key.at(k + 1);
		
		c_val = int((unsigned char)a) * 255 + int((unsigned char)b);
		
		a = public_key.at(k + 2);
		b = public_key.at(k + 3);
		p_val = int((unsigned char)a) * 255 + int((unsigned char)b);
		
		cript = (t_val + p_val) % c_val;
		a = cript / 255;
		b = cript % 255;
		
		encrypted_str << a << b;
		
		if(k == public_key.size() - 4) k = -4;
	}
	
	return encrypted_str.str();
}

string decrypt(string data, string public_key) {
	stringstream encrypted_str;
	char a, b;
	int p_val, c_val, t_val, cript;
	
	for(int i = 0, k = 0; i < data.size(); i += 2, k += 4) {
		a = data.at(i);
		b = data.at(i + 1);
		t_val = int((unsigned char)a) * 255 + int((unsigned char)b);
		
		a = public_key.at(k);
		b = public_key.at(k + 1);
		c_val = int((unsigned char)a) * 255 + int((unsigned char)b);
		
		a = public_key.at(k + 2);
		b = public_key.at(k + 3);
		p_val = int((unsigned char)a) * 255 + int((unsigned char)b);
		
		cript = (t_val + p_val) % c_val;
		a = cript;
		
		encrypted_str << a;
		
		if(k == public_key.size() - 4) k = -4;
	}
	
	return encrypted_str.str();
} 

bool is_valid_sign(string signature, string data, string public_key) {
	return decrypt(signature, public_key) == data;
}

string sing_data(string data, string private_key) {
	return encrypt(data, private_key);
}
