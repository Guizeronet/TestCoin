# TestCoin
A not trusted blockchain implementation only for learning.

This is just an attempty to build a blockchain only for learning purpose.

File structure:

- The main.cpp is the file used to test the blockchain;
- The blockchain.h, block.h and transaction.h are files with classes that represents each part of blockchain;
- base64.h (by René Nyffenegger) is a bounch of functions used to convert some data to base64 only for improve the apresentation;
- helper.h is only an algorithm to generate a hash, to use in this implementation, it can be a very weak hash algorithm, it's porpouse is only for learning.
- gcodex.h is a bunch of function to generate a pair of symmetric keys, I have no idea if is like this that a asymmetric encryption works, I only look at wikipedia RSA post and tried to do something like that.

This project was build in windows using Dev C++ 5.11

I followed [this](https://www.youtube.com/watch?v=zVqczFZr124) tutorial series from the channel Simply Explained to make this project.
