#pragma once

#include <stdexcept>

#include "helper.h"
#include "gcodex.h"
#include "base64.h"

using namespace std;

class Transaction {
	
	public:
		
		string fromAddress, toAddress, signature;
		long amount;
		
		Transaction(string fromAddress, string toAddress, long amount) {
			this->fromAddress = fromAddress;
			this->toAddress = toAddress;
			this->amount = amount;
		}
		
		string calculateHash() {
			stringstream ss;
		    ss << this->fromAddress << this->toAddress << this->amount;
			return calc_hash(ss.str());
		}
		
		void singTransaction(string signingKey) {
			
			/*
			if(signingKey != this->fromAddress) {
				throw runtime_error("You cannot sign transactions for other wallets!");
			}
			*/
			
			string hashTx = this->calculateHash();
			string sig = sing_data(hashTx, base64_decode(signingKey));
			sig = base64_encode( reinterpret_cast<const unsigned char *>( sig.c_str() ) , sig.size());
			
			this->signature = sig;
		}
		
		bool isValid() {
			if(this->fromAddress == "") return true;
			
			if(this->signature.size() == 0) {
				throw runtime_error("No signature in this transaction!");
			}
			
			return is_valid_sign(base64_decode(this->signature), this->calculateHash(), base64_decode(this->fromAddress));
		}
		
		void Print() {
			cout << "fromAddress: " << this->fromAddress << endl;
			cout << "  toAddress: " << this->toAddress << endl;
			cout << "     amount: " << this->amount << endl;
			cout << "  signature: " << this->signature << endl;
		}
		
};

