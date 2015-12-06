// PDC3_BloomFilter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassandra.h>
#include <conio.h>
#include <stdio.h>
#include "BitWiseArray.h"

using namespace std;

int main() {
	unsigned int N = 33;
	unsigned int i = 12;
	BitWiseArray* bitWiseArray = new BitWiseArray(N);

	for (unsigned int j = 0;j < N;j++) {
		cout << j << " : " << bitWiseArray->get(j) << endl;
	}
	bitWiseArray->set(i);
	bitWiseArray->set(i+1);
	cout << "--------------------------------" << endl;
	for (unsigned int j = 0;j < N;j++) {
		cout << j << " : " << bitWiseArray->get(j) << endl;
	}
	bitWiseArray->unset(i);
	cout << "--------------------------------" << endl;
	for (unsigned int j = 0;j < N;j++) {
		cout << j << " : " << bitWiseArray->get(j) << endl;
	}
	
	system("Pause");



}