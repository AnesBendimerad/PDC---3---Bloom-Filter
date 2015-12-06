#pragma once

class HashIterator {
public:
	HashIterator(unsigned int hashValue_1, unsigned int hashValue_2);
	unsigned int getNextHash();
private:
	unsigned int hashValue_1;
	unsigned int hashValue_2;
	unsigned int i = 0;

};