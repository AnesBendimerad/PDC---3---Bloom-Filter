#include "stdafx.h"
#include "RandomAdditionalOperations.h"
vector<unsigned int> getOrderedListOfRandomIntegers(unsigned int size, unsigned int maxInt)
{
	vector<unsigned int> randomIntegers;
	for (unsigned int i = 0; i < size; i++) {
		randomIntegers.push_back(rand() % maxInt);
	}
	sort(randomIntegers.begin(), randomIntegers.end());
	return randomIntegers;
}

string getRandomString(unsigned int len)
{
	string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	unsigned int pos;
	while (str.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		str.erase(pos, 1);
	}
	return str;
}