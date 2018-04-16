#ifndef ELECTRICFIELD_CUH
#define ELECTRICFIELD_CUH
#include <stdio.h>
#include <iostream>
#include <vector>

class ElectricField
{
	private:
		std::vector< std::vector<double> > _grid;
		double _xmax;
		double _xmin;
		double _ymax;
		double _ymin;
	public:
		ElectricField(double xmin, double xmax, double ymin, double ymax, int gridsX, int gridsY);
		double getEvalue(double x, double y);
		bool isIn(double x, double y);
};
#endif //ELECTRICFIELD_H
