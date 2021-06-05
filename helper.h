#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

long timeSinceEpochMillisec() {
	time_t t = time(0);
	return t;
}

string calc_hash(string data) {
	int b1 = 7, b2 = 7, b3 = 7, b4 = 7, b5 = 7, b6 = 7, b7 = 7, b8 = 7, v, s;
	
	for(int i = 0; i < data.size(); i ++) {
		v = (int) data.at(i);
		
		b1 = (b1 + b8 + v) % 65535;
		b2 = (b1 + b2 + v) % 65535;
		b3 = (b2 + b3 + v) % 65535;
		b4 = (b3 + b4 + v) % 65535;
		b5 = (b4 + b5 + v) % 65535;
		b6 = (b5 + b6 + v) % 65535;
		b7 = (b6 + b7 + v) % 65535;
		b8 = (b7 + b8 + v) % 65535;
	}
	
	stringstream ss;
	ss << setfill('0') << setw(4) << uppercase << hex << b1;
	ss << setfill('0') << setw(4) << uppercase << hex << b2;
	ss << setfill('0') << setw(4) << uppercase << hex << b3;
	ss << setfill('0') << setw(4) << uppercase << hex << b4;
	ss << setfill('0') << setw(4) << uppercase << hex << b5;
	ss << setfill('0') << setw(4) << uppercase << hex << b6;
	ss << setfill('0') << setw(4) << uppercase << hex << b7;
	ss << setfill('0') << setw(4) << uppercase << hex << b8;
	return ss.str();
}


/*

void generate_keys(string keys[]) {
	stringstream key_private;
	stringstream key_public;
	string commom_msg = "generate_keys";
	int i, vc, pk, vv, cp, pv;
	char a, b;
	
	vc = rand() % 253 + 10;
	a = vc;
	
	key_private << a;
	key_public << a;
	
	for(i = 0; i < commom_msg.size(); i ++) {
		vv = (int) commom_msg.at(i);
		
		pk = rand() % 255;
		cp = vc * pk + vv;
		pv = (vv + cp) / vc;
		
		a = pv / 255;
		b = pv % 255;
		key_private << a << b;
		
		a = pk / 255;
		b = pk % 255;
		key_public << a << b;
	}
	
	keys[0] = key_private.str();
	keys[1] = key_public.str();
}

string encrypt_str_1(string data, string public_key) {
	int vv, pk, i, j, vc, cp;
	stringstream ss;
	char a, b;
	
	vc = (int) public_key.at(0);
	
	for(i = 0, j = 1; i < data.size(); i ++, j += 2) {
		vv = (int) data.at(i);
		
		a = public_key.at(j);
		b = public_key.at(j + 1);
		pk = (int)a * 255 + (int)b;
		
		cp = vc * pk + vv;
		a = cp / 255;
		b = cp % 255;
		
		ss << a << b;
		
		if(j >= public_key.size() - 2) j = -1;
	}
	
	return ss.str();
}

string decrypt_str_1(string data, string private_key) {
	int vv, pv, i, j, vc, cp;
	stringstream ss;
	char a, b;
	
	vc = (int) private_key.at(0);
	
	for(i = 0, j = 1; i < data.size(); i ++, j += 2) {
		a = data.at(i);
		b = data.at(i);
		cp = (int)a * 255 + (int)b;
		
		a = private_key.at(j);
		b = private_key.at(j + 1);
		pv = (int)a * 255 + (int)b;
		
		vv = vc * pv - cp;
		a = vv;
		
		ss << a;
		
		if(j >= private_key.size() - 2) j = -1;
	}
	
	return ss.str();
}



string encrypt_str(string data, string encrypt_key) {
	int vi, vj, i, j, nv;
	stringstream ss;
	char a, b;
	
	for(i = 0, j = 0; i < data.size(); i ++, j ++) {
		vi = (int) data.at(i);
		vj = (int) encrypt_key.at(j);
		
		nv = vi + vj;
		a = nv / 255;
		b = nv % 255;
		
		ss << a << b ;
		
		if(j >= encrypt_key.size() - 1) j = -1;
	}
	
	return ss.str();
}

string decrypt_str(string data, string encrypt_key) {
	int vi, vj, i, j, nv;
	stringstream ss;
	char a, b;
	
	for(i = 0, j = 0; i < data.size(); i += 2, j ++) {
		vj = (int) encrypt_key.at(j);
		
		a = data.at(i);
		b = data.at(i+1);
		nv = (int)a + (int)b;
		vi = nv - vj;
		
		ss << (char)vi;
		
		if(j >= encrypt_key.size() - 1) j = -1;
	}
	
	return ss.str();
}


*/
