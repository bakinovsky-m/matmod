#include <fstream>
#include <cmath>

#include "generate.h"

using namespace std;

void generateFileWithRandom(const u64 m, const u64 a, const u64 c, const u64 X0){
	ofstream f(FILENAME);

	if(f.is_open()){
		u64 current = 0;
		u64 prev = X0;

		for(u64 i = 0; i < AMOUNT; ++i){
			current = (a * prev + c) % m;
			double res = (double)current / m;
			f << res << endl;
			prev = current;
		}
	}

	f.close();
}