#include <iostream>

#include "blockchain.h"
#include "gcodex.h";
#include "base64.h"

using namespace std;

int main(int argc, char** argv) {
	string chaves[2];
	
	generate_keys(chaves);
	string wallet1_private_key = base64_encode(reinterpret_cast<const unsigned char *>(chaves[0].c_str()), chaves[0].size());
	string wallet1_public_key = base64_encode(reinterpret_cast<const unsigned char *>(chaves[1].c_str()), chaves[1].size());
	
	cout << "wallet1 private_key: " << wallet1_private_key << endl;
	cout << "wallet1 public_key: " << wallet1_public_key << endl << endl;
	
	generate_keys(chaves, false);
	string wallet2_private_key = base64_encode(reinterpret_cast<const unsigned char *>(chaves[0].c_str()), chaves[0].size());
	string wallet2_public_key = base64_encode(reinterpret_cast<const unsigned char *>(chaves[1].c_str()), chaves[1].size());
	
	cout << "wallet2 private_key: " << wallet2_private_key << endl;
	cout << "wallet2 public_key: " << wallet2_public_key << endl << endl;
	
	BlockChain blockchain;
	
	Transaction* tx1 = new Transaction(wallet1_public_key, wallet2_public_key, 30);
	tx1->singTransaction(wallet1_private_key);
	blockchain.addTransaction(*tx1);
	
	cout << "Start the miner..." << endl;
	blockchain.minePenddingTransactions(wallet1_public_key);
	
	Transaction* tx2 = new Transaction(wallet1_public_key, wallet2_public_key, 20);
	tx2->singTransaction(wallet1_private_key);
	blockchain.addTransaction(*tx2);
	
	cout << "Start the miner..." << endl;
	blockchain.minePenddingTransactions(wallet1_public_key);
	
	cout << "wallet1 balance: " << blockchain.getBalanceOfAddress(wallet1_public_key) << endl;
	cout << "wallet2 balance: " << blockchain.getBalanceOfAddress(wallet2_public_key) << endl << endl;
	
	cout << "Is chain valid? " << blockchain.isChainValid() << endl;
	
	blockchain.ShowBlocks();
	
	return 0;
}
