#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>

class Field // сетка
{
public:
	Field() = default;
    Field(const double, const double, const double, const double, const bool);
    Field(const Field&);
    ~Field();

    void fieldInit(); // создает сетку и генерит граничные условия

    // void Print(Field &);
    // void Export(const char*); // вывод в файлы
    void print() const;
    void exportToGnuPlot(const std::string filename) const;

    bool fl;
    int numX, numT;
    double deltaT, deltaX, maxT, maxX;
    std::vector<std::vector<double>> field;
};

void init(double deltaT, double deltaX, double maxT, double maxX, bool flag);
double ODE(Field &f, int x, int t);

#endif // HEADER_H