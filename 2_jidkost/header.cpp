#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#include "header.h"

void Field::fieldInit()
{
    std::vector<double> v(numT, -1.0);
    field.assign(numX, v);
    for (int i = 0; i < numX; ++i)
    {
        for (int j = 0; j < numT; ++j)
        {
            if (!fl)
                {field[i][j] = 3.0*(i*deltaX-j*deltaT)+7;}
            else
                field[i][j] = 8.0*(i*deltaX*i*deltaX+2.0*j*deltaT)-4*i*deltaX+3;
        }
    }
}

Field::Field(const double deltaT_, const double deltaX_, const double maxT_, const double maxX_, const bool fl_)
{
    deltaT = deltaT_;
    deltaX = deltaX_;
    maxT = maxT_;
    maxX = maxX_;

    numT = maxT/deltaT;
    numX = maxX/deltaX;

    fl = fl_;

    fieldInit();
}

Field::Field(const Field &obj)
{
    field = obj.field;

    deltaT = obj.deltaT;
    deltaX = obj.deltaX;
    maxT = obj.maxT;
    maxX = obj.maxX;

    numT = maxT/deltaT;
    numX = maxX/deltaX;

    fl = obj.fl;

}
    
Field::~Field()
{

}

void init(double deltaT, double deltaX, double maxT, double maxX, bool flag){
    Field fluid(deltaT, deltaX, maxT, maxX, flag);
    Field diff = fluid;
    Field before = fluid;

    for (int i = 1; i <= fluid.numT; ++i)
    {
        for (int j = 1; j < fluid.numX-1; ++j)
        {
            fluid.field[j][i] = ODE(fluid, j, i);
        }
    }

    for (int i = 0; i < fluid.numT; ++i)
    {
        for (int j = 0; j < fluid.numX; ++j)
        {
            diff.field[j][i] = (fluid.field[j][i] - before.field[j][i]);
        }
    }

    cout << "ACURAT" << endl;
    before.print();
    // before.exportToGnuPlot("before.gnuplot");
    cout << endl << "APPROX" << endl;
    fluid.print();
}

double ODE(Field &f, int x, int t) {
    return (f.field[x-1][t-1]-f.field[x+1][t-1])*f.deltaT/(2*f.deltaX)+f.field[x][t-1];
}

// void Field::print() const {
//     for(int i = 0; i < this->field.size(); ++i){
//         for(int j = 0; j < this->field[0].size(); ++j){
//             cout << field[i][j] << " ";
//         }
//         cout << endl;
//     }
// }
void Field::print() const {
    for (int i = numX - 1; i >= 0; i -= round((double)numX/10))
    {
        for (int j = 0; j < numT; j += round((double)numT/10))
        {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

void Field::exportToGnuPlot(const std::string filename) const{
    ofstream file(filename);
    if(file.is_open()){
        for (int i = 0; i < numX; i++) {
            for (int j = 0; j < numT; ++j){
                file << i*deltaX << " " << j*deltaT << " " << field[i][j] << endl;
            }
        }
    }
    file.close();
}