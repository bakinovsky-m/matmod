#include <cmath>
#include <vector>
#include <fstream>

#include "check.h"

using namespace std;

bool checkFrequencyCrit(){
	vector<int> v;
	v.assign(D, 0);

	ifstream f(FILENAME);
	if(f.is_open()){
		double temp = 0;
		int ind = 0;
		while(f >> temp){
			ind = (int) (temp*10) % 10;
			v[ind]++;
		}
	} else {
		throw "no file";
		return false;
	}
	f.close();

	double stat = 0;

	for(unsigned int i = 0; i < D; ++i){
		stat += (double) pow(v[i] - AMOUNT * 1.0/D, 2) / (AMOUNT * 1.0/D);
	}

	double hiStat = hiPow2(0.95, D - 1);
	
	return stat < hiStat;
}

bool checkPairCrit(){
	vector<int> v(0);
	v.assign(D * D, 0);

	ifstream f(FILENAME);
	if(f.is_open()){
		double t1 = 0;
		double t2 = 0;
		int ind1 = 0, ind2 = 0;
		while(f >> t1 && f >> t2){
			ind1 = (int) (t1*10) % 10;
			ind2 = (int) (t2*10) % 10;
			v[ind1 * 10 + ind2]++;
		}
	} else {
		throw "no file";
		return false;
	}
	f.close();

	double stat = 0;
	for(unsigned int i = 0; i < D * D; ++i){
		stat += (double) std::pow(v[i] - AMOUNT/2 * 1.0/(D*D), 2) / (AMOUNT/2 * 1.0/(D*D));
	}

	double hiStat = hiPow2(.95, D*D - 1);

	return stat < hiStat;
}

bool checkSeriesCrit(){
	unsigned int m = 5;
	unsigned int count = 0;

	vector<int> v(0);
	v.assign(m + 1, 0);

	vector<double> p(0);
	for(unsigned int i = 0; i < m; ++i){
		p.push_back(9 * 1.0 / pow(10, i + 1));
	}
	p.push_back(1/pow(10, m));

	unsigned int l = 0;

	ifstream f(FILENAME);
	if(f.is_open()){
		double t1 = 0;
		double t2 = 0;
		int ind1 = 0, ind2 = 0;
		while(f >> t1 && f >> t2) {
			ind1 = (int) (t1 * 10) % 10;
			ind2 = (int) (t2 * 10) % 10;

			if(ind1 != ind2){
				v[l]++;
				l = 0;
			} else {
				l = min(l + 1, m + 1);
			}
		}
	}
	f.close();

	if (l > 0){
		v[l]++;
	}

	for(unsigned int i = 0; i < v.size(); ++i){
		count += v[i];
	}

	double stat = 0;
	for(unsigned int i = 0; i < v.size(); ++i){
		stat += (double) pow(v[i]-count*p[i], 2)/(count*p[i]);
	}

	double hiStat = hiPow2(0.95, m);

	return stat < hiStat;
}

bool checkPokerCrit(){
	vector<int> v(0);
	v.assign(5, 0);
	vector<int> ind2(0);
	ind2.assign(D, 0);
	vector<double> p(0);

	ifstream f(FILENAME);
	if(f.is_open()){
		unsigned int count = 0;
		unsigned int ind1 = 0;
		double temp = 0;
		for(unsigned int i = 0; i < AMOUNT/5; ++i){
			count = 0;
			ind2.clear();
			ind2.assign(D, 0);
			for(unsigned int j = 0; j < 5; ++j){
				f >> temp;
				ind1 = (int) (temp * 10) % 10;
				ind2[ind1]++;
			}
			for(unsigned int j = 0; j < ind2.size(); ++j){
				if(ind2[j] != 0){
					count++;
				}
			}
			v[count - 1]++;
		}
	}
	f.close();

	int fr = 1;
	for(unsigned int i = 1; i <= v.size(); ++i){
		fr *= D - i + 1;
		p.push_back(fr * 1.0/pow(D, 5) * sterlingNums(5, i));
	}

	double stat = 0;
	for(unsigned int i = 0; i < v.size(); ++i){
		stat += (double) pow(v[i] - AMOUNT/5 * p[i], 2) / (AMOUNT/5*p[i]);
	}

	double hiStat = hiPow2(.95, 5);

	return stat < hiStat;
}

double hiPow2(const double alpha, const int nu){
	vector<double> a = { 1.0000886 ,  0.4713941  , 0.0001348028, -0.008553069,  0.00312558 , -0.0008426812,  0.00009780499};
	vector<double> b = {-0.2237368 ,  0.02607083 , 0.01128186  , -0.01153761 ,  0.005169654,  0.00253001  , -0.001450117  };
	vector<double> c = {-0.01513904, -0.008986007, 0.02277679  , -0.01323293 , -0.006950356,  0.001060438 ,  0.001565326  };
    double d = 0;
    double sum = 0;

    if (alpha < 0.5) {
        d = -2.0637 * pow( (log(1.0 / alpha) - 0.16), 0.4274) + 1.5774;
    } else {
        d =  2.0637 * pow( (log(1.0 / (1 - alpha)) - 0.16), 0.4274) - 1.5774;
    }

    for (unsigned int i = 0; i < 7; ++i) {
        sum += pow(nu, -(1.0 * i) / 2) * pow(d, i) * (a[i] + b[i]/nu + c[i]/(pow(nu, 2)));
    }

    return nu * pow(sum, 3.0);
}

unsigned int sterlingNums(const unsigned int n, const unsigned int k){
	if (n == 0 || n == k) {
		return 1;
	}
	if (k == 0) {
    	return 0;
	}
    return sterlingNums(n - 1, k - 1) + k * sterlingNums(n - 1, k);
}