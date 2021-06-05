#pragma once

#include <vector>
#include <stdexcept>

#include "helper.h"
#include "transaction.h"
#include "block.h"

class BlockChain {
	vector<Block> chain;
	vector<Transaction> peddingTransactions;
	const int miningReward = 100;
	const int difficulty = 5;
	
	public:
		
		BlockChain() {
			this->chain.push_back(createGenesisBlock());
		}
		
		Block createGenesisBlock() {
			Block *block = new Block(peddingTransactions, timeSinceEpochMillisec(), "");
			// block->mineBlock(this->difficulty);
			return *block;
		}
		
		Block getLastBlock() {
			return this->chain[this->chain.size() - 1];
		}
		
		/*
		void addNewBlock(Block *newBlock) {
			newBlock->setPreviousHash(getLastBlock().getHash());
			// newBlock->setHash(newBlock->calculateHash());
			newBlock->mineBlock(this->difficulty);
			this->chain.push_back(*newBlock);
		}
		*/
		
		void minePenddingTransactions(string miningRewardAddress) {
			Block *block = new Block(peddingTransactions, timeSinceEpochMillisec(), getLastBlock().getHash());
			block->mineBlock(this->difficulty);
			this->chain.push_back(*block);
			
			peddingTransactions.clear();
			peddingTransactions.push_back(Transaction("", miningRewardAddress, this->miningReward));
		}
		
		/*
		void createTransaction(Transaction transaction) {
			peddingTransactions.push_back(transaction);
		}
		*/
		
		void addTransaction(Transaction transaction) {
			
			if(transaction.fromAddress.size() == 0 || transaction.toAddress.size() == 0) {
				throw runtime_error("Transaction must include from and to address!");
			}
			
			if(!transaction.isValid()) {
				throw runtime_error("Cannot add invalid transaction to chain!");
			}
			
			peddingTransactions.push_back(transaction);
		}
		
		long getBalanceOfAddress(string address) {
			long balance = 0;
			
			for(int i = 0; i < this->chain.size(); i ++) {
				Block currentBlock = this->chain[i];
				
				for(int j = 0; j < currentBlock.getTransactions().size(); j ++) {
					Transaction trans = currentBlock.getTransactions()[j];
					
					if(trans.fromAddress == address) {
						balance -= trans.amount;
					}
					
					if(trans.toAddress == address) {
						balance += trans.amount;
					}
					
				}
				
			}
			
			return balance;
		}
		
		bool isChainValid() {
			
			for(int i = 1; i < this->chain.size(); i ++) {
				Block currentBlock = this->chain[i];
				Block previousBlock = this->chain[i - 1];
				
				if(!currentBlock.hasValidTransactions()) {
					return false;
				}
				
				if(currentBlock.getHash() != currentBlock.calculateHash()) {
					return false;
				}
				
				if(currentBlock.getPreviousHash() != previousBlock.getHash()) {
					return false;
				}
				
			}
			
			return true;
		}
		
		void ShowBlocks() {
			for(int i = this->chain.size() - 1; i >= 0; i --) {
				cout << i + 1 << endl;
				this->chain[i].PrintBlock();
				cout << endl;
			}
		}
};
