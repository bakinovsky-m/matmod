#ifndef CHECK_H
#define CHECK_H

#include "misc.h"

bool checkFrequencyCrit();
bool checkPairCrit();
bool checkSeriesCrit();
bool checkPokerCrit();

double hiPow2(const double alpha, const int nu);
unsigned int sterlingNums(const unsigned int n, const unsigned int k);

#endif