#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "helper.h"
#include "transaction.h"

using namespace std;


class Block {
	string previousHash, hash;
	long timestamp, nonce;
	vector<Transaction> transactions;
	
	public:
		Block(vector<Transaction> transactions, long timestamp, string previousHash = "") {
			this->transactions = transactions;
			this->previousHash = previousHash;
			this->timestamp = timestamp;
			this->hash = calculateHash();
			this->nonce = 0;
		}
	
		string calculateHash() {
			stringstream ss;
		    ss << this->nonce << this->previousHash << this->timestamp;
		    
		    for(int i = 0; i < transactions.size(); i ++) {
		    	ss << transactions[i].fromAddress;
		    	ss << transactions[i].toAddress;
		    	ss << transactions[i].amount;
			}
		    
			return calc_hash(ss.str());
		}
		
		void mineBlock(int difficulty) {
			string diff_target = string(difficulty, '0');
			int tep;
			
			while(this->hash.substr(0, difficulty) != diff_target) {
				this->nonce ++;
				this->hash = calculateHash();
			}
			
			cout << "Block mined: " << this->hash << " " << this->nonce << endl;
		}
		
		bool hasValidTransactions() {
			
			for(int i = 0; i < this->transactions.size(); i ++) {
				if(!this->transactions[i].isValid()) return false;
			}
			
			return true;
		}
		
		
		string getPreviousHash() {
			return this->previousHash;
		}
		
		void setPreviousHash(string hash) {
			this->previousHash = hash;
		}
		
		string getHash() {
			return this->hash;
		}
		
		void setHash(string hash) {
			this->hash = hash;
		}
		
		vector<Transaction> getTransactions() {
			return this->transactions;
		}
		
		
		void PrintBlock() {
			cout << "previousHash: " << this->previousHash << endl;
			cout << "   timestamp: " << this->timestamp << endl;
			cout << "        hash: " << this->hash << endl;
			cout << "       nonce: " << this->nonce << endl;
			cout << "Transactions: " << endl;
			for(int i = 0; i < this->transactions.size(); i ++) {
				Transaction tx = this->transactions[i];
				cout << i + 1 << ") " << tx.fromAddress << " " << tx.toAddress << " " << tx.amount << endl;
			}
		}
	
};
