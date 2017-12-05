#include <iostream>
#include <cmath>
#include "generate.h"
#include "check.h"

using namespace std;

int main(){
	// ANSI C parameters
	generateFileWithRandom(pow(2, 31), 1103515245, 12345, 12345);

	cout << "Freq crit: " << checkFrequencyCrit() << endl;
	cout << "Pair crit: " << checkPairCrit() << endl;
	cout << "Series crit: " << checkSeriesCrit() << endl;
	cout << "Poker crit: " << checkPokerCrit() << endl;

	return 0;
}